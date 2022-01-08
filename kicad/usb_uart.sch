EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4950 3150 4700 3150
Wire Wire Line
	4950 3050 4700 3050
Text Label 4700 3050 0    50   ~ 0
D+
Text Label 4700 3150 0    50   ~ 0
D-
$Comp
L power:+5V #PWR?
U 1 1 61D4AE4D
P 4400 2450
AR Path="/61D4AE4D" Ref="#PWR?"  Part="1" 
AR Path="/61C72A3E/61D4AE4D" Ref="#PWR?"  Part="1" 
AR Path="/61D338A3/61D4AE4D" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4400 2300 50  0001 C CNN
F 1 "+5V" H 4415 2623 50  0000 C CNN
F 2 "" H 4400 2450 50  0001 C CNN
F 3 "" H 4400 2450 50  0001 C CNN
	1    4400 2450
	1    0    0    -1  
$EndComp
NoConn ~ 5950 3550
NoConn ~ 5950 4450
NoConn ~ 5950 4350
NoConn ~ 5950 4250
NoConn ~ 5950 4150
NoConn ~ 5950 4650
NoConn ~ 5950 4750
NoConn ~ 5950 4550
Wire Wire Line
	5950 3050 6300 3050
Wire Wire Line
	5950 2850 6300 2850
Wire Wire Line
	5950 2750 6300 2750
Wire Wire Line
	5450 4950 5450 5100
$Comp
L power:GND #PWR?
U 1 1 61D4AE6E
P 5450 5100
AR Path="/61D4AE6E" Ref="#PWR?"  Part="1" 
AR Path="/61C72A3E/61D4AE6E" Ref="#PWR?"  Part="1" 
AR Path="/61D338A3/61D4AE6E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5450 4850 50  0001 C CNN
F 1 "GND" H 5455 4927 50  0000 C CNN
F 2 "" H 5450 5100 50  0001 C CNN
F 3 "" H 5450 5100 50  0001 C CNN
	1    5450 5100
	1    0    0    -1  
$EndComp
NoConn ~ 5950 3150
NoConn ~ 5950 3250
NoConn ~ 5950 3450
$Comp
L Device:R R?
U 1 1 61D4AE78
P 4400 3250
AR Path="/61D4AE78" Ref="R?"  Part="1" 
AR Path="/61245DD9/61D4AE78" Ref="R?"  Part="1" 
AR Path="/61C72A3E/61D4AE78" Ref="R?"  Part="1" 
AR Path="/61D338A3/61D4AE78" Ref="R?"  Part="1" 
F 0 "R?" H 4500 3400 50  0000 C CNN
F 1 "47k5" H 4550 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4330 3250 50  0001 C CNN
F 3 "~" H 4400 3250 50  0001 C CNN
F 4 "RMCF0603FT47K5CT-ND" V 4400 3250 50  0001 C CNN "Digikey"
	1    4400 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 61D4AE7F
P 4400 2650
AR Path="/61D4AE7F" Ref="R?"  Part="1" 
AR Path="/61245DD9/61D4AE7F" Ref="R?"  Part="1" 
AR Path="/61C72A3E/61D4AE7F" Ref="R?"  Part="1" 
AR Path="/61D338A3/61D4AE7F" Ref="R?"  Part="1" 
F 0 "R?" H 4500 2800 50  0000 C CNN
F 1 "22k1" H 4550 2500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4330 2650 50  0001 C CNN
F 3 "~" H 4400 2650 50  0001 C CNN
F 4 "RMCF0603FT22K1CT-ND" V 4400 2650 50  0001 C CNN "Digikey"
	1    4400 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2450 4400 2500
Wire Wire Line
	4400 2800 4400 2950
Connection ~ 4400 2950
Wire Wire Line
	4400 2950 4400 3100
Wire Wire Line
	4400 2950 4950 2950
$Comp
L power:GND #PWR?
U 1 1 61D4AE8A
P 4400 3550
AR Path="/61D4AE8A" Ref="#PWR?"  Part="1" 
AR Path="/61C72A3E/61D4AE8A" Ref="#PWR?"  Part="1" 
AR Path="/61D338A3/61D4AE8A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4400 3300 50  0001 C CNN
F 1 "GND" H 4405 3377 50  0000 C CNN
F 2 "" H 4400 3550 50  0001 C CNN
F 3 "" H 4400 3550 50  0001 C CNN
	1    4400 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 3550 4400 3400
