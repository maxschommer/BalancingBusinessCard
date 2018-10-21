EESchema Schematic File Version 4
LIBS:BalancingBusinessCard-cache
EELAYER 26 0
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
Text HLabel 4300 2950 0    50   Input ~ 0
Vin
Wire Wire Line
	4600 2950 4300 2950
Text HLabel 6800 3050 2    50   Input ~ 0
Vin
$Comp
L Device:C C501
U 1 1 5BCC4233
P 4300 3100
F 0 "C501" H 4415 3146 50  0000 L CNN
F 1 "4.7uF" H 4415 3055 50  0000 L CNN
F 2 "" H 4338 2950 50  0001 C CNN
F 3 "~" H 4300 3100 50  0001 C CNN
	1    4300 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0501
U 1 1 5BCC42BA
P 4300 3250
F 0 "#PWR0501" H 4300 3000 50  0001 C CNN
F 1 "GND" H 4305 3077 50  0000 C CNN
F 2 "" H 4300 3250 50  0001 C CNN
F 3 "" H 4300 3250 50  0001 C CNN
	1    4300 3250
	1    0    0    -1  
$EndComp
$Comp
L Custom:FT440CA U?
U 1 1 5BCC411B
P 4600 2950
AR Path="/5BCC411B" Ref="U?"  Part="1" 
AR Path="/5BCC40AE/5BCC411B" Ref="U501"  Part="1" 
F 0 "U501" H 5700 3337 60  0000 C CNN
F 1 "FT440CA" H 5700 3231 60  0000 C CNN
F 2 "FRE_SOT23-5" H 5700 3190 60  0001 C CNN
F 3 "" H 4600 2950 60  0000 C CNN
	1    4600 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3050 4600 3250
Wire Wire Line
	4600 3250 4300 3250
Connection ~ 4300 3250
Text HLabel 7550 3150 2    50   Input ~ 0
Vout
$Comp
L Device:L L501
U 1 1 5BCC459A
P 7150 3150
F 0 "L501" V 7340 3150 50  0000 C CNN
F 1 "2.2uH" V 7249 3150 50  0000 C CNN
F 2 "" H 7150 3150 50  0001 C CNN
F 3 "~" H 7150 3150 50  0001 C CNN
	1    7150 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7000 3150 6800 3150
Wire Wire Line
	7300 3150 7400 3150
Wire Wire Line
	7550 3150 7550 3250
$Comp
L Device:C C503
U 1 1 5BCC46FF
P 7550 3400
F 0 "C503" H 7665 3446 50  0000 L CNN
F 1 "10uF" H 7665 3355 50  0000 L CNN
F 2 "" H 7588 3250 50  0001 C CNN
F 3 "~" H 7550 3400 50  0001 C CNN
	1    7550 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0503
U 1 1 5BCC477E
P 7550 3550
F 0 "#PWR0503" H 7550 3300 50  0001 C CNN
F 1 "GND" H 7555 3377 50  0000 C CNN
F 2 "" H 7550 3550 50  0001 C CNN
F 3 "" H 7550 3550 50  0001 C CNN
	1    7550 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2950 6800 2750
Wire Wire Line
	6800 2750 7100 2750
Wire Wire Line
	7100 2750 7100 2600
$Comp
L Device:R R501
U 1 1 5BCC4CF2
P 6800 2600
F 0 "R501" H 6870 2646 50  0000 L CNN
F 1 "100k" H 6870 2555 50  0000 L CNN
F 2 "" V 6730 2600 50  0001 C CNN
F 3 "~" H 6800 2600 50  0001 C CNN
	1    6800 2600
	1    0    0    -1  
$EndComp
Connection ~ 6800 2750
Wire Wire Line
	6800 2450 6650 2450
$Comp
L power:GND #PWR0502
U 1 1 5BCC4E33
P 6650 2450
F 0 "#PWR0502" H 6650 2200 50  0001 C CNN
F 1 "GND" H 6655 2277 50  0000 C CNN
F 2 "" H 6650 2450 50  0001 C CNN
F 3 "" H 6650 2450 50  0001 C CNN
	1    6650 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C502
U 1 1 5BCC4E79
P 7250 2600
F 0 "C502" V 6998 2600 50  0000 C CNN
F 1 "22pF" V 7089 2600 50  0000 C CNN
F 2 "" H 7288 2450 50  0001 C CNN
F 3 "~" H 7250 2600 50  0001 C CNN
	1    7250 2600
	0    1    1    0   
$EndComp
$Comp
L Device:R R502
U 1 1 5BCC4F31
P 7250 2750
F 0 "R502" V 7150 2750 50  0000 C CNN
F 1 "200k" V 7250 2750 50  0000 C CNN
F 2 "" V 7180 2750 50  0001 C CNN
F 3 "~" H 7250 2750 50  0001 C CNN
	1    7250 2750
	0    -1   -1   0   
$EndComp
Connection ~ 7100 2750
Wire Wire Line
	7400 2600 7400 2750
Wire Wire Line
	7400 2750 7400 3150
Connection ~ 7400 2750
Connection ~ 7400 3150
Wire Wire Line
	7400 3150 7550 3150
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5BCCA913
P 7550 3150
F 0 "#FLG0103" H 7550 3225 50  0001 C CNN
F 1 "PWR_FLAG" H 7550 3324 50  0000 C CNN
F 2 "" H 7550 3150 50  0001 C CNN
F 3 "~" H 7550 3150 50  0001 C CNN
	1    7550 3150
	1    0    0    -1  
$EndComp
Connection ~ 7550 3150
$EndSCHEMATC
