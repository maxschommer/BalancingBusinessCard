/*
 * BalancingBusinessCard.cpp
 *
 * Created: 11/3/2018 4:36:13 PM
 * Author : mschommer
 */ 
// #define F_CPU 2000000UL  // 2 MHz for delay

#include<avr/io.h>
#include<stdio.h>
#include<math.h>
// #include <util/twi.h>
#include "alphabet.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "TinyWireM.h"
// #include "TinyWireM.cpp"
#include "USI_TWI_Master.h"
// #include "USI_TWI_Master.cpp"

// #include "lis3dh_reg.h"
// #include "lis3dh_reg.c"


#define LIS3DHTR_ADDR   0x33              // 7 bit I2C address for LIS3DHTR accelerometer sensor


//void Init_ACC(){ // Setup the LIS3DHTR
	//TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	//TinyWireM.send(0xAC);                 // Access Command Register
	//TinyWireM.send(0b00000001);            // Using one-shot mode for battery savings
	////TinyWireM.send(B00000000);          // if setting continious mode for fast reads
	//TinyWireM.endTransmission();          // Send to the slave
//}

void ShowLine(uint16_t line) {
    PORTA = (line & 0b000011111) << 3; // LED0, LED1, LED2, LED3, LED4
    PORTB = ((line & 0b000100000) << 1) ;  // LED5
	PORTB |= ((line & 0b001000000) >> 1);  // LED6
	PORTB |= ((line & 0b010000000) >> 3);  // LED7
	PORTB |= ((line & 0b100000000) >> 5);  // LED8
}

int lis3dhReadInt(unsigned char address)
{
	unsigned char msb, lsb;
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	TinyWireM.send(address);
	TinyWireM.endTransmission();
	TinyWireM.requestFrom(LIS3DHTR_ADDR, 2);
	while(TinyWireM.available()<2);
	msb = TinyWireM.receive();
	lsb = TinyWireM.receive();
	return (int) msb<<8 | lsb;
}

static int32_t modifyPointer(uint8_t *bufp)
{
	bufp[0] = 0b10101010;
}

/* Private functions ---------------------------------------------------------*/
/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
static void platform_init(void);

/* Private variables ---------------------------------------------------------*/
// static axis3bit16_t data_raw_acceleration;
// static axis1bit16_t data_raw_temperature;
static float acceleration_mg[3];
static float temperature_degC;
static uint8_t whoamI;
static uint8_t tx_buffer[1000];