$Comp
L Interface_USB:CP2102N-A01-GQFN28 U?
U 1 1 61D4AE92
P 5450 3650
AR Path="/61D4AE92" Ref="U?"  Part="1" 
AR Path="/61245DD9/61D4AE92" Ref="U?"  Part="1" 
AR Path="/61C72A3E/61D4AE92" Ref="U?"  Part="1" 
AR Path="/61D338A3/61D4AE92" Ref="U?"  Part="1" 
F 0 "U?" H 5550 4900 50  0000 C CNN
F 1 "CP2102N-A01-GQFN28" V 5000 2950 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-28-1EP_5x5mm_P0.5mm_EP3.35x3.35mm" H 5900 2450 50  0001 L CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/cp2102n-datasheet.pdf" H 5500 2900 50  0001 C CNN
F 4 "CP2102N-A02-GQFN28R" H 5450 3650 50  0001 C CNN "Digikey"
	1    5450 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 2750 4750 2750
Wire Wire Line
	4750 2750 4750 2600
$Comp
L Device:R R?
U 1 1 61D4AE9B
P 4750 2450
AR Path="/61D4AE9B" Ref="R?"  Part="1" 
AR Path="/61245DD9/61D4AE9B" Ref="R?"  Part="1" 
AR Path="/61C72A3E/61D4AE9B" Ref="R?"  Part="1" 
AR Path="/61D338A3/61D4AE9B" Ref="R?"  Part="1" 
F 0 "R?" H 4850 2600 50  0000 C CNN
F 1 "2k" H 4850 2300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4680 2450 50  0001 C CNN
F 3 "~" H 4750 2450 50  0001 C CNN
F 4 "311-2.00KHRCT-ND" V 4750 2450 50  0001 C CNN "Digikey"
	1    4750 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2300 4750 2150
$Comp
L power:+3V3 #PWR?
U 1 1 61D4AEA2
P 4750 2150
AR Path="/61D4AEA2" Ref="#PWR?"  Part="1" 
AR Path="/61C72A3E/61D4AEA2" Ref="#PWR?"  Part="1" 
AR Path="/61D338A3/61D4AEA2" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4750 2000 50  0001 C CNN
F 1 "+3V3" H 4765 2323 50  0000 C CNN
F 2 "" H 4750 2150 50  0001 C CNN
F 3 "" H 4750 2150 50  0001 C CNN
	1    4750 2150
	1    0    0    -1  
$EndComp
NoConn ~ 5950 2550
Wire Wire Line
	5950 2650 6300 2650
NoConn ~ 5950 2950
$Comp
L power:GND #PWR?
U 1 1 61C65BDB
P 1950 4800
AR Path="/61245DD9/61C65BDB" Ref="#PWR?"  Part="1" 
AR Path="/61C65BDB" Ref="#PWR?"  Part="1" 
AR Path="/61C72A3E/61C65BDB" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1950 4550 50  0001 C CNN
F 1 "GND" H 1955 4627 50  0000 C CNN
F 2 "" H 1950 4800 50  0001 C CNN
F 3 "" H 1950 4800 50  0001 C CNN
	1    1950 4800
	1    0    0    -1  
$EndComp
Connection ~ 1950 4750
Wire Wire Line
	1950 4750 1950 4800
Wire Wire Line
	2350 4750 2350 4700
Wire Wire Line
	1950 4750 2350 4750
Wire Wire Line
	1950 4700 1950 4750
Connection ~ 1950 4350
Wire Wire Line
	1950 4350 1950 4300
Wire Wire Line
	2350 4350 2350 4400
Wire Wire Line
	1950 4350 2350 4350
Wire Wire Line
	1950 4400 1950 4350
$Comp
L power:+3V3 #PWR?
U 1 1 61C65BEB
P 1950 4300
AR Path="/61245DD9/61C65BEB" Ref="#PWR?"  Part="1" 
AR Path="/61C65BEB" Ref="#PWR?"  Part="1" 
AR Path="/61C72A3E/61C65BEB" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1950 4150 50  0001 C CNN
F 1 "+3V3" H 1965 4473 50  0000 C CNN
F 2 "" H 1950 4300 50  0001 C CNN
F 3 "" H 1950 4300 50  0001 C CNN
	1    1950 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 61C65BF2
P 2350 4550
AR Path="/61245DD9/61C65BF2" Ref="C?"  Part="1" 
AR Path="/61C65BF2" Ref="C?"  Part="1" 
AR Path="/61C72A3E/61C65BF2" Ref="C?"  Part="1" 
F 0 "C?" H 2465 4596 50  0000 L CNN
F 1 "100n" H 2465 4505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2388 4400 50  0001 C CNN
F 3 "~" H 2350 4550 50  0001 C CNN
F 4 "1292-1393-1-ND" H 2350 4550 50  0001 C CNN "Digikey"
	1    2350 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 61C65BF9
