EESchema Schematic File Version 4
LIBS:BalancingBusinessCardLights-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
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
S 7500 2300 1600 1200
U 5BCB9BF4
F0 "LightModule" 50
F1 "lightModule.sch" 50
F2 "LED_1" I L 7500 2600 50 
F3 "LED_2" I L 7500 2700 50 
F4 "LED_3" I L 7500 2800 50 
F5 "LED_4" I L 7500 2900 50 
F6 "LED_5" I L 7500 3000 50 
F7 "LED_6" I L 7500 3100 50 
F8 "LED_7" I L 7500 3200 50 
F9 "LED_0" I L 7500 2500 50 
F10 "LED_8" I L 7500 3300 50 
$EndSheet
Text Label 3800 2950 0    50   ~ 0
SDA
Text Label 3800 3150 0    50   ~ 0
SCL
$Comp
L Device:Battery BT101
U 1 1 5BCBEFF8
P 4400 1300
F 0 "BT101" H 4508 1346 50  0000 L CNN
F 1 "Battery" H 4508 1255 50  0000 L CNN
F 2 "CustomFootprints:CR2016VP" V 4400 1360 50  0001 C CNN
F 3 "~" V 4400 1360 50  0001 C CNN
	1    4400 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0101
U 1 1 5BCBF44A
P 4400 1050
F 0 "#PWR0101" H 4400 900 50  0001 C CNN
F 1 "+BATT" H 4415 1223 50  0000 C CNN
F 2 "" H 4400 1050 50  0001 C CNN
F 3 "" H 4400 1050 50  0001 C CNN
	1    4400 1050
	1    0    0    -1  
$EndComp
Text Notes 4600 950  0    50   ~ 0
+3V
$Comp
L power:GND #PWR0102
U 1 1 5BCBF4A9
P 4400 1500
F 0 "#PWR0102" H 4400 1250 50  0001 C CNN
F 1 "GND" H 4405 1327 50  0000 C CNN
F 2 "" H 4400 1500 50  0001 C CNN
F 3 "" H 4400 1500 50  0001 C CNN
	1    4400 1500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even ICSP1
U 1 1 5BCBEC7A
P 3000 5850
F 0 "ICSP1" H 3050 6050 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 3050 5650 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 3000 5850 50  0001 C CNN
F 3 "~" H 3000 5850 50  0001 C CNN
	1    3000 5850
	1    0    0    -1  
$EndComp
Text Label 3300 5850 0    50   ~ 0
MOSI
$Comp
L power:GND #PWR0107
U 1 1 5BCBF839
P 3300 5950
F 0 "#PWR0107" H 3300 5700 50  0001 C CNN
F 1 "GND" V 3305 5822 50  0000 R CNN
F 2 "" H 3300 5950 50  0001 C CNN
F 3 "" H 3300 5950 50  0001 C CNN
	1    3300 5950
	0    -1   -1   0   
$EndComp
Text Label 2800 5750 2    50   ~ 0
MISO
Text Label 2800 5850 2    50   ~ 0
SCK
Text Label 2800 5950 2    50   ~ 0
RESET
Text Label 3800 4550 0    50   ~ 0
RESET
$Comp
L power:GND #PWR0108
U 1 1 5BCCA97D
P 3100 4950
F 0 "#PWR0108" H 3100 4700 50  0001 C CNN
F 1 "GND" H 3105 4777 50  0000 C CNN
F 2 "" H 3100 4950 50  0001 C CNN
F 3 "" H 3100 4950 50  0001 C CNN
	1    3100 4950
	1    0    0    -1  
$EndComp
Text Label 4900 3850 0    50   ~ 0
MOSI
Text Label 4100 3950 0    50   ~ 0
MISO
Text Label 4100 4050 0    50   ~ 0
SCK
$Sheet
S 7500 950  1600 1100
U 5BCBF6E4
F0 "Accelerometer" 50
F1 "LIS3DHTR.sch" 50
F2 "SDA" I L 7500 1300 50 
F3 "SCL" I L 7500 1400 50 
$EndSheet
Text Label 7175 1300 2    50   ~ 0
SDA
Text Label 6825 1400 2    50   ~ 0
SCL
Wire Wire Line
	4400 1100 4400 1050
