EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATtiny:ATtiny261A-SU U?
U 1 1 5BCB9B43
P 3100 3750
F 0 "U?" H 2470 3796 50  0000 R CNN
F 1 "ATtiny261-20SU" H 2470 3705 50  0000 R CNN
F 2 "Package_SO:SOIC-20W_7.5x12.8mm_P1.27mm" H 3100 3750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2588-8-bit-avr-microcontrollers-tinyavr-attiny261-attiny461-attiny861_datasheet.pdf" H 3100 3750 50  0001 C CNN
	1    3100 3750
	1    0    0    -1  
$EndComp
$Sheet
S 7500 3700 1600 1200
U 5BCB9C49
F0 "MotorModule" 50
F1 "motorModule.sch" 50
F2 "DIFF1" I L 7500 3800 50 
F3 "DIFF2" I L 7500 3900 50 
F4 "INA" I L 7500 4000 50 
F5 "INB" I L 7500 4100 50 
F6 "VC" I L 7500 4200 50 
F7 "VM" I L 7500 4300 50 
$EndSheet
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
ADC0
Text Label 3800 3050 0    50   ~ 0
ADC1
Text Label 3800 3850 0    50   ~ 0
SDA
Text Label 3800 4050 0    50   ~ 0
SCL
$Comp
L Device:Battery BT?
U 1 1 5BCBEFF8
P 4400 1300
F 0 "BT?" H 4508 1346 50  0000 L CNN
F 1 "Battery" H 4508 1255 50  0000 L CNN
F 2 "" V 4400 1360 50  0001 C CNN
F 3 "~" V 4400 1360 50  0001 C CNN
	1    4400 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 5BCBF44A
P 4400 1100
F 0 "#PWR?" H 4400 950 50  0001 C CNN
F 1 "+BATT" H 4415 1273 50  0000 C CNN
F 2 "" H 4400 1100 50  0001 C CNN
F 3 "" H 4400 1100 50  0001 C CNN
	1    4400 1100
	1    0    0    -1  
$EndComp
Text Notes 4600 950  0    50   ~ 0
+3V
$Comp
L power:GND #PWR?
U 1 1 5BCBF4A9
P 4400 1500
F 0 "#PWR?" H 4400 1250 50  0001 C CNN
F 1 "GND" H 4405 1327 50  0000 C CNN
F 2 "" H 4400 1500 50  0001 C CNN
F 3 "" H 4400 1500 50  0001 C CNN
	1    4400 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 5BCBF62A
P 7050 4300
F 0 "#PWR?" H 7050 4150 50  0001 C CNN
F 1 "+BATT" H 7065 4473 50  0000 C CNN
F 2 "" H 7050 4300 50  0001 C CNN
F 3 "" H 7050 4300 50  0001 C CNN
	1    7050 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 4300 7500 4300
$EndSCHEMATC
