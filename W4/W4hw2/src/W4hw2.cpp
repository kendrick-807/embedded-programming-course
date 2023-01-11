/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include "DigitalIoPin.h"
#include "LpcUart.h"
#include "I2C.h"
#include <string>


/* I2C clock is set to 1.8MHz */
#define I2C_CLK_DIVIDER         (1440)
/* 100KHz I2C bit-rate */
#define I2C_BITRATE         (50000)
/* Standard I2C mode */
#define I2C_MODE    (0)
#define I2C_TEMP_ADDR_7BIT 	(0x4A)
#include <atomic>

static volatile std::atomic_int tick;
static volatile std::atomic_int counter;
#ifdef __cplusplus
extern "C" {
#endif
/**
* @brief Handle interrupt from SysTick timer
* @return Nothing
*/
void SysTick_Handler(void)
{
    if(counter > 0) counter--;
    tick++;
}
void Sleep(int ms)
{
    counter = ms;
    while(counter > 0) {
        __WFI();
    }
}
int millis(void)
{
    return tick;
}
int reset(void){
	return 0;
}
#ifdef __cplusplus
}
#endif
#define TICKRATE_HZ      (1000)

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
//static void setupI2CMaster()
//{
//	/* Enable I2C clock and reset I2C peripheral - the boot ROM does not
//	   do this */
//	Chip_I2C_Init(LPC_I2C0);
//
//	/* Setup clock rate for I2C */
//	Chip_I2C_SetClockDiv(LPC_I2C0, I2C_CLK_DIVIDER);
//
//	/* Setup I2CM transfer rate */
//	Chip_I2CM_SetBusSpeed(LPC_I2C0, I2C_BITRATE);
//
//	/* Enable Master Mode */
//	Chip_I2CM_Enable(LPC_I2C0);
//}
//
//static void Init_I2C_PinMux(void)
//{
//#if defined(BOARD_NXP_LPCXPRESSO_1549)
//	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 22, IOCON_DIGMODE_EN | I2C_MODE);
//	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 23, IOCON_DIGMODE_EN | I2C_MODE);
//	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SCL);
//	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SDA);
//	Chip_I2C_Init(LPC_I2C0);
//#else
//#error "No I2C Pin Muxing defined for this example"
//#endif
//}
//
//
//static bool SetupXferRecAndExecute(uint8_t devAddr,
//								   uint8_t *txBuffPtr,
//								   uint16_t txSize,
//								   uint8_t *rxBuffPtr,
//								   uint16_t rxSize)
//{
//	/* Setup I2C transfer record */
//	i2cmXferRec.slaveAddr = devAddr;
//	i2cmXferRec.status = 0;
//	i2cmXferRec.txSz = txSize;
//	i2cmXferRec.rxSz = rxSize;
//	i2cmXferRec.txBuff = txBuffPtr;
//	i2cmXferRec.rxBuff = rxBuffPtr;
//
//	Chip_I2CM_XferBlocking(LPC_I2C0, &i2cmXferRec);
//	if(i2cmXferRec.status == I2CM_STATUS_OK){
//		return true;
//	}else {
//		return false;
//	}
//}
//
//static void ReadTemperatureI2CM(void)
//{
//
//}
int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif
    LpcPinMap none = {-1, -1}; // unused pin has negative values in it
	LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
	LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
	LpcUartConfig cfg = { LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin, none, none };
	LpcUart uart(cfg);
    uint32_t sysTickRate;
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / 1000);
    // TODO: insert code here
    DigitalIoPin sw3(1, 9 ,true ,true, true);
    // Force the counter to be placed into memory
    // Enter an infinite loop, just incrementing a counter
	std::string str;
	I2C i2c_temp((uint8_t)0x4A);

	    uint8_t read = 0x00;
	    uint8_t temperature[2];

	    int time =0;
	    int timestamp = 0;
	    int sample = 0;
	    int newTime = 0;
	    uint8_t standby = 0x80;
	    uint8_t normal = 0x00;
	    uint8_t control = 0x01;
	    uint8_t ready = 0x40;
//	    vehicle1[L"id"] = json::value::string(L"35092_35092_353");
//	    vehicle1[L"x"] = json::value::number(6.988270);
//	    vehicle1[L"y"] = json::value::number(50.872139);

	    while(1){

	    	time = millis();
	    	timestamp = millis();

	    	if(time == 5000 || time == newTime){
	    		if(time != 0){
	    			//    	    		   transmit[0] = 0x01;
	    			//    	    		   transmit[1] = 0x80;
	    			if( i2c_temp.read(control, &read, 1) && (read & standby) ) {
	    				if(!i2c_temp.write(control, &normal, 1)){
	    					uart.write("STANDBY STILL ON!\r\n");
	    				}
	    				else {
	    					uart.write("STANBY MODE OFF\r\n");
	    				}
	    			}else if( i2c_temp.read(control, &read, 1) && !(read & standby)){
	    				uart.write("STANBY MODE ON\r\n");
	    			}
	    		}
//    	    		   transmit_s = 2;
//    	    		   read = 0;
//    	    		   read_s = 1;
//    	    		  i2c_temp.SetupXferRecAndExecute(I2C_TEMP_ADDR_7BIT,transmit, transmit_s, &read, read_s);
//    	    		  uart.write("STANDBY MODE ON\r\n");
//    	    		  standby = true;
    	    }

    	    if(sw3.read()){
    	    	if( i2c_temp.read(control, &read, 1) && !(read & standby)) {
    	    		if(!i2c_temp.write(control, &normal, 1)){
    	    			uart.write("STANDBY STILL ON!\r\n");
    	    		}
    	    		else {
    	    			uart.write("STANBY MODE OFF\r\n");
    	    		}
    	    	}

    	    	while(sw3.read());


    	    	//				transmit[0] = 0x01;
    	    	//				transmit_s = 1;
    	    	//				read = 0;
    	    	//				read_s = 1;
    	    	//				i2c_temp.SetupXferRecAndExecute(I2C_TEMP_ADDR_7BIT,transmit, transmit_s, &read, read_s);

    	    	//	    			uart.write("MODE IS %s \r\n",readStatus);


    	    	if(i2c_temp.read(control,&read,1)){

    	    		if((read & ready) && !(read & standby)) {

    	    			if(i2c_temp.read(normal,temperature,1)){
    	    				int8_t temp_int = ( temperature[0] ^ 0x80 ) - 0x80;
    	    				sample +=1;
    	    				uart.write("{\n\r\"samplenr\": ");
    	    				uart.write(std::to_string(sample).c_str());
    	    				uart.write(",\n\r\"timestamp\": ");
    	    				uart.write(std::to_string(timestamp).c_str());
    	    				uart.write(",\n\r\"temperature\": ");
    	    				uart.write(std::to_string(temp_int).c_str());
    	    				uart.write("\r\n}\r\n");
    	    				Sleep(5);
    	    				newTime  = time +5000 ;
    	    			}
    	    		}
    	    	}else if(read & standby) {
    	    		uart.write("STANBY MODE IS STILL ON!\r\n");
    	    	}







    	    }

    	    //
	    }
        __asm volatile ("nop");
        return 0 ;

}