Connection ~ 4400 1100
Text Label 7500 2500 2    50   ~ 0
LED_0
Text Label 7500 2600 2    50   ~ 0
LED_1
Text Label 7500 2700 2    50   ~ 0
LED_2
Text Label 7500 2800 2    50   ~ 0
LED_3
Text Label 7500 2900 2    50   ~ 0
LED_4
Text Label 7500 3000 2    50   ~ 0
LED_5
Text Label 7500 3100 2    50   ~ 0
LED_6
Text Label 7500 3200 2    50   ~ 0
LED_7
Text Label 7500 3300 2    50   ~ 0
LED_8
Text Label 3800 3250 0    50   ~ 0
LED_0
Text Label 3800 3350 0    50   ~ 0
LED_1
Text Label 3800 3450 0    50   ~ 0
LED_2
Text Label 3800 3550 0    50   ~ 0
LED_3
Text Label 3800 3650 0    50   ~ 0
LED_4
Text Label 3800 4450 0    50   ~ 0
LED_5
Text Label 3800 4350 0    50   ~ 0
LED_6
Text Label 3800 4250 0    50   ~ 0
LED_7
Text Label 3800 4150 0    50   ~ 0
LED_8
Wire Wire Line
	3100 2650 3100 2575
Wire Wire Line
	3100 2400 3450 2400
$Comp
L Device:C C101
U 1 1 5BCC392A
P 3600 2400
F 0 "C101" V 3852 2400 50  0000 C CNN
F 1 "10uF" V 3761 2400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3638 2250 50  0001 C CNN
F 3 "~" H 3600 2400 50  0001 C CNN
	1    3600 2400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5BCC3A23
P 3750 2400
F 0 "#PWR0112" H 3750 2150 50  0001 C CNN
F 1 "GND" H 3755 2227 50  0000 C CNN
F 2 "" H 3750 2400 50  0001 C CNN
F 3 "" H 3750 2400 50  0001 C CNN
	1    3750 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4050 4100 4050
Wire Wire Line
	3800 3950 4100 3950
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5BCC0D87
P 4050 1100
F 0 "#FLG0101" H 4050 1175 50  0001 C CNN
F 1 "PWR_FLAG" H 4050 1274 50  0000 C CNN
F 2 "" H 4050 1100 50  0001 C CNN
F 3 "~" H 4050 1100 50  0001 C CNN
	1    4050 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 1100 4400 1100
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5BCC114E
P 4050 1400
F 0 "#FLG0102" H 4050 1475 50  0001 C CNN
F 1 "PWR_FLAG" H 4050 1574 50  0000 C CNN
F 2 "" H 4050 1400 50  0001 C CNN
F 3 "~" H 4050 1400 50  0001 C CNN
	1    4050 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 1450 4050 1400
$Comp
L power:GND #PWR0134
U 1 1 5BCC13FA
P 4050 1450
F 0 "#PWR0134" H 4050 1200 50  0001 C CNN
F 1 "GND" H 4055 1277 50  0000 C CNN
F 2 "" H 4050 1450 50  0001 C CNN
F 3 "" H 4050 1450 50  0001 C CNN
	1    4050 1450
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATtiny:ATtiny261A-MU U101
U 1 1 5C0B1B62
P 3100 3750
F 0 "U101" H 2459 3796 50  0000 R CNN
F 1 "ATtiny261A-MU" H 2459 3705 50  0000 R CNN
F 2 "Housings_DFN_QFN:QFN-32-1EP_5x5mm_Pitch0.5mm" H 3100 3750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc8197.pdf" H 3100 3750 50  0001 C CNN
	1    3100 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2650 3200 2575
Wire Wire Line
	3200 2575 3100 2575
Connection ~ 3100 2575
Wire Wire Line
	3100 2575 3100 2400