int main()
{
	
	
	// Configuring ATTiny
	DDRA=0xff;                            // Configure PORTA as output
	//CLKPR = 1<<CLKPCE;
	//CLKPR = 1<<CLKPS1;                    // Set clock division to 4

	TCCR0B = 1<<CS02;                     // Divide clock by 256

	USICR = 1<<USIWM1;                    // Enable Two-Wire mode of USI register
	
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
	
	//
	//TinyWireM.begin();                    // initialize I2C lib
	//
	/*
	*  Initialize mems driver interface
	*/
	//lis3dh_ctx_t dev_ctx;
//
	//dev_ctx.write_reg = platform_write;
	//dev_ctx.read_reg = platform_read;
	//dev_ctx.handle = 0; 
	//

	//lis3dh_device_id_get(0, &whoamI);
	//if (whoamI != LIS3DH_ID)
	//{
		//while(1)
		//{
					//PORTA = PORTA | 1<<PA5;
					//_delay_ms(5);
					//PORTA = PORTA & ~(1<<PA5);
					//_delay_ms(100);
		//}
	//}
	//else
	//{
		//while(1)
		//{
		//PORTA = PORTA | 1<<PA6;
		//_delay_ms(5);
		//PORTA = PORTA & ~(1<<PA6);
		//_delay_ms(1000);
		//}
	//}
//
	//int xL; 
	//
	//xL = lis3dhReadInt(0x1E);
	//dev_ctx.read_reg(0, 0x0F, &xL, 1);
	
	
	
	// modifyPointer(&xL);
	//TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	//TinyWireM.send(0x07);                 // read ctrl_reg_0
	//
	//TinyWireM.endTransmission();          // Send 1 byte to the slave
	//_delay_ms(10);
	//TinyWireM.requestFrom(LIS3DHTR_ADDR,1); // Request 1 byte from slave
	// xL = TinyWireM.read();          // get the temperature
	
	//if(xL ==  0)
	//{
		//PORTA = PORTA | 1<<PA3;
	//}
  ///*
   //*  Enable Block Data Update
   //*/
  //lis3dh_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
//
  ///*
   //* Set Output Data Rate to 1Hz
   //*/
  //lis3dh_data_rate_set(&dev_ctx, LIS3DH_ODR_1Hz);
//
  ///*
   //* Set full scale to 2g
   //*/  
  //lis3dh_full_scale_set(&dev_ctx, LIS3DH_2g);
//
  ///*
   //* Enable temperature sensor
   //*/   
  //lis3dh_aux_adc_set(&dev_ctx, LIS3DH_AUX_ON_TEMPERATURE);
//
  ///*
   //* Set device in continuous mode with 12 bit resolution.
   //*/   
  //lis3dh_operating_mode_set(&dev_ctx, LIS3DH_HR_12bit);
  //

	// Generate Flash Pattern
	struct FlashPattern flashPattern = convertString(message, kerning);
	long double timeToWait;
	
	int byteCount = 0;

	while(1)
	{ 
		////////////////////////////////////////////////// BEGIN TEST
    //lis3dh_reg_t reg;
//
    ///*
     //* Read output only if new value available
     //*/
    //lis3dh_xl_data_ready_get(&dev_ctx, &reg.byte);
    //if (reg.byte)
    //{
      ///* Read accelerometer data */
      //memset(data_raw_acceleration.u8bit, 0x00, 3*sizeof(int16_t));
      //lis3dh_acceleration_raw_get(&dev_ctx, data_raw_acceleration.u8bit);
      //acceleration_mg[0] =
        //lis3dh_from_fs2_hr_to_mg(data_raw_acceleration.i16bit[0]);
      //acceleration_mg[1] =
        //lis3dh_from_fs2_hr_to_mg(data_raw_acceleration.i16bit[1]);
      //acceleration_mg[2] =
        //lis3dh_from_fs2_hr_to_mg(data_raw_acceleration.i16bit[2]);
		//PORTA = PORTA | 1<<PA3;
	//}
	//else
	//{
		//PORTA = PORTA | 1<<PA4;
	//}
	//if(byteCount > 7){
		//continue;
	//}
	//
	//if ((xL & 1) == 1)
	//{
		//
		//PORTA = PORTA | 1<<PA4;
		//_delay_ms(10);
		//PORTA = PORTA & ~(1<<PA4);
		//_delay_ms(1000);
	//} 
	//else
	//{
		//PORTA = PORTA | 1<<PA3;
		//_delay_ms(10);
		//PORTA = PORTA & ~(1<<PA3);
		//_delay_ms(1000);
	//}
	//byteCount ++;
	//xL = xL>>1;
		////////////////////////////////////////////////// END TEST
		
		
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



/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,
                              uint16_t len)
{
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);	
	TinyWireM.send(reg);                 // Access Register
	TinyWireM.write(bufp, len);
	TinyWireM.endTransmission(LIS3DHTR_ADDR);

  return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	TinyWireM.write(reg);                 // Register to start at
	TinyWireM.endTransmission(LIS3DHTR_ADDR);
	
	_delay_ms(1);
	TinyWireM.requestFrom(LIS3DHTR_ADDR, len); // Request len bytes from slave
	
	uint8_t inc = 0;                           // Counter for writing to bufp  
	while (TinyWireM.available())
	{
		bufp[inc] = TinyWireM.read();
		inc ++;
	}
  return 0;
}