P 1950 4550
AR Path="/61245DD9/61C65BF9" Ref="C?"  Part="1" 
AR Path="/61C65BF9" Ref="C?"  Part="1" 
AR Path="/61C72A3E/61C65BF9" Ref="C?"  Part="1" 
F 0 "C?" H 2065 4596 50  0000 L CNN
F 1 "4.7µ" H 2065 4505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1988 4400 50  0001 C CNN
F 3 "~" H 1950 4550 50  0001 C CNN
F 4 "1276-1045-1-ND" H 1950 4550 50  0001 C CNN "Digikey"
	1    1950 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 61C65C00
P 3600 4700
AR Path="/61245DD9/61C65C00" Ref="C?"  Part="1" 
AR Path="/61C65C00" Ref="C?"  Part="1" 
AR Path="/61C72A3E/61C65C00" Ref="C?"  Part="1" 
F 0 "C?" H 3715 4746 50  0000 L CNN
F 1 "100n" H 3715 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3638 4550 50  0001 C CNN
F 3 "~" H 3600 4700 50  0001 C CNN
F 4 "1292-1393-1-ND" H 3600 4700 50  0001 C CNN "Digikey"
	1    3600 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 61C65C06
P 3150 4450
AR Path="/61245DD9/61C65C06" Ref="#PWR?"  Part="1" 
AR Path="/61C65C06" Ref="#PWR?"  Part="1" 
AR Path="/61C72A3E/61C65C06" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3150 4300 50  0001 C CNN
F 1 "+3V3" H 3165 4623 50  0000 C CNN
F 2 "" H 3150 4450 50  0001 C CNN
F 3 "" H 3150 4450 50  0001 C CNN
	1    3150 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61C65C0C
P 3150 4950
AR Path="/61245DD9/61C65C0C" Ref="#PWR?"  Part="1" 
AR Path="/61C65C0C" Ref="#PWR?"  Part="1" 
AR Path="/61C72A3E/61C65C0C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3150 4700 50  0001 C CNN
F 1 "GND" H 3155 4777 50  0000 C CNN
F 2 "" H 3150 4950 50  0001 C CNN
F 3 "" H 3150 4950 50  0001 C CNN
	1    3150 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 4950 3150 4900
Wire Wire Line
	3150 4550 3150 4500
$Comp
L Device:C C?
U 1 1 61C65C15
P 3150 4700
AR Path="/61245DD9/61C65C15" Ref="C?"  Part="1" 
AR Path="/61C65C15" Ref="C?"  Part="1" 
AR Path="/61C72A3E/61C65C15" Ref="C?"  Part="1" 
F 0 "C?" H 3265 4746 50  0000 L CNN
F 1 "22µ" H 3265 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3188 4550 50  0001 C CNN
F 3 "~" H 3150 4700 50  0001 C CNN
F 4 "490-10476-1-ND" H 3150 4700 50  0001 C CNN "Digikey"
	1    3150 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 4500 3600 4500
Wire Wire Line
	3600 4500 3600 4550
Connection ~ 3150 4500
Wire Wire Line
	3150 4500 3150 4450
Wire Wire Line
	3150 4900 3600 4900
Wire Wire Line
	3600 4900 3600 4850
Connection ~ 3150 4900
Wire Wire Line
	3150 4900 3150 4850
Text HLabel 6300 2650 2    50   Output ~ 0
RTS
Text HLabel 6300 2750 2    50   Output ~ 0
RXD
Text HLabel 6300 3050 2    50   Output ~ 0
DTS
Text HLabel 6300 2850 2    50   Output ~ 0
TXD
Wire Wire Line
	5950 3750 6300 3750
Wire Wire Line
	5950 3850 6300 3850
Wire Wire Line
	5950 3950 6300 3950
Text HLabel 6300 3750 2    50   Output ~ 0
CHREN
Text HLabel 6300 3850 2    50   Output ~ 0
CHR0
Text HLabel 6300 3950 2    50   Output ~ 0
CHR1
$Comp
L power:+3V3 #PWR?
U 1 1 61C6BA48
P 5350 2150
AR Path="/61C6BA48" Ref="#PWR?"  Part="1" 
AR Path="/61C72A3E/61C6BA48" Ref="#PWR?"  Part="1" 
AR Path="/61D338A3/61C6BA48" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5350 2000 50  0001 C CNN
F 1 "+3V3" H 5365 2323 50  0000 C CNN
F 2 "" H 5350 2150 50  0001 C CNN
F 3 "" H 5350 2150 50  0001 C CNN
	1    5350 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2150 5350 2300
Wire Wire Line
	5450 2350 5450 2300
Wire Wire Line
	5450 2300 5350 2300
Connection ~ 5350 2300
Wire Wire Line
	5350 2300 5350 2350
$EndSCHEMATC
