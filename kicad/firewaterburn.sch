EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 8350 3400 950  1050
U 61C10703
F0 "ntc probe" 50
F1 "ntc.sch" 50
F2 "probe6" O L 8350 4300 50 
F3 "probe3" O L 8350 3850 50 
F4 "probe2" O L 8350 3700 50 
F5 "probe1" O L 8350 3550 50 
F6 "probe4" O L 8350 4000 50 
F7 "probe5" O L 8350 4150 50 
$EndSheet
$Sheet
S 2700 1150 1650 1300
U 61C2272B
F0 "power unit" 50
F1 "power.sch" 50
$EndSheet
$Sheet
S 5200 3350 1750 1500
U 61C72A3E
F0 "mcu_n_tft" 50
F1 "mcu_n_tft.sch" 50
$EndSheet
$Sheet
S 2750 3300 1600 1550
U 61D338A3
F0 "usb_uart" 50
F1 "usb_uart.sch" 50
$EndSheet
Wire Wire Line
	1950 2750 2200 2750
Wire Wire Line
	1950 2850 2200 2850
Text Label 2200 2750 2    50   ~ 0
D-
Text Label 2200 2850 2    50   ~ 0
D+
Wire Wire Line
	1350 3750 1350 3900
Wire Wire Line
	1950 2250 2050 2250
NoConn ~ 1950 2450
NoConn ~ 1950 2550
$Comp
L power:+5V #PWR?
U 1 1 61D526AC
P 2050 2050
AR Path="/61D526AC" Ref="#PWR?"  Part="1" 
AR Path="/61D338A3/61D526AC" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2050 1900 50  0001 C CNN
F 1 "+5V" H 2065 2223 50  0000 C CNN
F 2 "" H 2050 2050 50  0001 C CNN
F 3 "" H 2050 2050 50  0001 C CNN
	1    2050 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 2050 2050 2250
$Comp
L power:GND #PWR?
U 1 1 61D526B3
P 1350 3900
AR Path="/61D526B3" Ref="#PWR?"  Part="1" 
AR Path="/61D338A3/61D526B3" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1350 3650 50  0001 C CNN
F 1 "GND" H 1355 3727 50  0000 C CNN
F 2 "" H 1350 3900 50  0001 C CNN
F 3 "" H 1350 3900 50  0001 C CNN
	1    1350 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61D526B9
P 1050 3900
AR Path="/61D526B9" Ref="#PWR?"  Part="1" 
AR Path="/61D338A3/61D526B9" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1050 3650 50  0001 C CNN
F 1 "GND" H 1055 3727 50  0000 C CNN
F 2 "" H 1050 3900 50  0001 C CNN
F 3 "" H 1050 3900 50  0001 C CNN
	1    1050 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 3900 1050 3750
$Comp
L z_connector:USB_C_Plug_USB2.0 P?
U 1 1 61D5FC46
P 1350 2850
F 0 "P?" H 1457 3717 50  0000 C CNN
F 1 "USB_C_Plug_USB2.0" H 1457 3626 50  0000 C CNN
F 2 "Connector_USB:USB_C_Receptacle_Amphenol_12401610E4-2A" H 1500 2850 50  0001 C CNN
F 3 "" H 1500 2850 50  0001 C CNN
F 4 "12401610E4#2A" H 1350 2850 50  0001 C CNN "Digikey"
	1    1350 2850
	1    0    0    -1  
$EndComp
NoConn ~ 1950 3200
NoConn ~ 1950 3300
$EndSCHEMATC
