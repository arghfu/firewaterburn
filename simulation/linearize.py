import re
import keyboard
import matplotlib.pyplot as plt
import numpy as np

# __________________________________ 5V
#               |
#               |
#              _|_
#              | | Rv
#              |_|
#               |
#               |___________________ ADC_IN
#              _|_     _|_
#              | | Rt  | | Rp
#              |_|     |_|
#               |       |
# ______________|_______|___________ 0V

# R(4°C) = 133,5k
# R(26°C) = 46,6k
# R(103°C) = 3k

def SolveSteinhartHart(a, b, c):
    A = np.array([[1, np.log(a[0]), np.power(np.log(a[0]), 3)],
                  [1, np.log(b[0]), np.power(np.log(b[0]), 3)],
                  [1, np.log(c[0]), np.power(np.log(c[0]), 3)]])

    b = np.array([1 / (a[1] + 273.15), 1 / (b[1] + 273.15), 1 / (c[1] + 273.15)])

    x = np.linalg.solve(A, b)

    return x


def CalcResistanceOverTemp(coeff, T):
    a0 = coeff[0]
    a1 = coeff[1]
    a3 = coeff[2]

    y = (a0 - 1 / T) / (2 * a3)
    x = np.sqrt(np.power(a1 / (3 * a3), 3) + np.power(y, 2))

    resistance = np.exp(np.cbrt(x - y) - np.cbrt(x + y))
    return resistance


def PlotDataOverTemp(temp, data, ylabel):
    temp = temp - 273.15
    fig, ax = plt.subplots()
    ax.plot(temp, data)
    plt.xlabel("Temperature(°C)")
    plt.ylabel(ylabel)
    plt.grid(True)
    ax.set_xlim(xmin=0, xmax=temp[-1])
    ax.set_ylim(ymin=0)

def CalcOperationAmplifier(temp, res, range, B, Uref, Umax):
    down = range[0]
    mid = range[1]
    up = range[2]

    Ru = res[down]
    Rm = res[mid]
    Ro = res[up]

    Tu = temp[down]
    Tm = temp[mid]
    To = temp[up]

    thetaU = Tu - 273.15
    thetaM = Tm - 273.15
    thetaO = To - 273.15

    Rlin = Rm * (B - Tm) / (B + 2 * Tm)

    Uo = Uref * Ru / (Ru + Rlin) #for PTC change Uo to Uu
    Um = Uref * Rm / (Rm + Rlin)
    Uu = Uref * Ro / (Ro + Rlin) #for PTC change Uo to Uo

    R2 = Rlin
    A = Umax/(Uo - Uu)
    a = Uu/Uref



    u = A - 1

    R1 = (a * Rlin * (u + 1)) / (u-a*u-a)
    R3 = u * (R1*R2)/(R1+R2)

    print("Range:  {}°C {}°C {}°C".format(thetaU, thetaM, thetaO))
    print("Rlin:\t {:.0f}\tR3:\t\t {:.0f}".format(Rlin, R3))
    print("R1:\t\t{:.0f}\tR2:\t\t {:.0f}\n".format(R1, R2))



def CalcVoltageDivider(temp, res, mid, B):
    Rm = res[mid]

    Tm = temp[mid]

    Rlin = Rm * (B - Tm) / (B + 2 * Tm)

    print("Rlin:\t {:.0f}\tRv:\t\t {:.0f}\n".format(Rlin, Rm))

    return Rlin, Rm


def ReadSimulation(simFile, tempRange):
    with open(simFile) as f:
        lines = f.readlines()
        lines = lines[1:]
        split = []

        temp = []
        Uopv = []

        for l in lines:
            split.append(re.split(r'\t', l))

        for i in range(len(split)):
            temp.append(float(split[i][0]))
            Uopv.append(float(split[i][1]))

        insertCnt = int(temp[0] - tempRange[0])
        appendCnt = int(tempRange[1] - temp[-1] - 1)

        tmp = Uopv[0]

        for i in range(insertCnt):
            Uopv.insert(0, tmp)

        tmp = Uopv[-1]

        for i in range(appendCnt):
            Uopv.append(tmp)

    return Uopv


def GenerateRange(tempMin, tempMax, linMin, linMax):
    tempRange = np.arange(tempMin, tempMax + 1) + 273.15
    mid = int((linMax + linMin) / 2)
    linRange = [linMin, mid, linMax]

    return tempRange, len(tempRange), linRange

def ModelingResistor(temp):
    coef = SolveSteinhartHart((133500, 4), (46600, 26), (3000, 103))
    Rt = CalcResistanceOverTemp(coef, temp)
    B = 3966.47

    return Rt, B, coef

def PlotResistorData(temp, Rt, linRange, B):
    Rlin, Rv = CalcVoltageDivider(temp, Rt, linRange[1], B)

    Rpara = (Rt * Rlin) / (Rt + Rlin)
    Uadc = U0 * Rpara / (Rpara + Rv)

    PlotDataOverTemp(temp, Uadc, "Uadc (Volt)")


def PlotOpvData(temp, Rt, linRange, B, Uref, Umax):
    CalcOperationAmplifier(temp, Rt, linRange, B, Uref, Umax)

    mid = np.linspace(0, Umax, linRange[2] - linRange[0])
    begin = np.zeros(linRange[0])
    end = Umax * np.ones(length - linRange[2])

    UopvIdeal = np.concatenate((begin, mid, end))

    print("run spice simulation with new values")
    print("to continue press +")

    keyboard.wait("+")

    Uopv = ReadSimulation("linearize.txt", (0, length))

    temp = temp - 273.15
    fig, ax = plt.subplots()
    ax.plot(temp, UopvIdeal, temp, Uopv)
    plt.xlabel("Temperature(°C)")
    plt.ylabel("Uadc(Volt)")
    plt.grid(True)
    ax.set_xlim(xmin=0, xmax=temp[-1])
    ax.set_ylim(ymin=0)


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    U0 = 3.3  # V
    Umax = 3.3

    temp, length, linRange = GenerateRange(0, 200, 70, 130)
    Rt, B, coef = ModelingResistor(temp)

    PlotResistorData(temp, Rt, linRange, B)

    PlotOpvData(temp, Rt, linRange, B, U0, U0)

    plt.show()