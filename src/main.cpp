/*
 * BalancingBusinessCard.cpp
 *
 * Created: 11/3/2018 4:36:13 PM
 * Author : mschommer
 */ 

#include<avr/io.h>
#include<stdio.h>
#include<math.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "alphabet.h"
#include "lis3dh_STdC/driver/lis3dh_reg.h"
#include "lis3dh_STdC/driver/lis3dh_reg.c"

void ShowLine(uint16_t line) {
    PORTA = (line & 0b000011111) << 3; // LED0, LED1, LED2, LED3, LED4
    PORTB = ((line & 0b000100000) << 1) ;  // LED5
	PORTB |= ((line & 0b001000000) >> 1);  // LED6
	PORTB |= ((line & 0b010000000) >> 3);  // LED7
	PORTB |= ((line & 0b100000000) >> 5);  // LED8
}

int main()
{
	// Configuring ATTiny
	DDRA=0xff;                            // Configure PORTA as output
	CLKPR = 1<<CLKPCE;
	CLKPR = 1<<CLKPS1;                    // Set clock division to 4
	
	TCCR0B = 1<<CS02;                     // Divide clock by 256

	DDRB = 0b01111010;                    // Set LEDs on port B as output
	DDRA = 0b11111000;                    // Set LEDs on port A as output

	// Parameters
	char message[] = "MAX";	              // Message to display
	int kerning = 2;                      // Space between letters 
	int buffer = 20;                      // Space on both sides of displayed message
	uint32_t switchDebounceTime = 200;    // Time switch must debounce 
	uint8_t swingTimeTrailingAvgLen = 5;  // Trailing average number for swing time
	

	// Variable Initializations
	uint32_t timerOverflowCount = 0;      // Each tick is 0.032768s
	uint32_t totalTime = 0;               // Each tick of totalTime is 0.000128s
	uint32_t lastSwitchedTime = 0;	      // Time that the switch last changed
	// uint32_t previousTime = 0;            // Used for debugging. TODO: Remove
	long double swingTime = 2000;         // Initial guess for time to swing back and forth
	int messageIndex = 0;			      // Index of displayed message
	
	bool messageStarted = false;		  // State of message display. Starts on a change of state
	bool switchState = true;              // State of debounced tilt switch, either 0 or 1
	bool countStarted = false;		      // State of switch counter, 1 if started and 0 if not
	uint32_t switchPreviousTime = 0;      // Time of triggering switch
	
	
	// Generate Flash Pattern
	struct FlashPattern flashPattern = convertString(message, kerning);
	long double timeToWait;
	

	while(1)
	{ 
		// Calculate how many ticks each line should last
		timeToWait = swingTime / (2 * buffer + flashPattern.length);
				
		
		// Record total time since start 
		if ((TIFR & (1<<TOV0)) == (1<<TOV0)) // check if overflow flag is set
		{
			TIFR =  1<<TOV0;; //clear timer1 overflow flag
			timerOverflowCount++;
		}
		totalTime = TCNT0L + 256 * timerOverflowCount; // total time since start of uC
		
		
		// Debounce tilt switch
		if (((PINA & (1<<PINA1)) != (switchState<<PINA1)) ) // Switch triggered
		{
			// PORTA = PORTA | (1<<PA3);
			if(countStarted == false)  // If counter hasn't started yet
			{
				countStarted = true;               // Start counter
				switchPreviousTime = totalTime;    // Set counter start time
			}
			else               // If the counter has started
			{
				if ((totalTime - switchPreviousTime ) > switchDebounceTime) 
				{
					// On change of state, update trailing average
					swingTime = swingTime * (swingTimeTrailingAvgLen - 1)/swingTimeTrailingAvgLen +
								(totalTime - lastSwitchedTime) / swingTimeTrailingAvgLen;
					
					lastSwitchedTime = totalTime;
					switchState = !switchState;
					countStarted = false;			// End the counter
					messageStarted = true;			// Start message
				}
			}
		}
		else                                    // If switch is not triggered
		{
			countStarted = false;                   // End the counter
		}
		
		
		if(messageStarted)
		{
			if((totalTime - lastSwitchedTime) > (buffer * timeToWait))
			{
				if(switchState){
					// Get index of message using the time.
					messageIndex = flashPattern.length - floor((totalTime - lastSwitchedTime - buffer * timeToWait) / timeToWait);
				}
				else
				{
					// Get index of message using the time.
					messageIndex = floor((totalTime - lastSwitchedTime - buffer * timeToWait) / timeToWait);
					
				}
				if(messageIndex < flashPattern.length)
				{
					ShowLine(flashPattern.data[messageIndex]);
				}
				else // Message display finished
				{
					messageStarted = false;
					messageIndex = 0;
				}
			}	
		}
	}
}