Wire Wire Line
	3100 4850 3100 4900
Wire Wire Line
	3200 4850 3200 4900
Wire Wire Line
	3200 4900 3100 4900
Connection ~ 3100 4900
Wire Wire Line
	3100 4900 3100 4950
$Sheet
S 1050 1350 1350 325 
U 5C0D2666
F0 "3V3Regulator" 50
F1 "3V3Regulator.sch" 50
F2 "VIN" I R 2400 1425 50 
F3 "VOUT" I R 2400 1550 50 
$EndSheet
$Comp
L power:+3V3 #PWR0103
U 1 1 5C0EE9D9
P 2750 1550
F 0 "#PWR0103" H 2750 1400 50  0001 C CNN
F 1 "+3V3" H 2765 1723 50  0000 C CNN
F 2 "" H 2750 1550 50  0001 C CNN
F 3 "" H 2750 1550 50  0001 C CNN
	1    2750 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1550 2750 1550
$Comp
L power:+BATT #PWR0104
U 1 1 5C0EEBFA
P 2525 1425
F 0 "#PWR0104" H 2525 1275 50  0001 C CNN
F 1 "+BATT" H 2540 1598 50  0000 C CNN
F 2 "" H 2525 1425 50  0001 C CNN
F 3 "" H 2525 1425 50  0001 C CNN
	1    2525 1425
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1425 2525 1425
$Comp
L power:+3V3 #PWR0105
U 1 1 5C0EF8B9
P 3100 2400
F 0 "#PWR0105" H 3100 2250 50  0001 C CNN
F 1 "+3V3" H 3115 2573 50  0000 C CNN
F 2 "" H 3100 2400 50  0001 C CNN
F 3 "" H 3100 2400 50  0001 C CNN
	1    3100 2400
	1    0    0    -1  
$EndComp
Connection ~ 3100 2400
$Comp
L power:+3V3 #PWR0110
U 1 1 5C0EF953
P 3300 5750
F 0 "#PWR0110" H 3300 5600 50  0001 C CNN
F 1 "+3V3" H 3315 5923 50  0000 C CNN
F 2 "" H 3300 5750 50  0001 C CNN
F 3 "" H 3300 5750 50  0001 C CNN
	1    3300 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R103
U 1 1 5C0ECCA8
P 7250 1025
F 0 "R103" H 7320 1071 50  0000 L CNN
F 1 "10k" H 7320 980 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7180 1025 50  0001 C CNN
F 3 "~" H 7250 1025 50  0001 C CNN
	1    7250 1025
	1    0    0    -1  
$EndComp
$Comp
L Device:R R102
U 1 1 5C0ECD2E
P 6900 1025
F 0 "R102" H 6970 1071 50  0000 L CNN
F 1 "10k" H 6970 980 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6830 1025 50  0001 C CNN
F 3 "~" H 6900 1025 50  0001 C CNN
	1    6900 1025
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0109
U 1 1 5C0ED0B8
P 6900 875
F 0 "#PWR0109" H 6900 725 50  0001 C CNN
F 1 "+3V3" H 6915 1048 50  0000 C CNN
F 2 "" H 6900 875 50  0001 C CNN
F 3 "" H 6900 875 50  0001 C CNN
	1    6900 875 
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0137
U 1 1 5C0ED0E1
P 7250 875
F 0 "#PWR0137" H 7250 725 50  0001 C CNN
F 1 "+3V3" H 7265 1048 50  0000 C CNN
F 2 "" H 7250 875 50  0001 C CNN
F 3 "" H 7250 875 50  0001 C CNN
	1    7250 875 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1400 6900 1175
Wire Wire Line
	6900 1400 7500 1400
Wire Wire Line
	6900 1400 6825 1400
Connection ~ 6900 1400
Wire Wire Line
	7250 1300 7250 1175
Wire Wire Line
	7250 1300 7500 1300
Wire Wire Line
	7250 1300 7175 1300
Connection ~ 7250 1300
$Comp
L Custom:Test_Point TP101
U 1 1 5C7DEA24
P 5250 2750
F 0 "TP101" V 5204 2938 50  0000 L CNN
F 1 "TestPoint" V 5295 2938 50  0000 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 5450 2750 50  0001 C CNN
F 3 "~" H 5450 2750 50  0001 C CNN
	1    5250 2750
	0    1    1    0   
$EndComp
$Comp
L Custom:Test_Point TP102
U 1 1 5C7DEC98
P 5250 2950
F 0 "TP102" V 5204 3138 50  0000 L CNN
F 1 "TestPoint" V 5295 3138 50  0000 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 5450 2950 50  0001 C CNN
F 3 "~" H 5450 2950 50  0001 C CNN
	1    5250 2950
	0    1    1    0   
$EndComp
Text Label 5250 2750 2    50   ~ 0
SDA
Text Label 5250 2950 2    50   ~ 0
SCL
$Comp
L Connector_Generic:Conn_02x01 J101
U 1 1 5C7DF1A3
P 5400 3450
F 0 "J101" H 5450 3667 50  0000 C CNN
F 1 "Conn_02x01" H 5450 3576 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5400 3450 50  0001 C CNN
F 3 "~" H 5400 3450 50  0001 C CNN
	1    5400 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0106
U 1 1 5C7DF23F
P 5700 3450
F 0 "#PWR0106" H 5700 3300 50  0001 C CNN
F 1 "+3V3" H 5715 3623 50  0000 C CNN
F 2 "" H 5700 3450 50  0001 C CNN
F 3 "" H 5700 3450 50  0001 C CNN
	1    5700 3450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5C7DF2BD
P 5200 3450
F 0 "#PWR0111" H 5200 3200 50  0001 C CNN
F 1 "GND" H 5205 3277 50  0000 C CNN
F 2 "" H 5200 3450 50  0001 C CNN
F 3 "" H 5200 3450 50  0001 C CNN
	1    5200 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5C7E1777
P 8000 4600
F 0 "#PWR0114" H 8000 4350 50  0001 C CNN
F 1 "GND" H 8005 4427 50  0000 C CNN
F 2 "" H 8000 4600 50  0001 C CNN
F 3 "" H 8000 4600 50  0001 C CNN
	1    8000 4600
	1    0    0    -1  
$EndComp
Text Label 8000 4300 1    50   ~ 0
TOUCH_REVEIVE
$Comp
L Device:R R101
U 1 1 5C7E1882
P 7750 4300
F 0 "R101" V 7543 4300 50  0000 C CNN
F 1 "976k" V 7634 4300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7680 4300 50  0001 C CNN
F 3 "~" H 7750 4300 50  0001 C CNN
	1    7750 4300
	0    1    1    0   
$EndComp
Text Label 4400 3850 1    50   ~ 0
TOUCH_SEND
Text Label 3800 3050 0    50   ~ 0
TOUCH_RECEIVE
Wire Wire Line
	3800 3850 4900 3850
Text Label 7325 4300 2    50   ~ 0
TOUCH_SEND
Wire Wire Line
	7325 4300 7600 4300
$Comp
L Device:C C?
U 1 1 5C837217
P 8000 4450
F 0 "C?" H 8115 4496 50  0000 L CNN
F 1 "22pf" H 8115 4405 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 8038 4300 50  0001 C CNN
F 3 "~" H 8000 4450 50  0001 C CNN
	1    8000 4450
	1    0    0    -1  
$EndComp
$Comp
L Custom:Test_Point BTN?
U 1 1 5C837578
P 8400 4300
F 0 "BTN?" H 8458 4420 50  0000 L CNN
F 1 "Cap Sense" H 8458 4329 50  0000 L CNN
F 2 "CustomFootprints:CAP_TOUCH" H 8600 4300 50  0001 C CNN
F 3 "~" H 8600 4300 50  0001 C CNN
	1    8400 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 4300 8000 4300
Connection ~ 8000 4300
Wire Wire Line
	8000 4300 8400 4300
$EndSCHEMATC
