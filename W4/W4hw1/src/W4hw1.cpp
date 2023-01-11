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

static I2CM_XFER_T  i2cmXferRec;
/* I2C clock is set to 1.8MHz */
#define I2C_CLK_DIVIDER         (1440)
/* 100KHz I2C bit-rate */
#define I2C_BITRATE         (50000)
/* Standard I2C mode */
#define I2C_MODE    (0)
#define I2C_TEMP_ADDR_7BIT 	(0x4A)
#include <atomic>

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
}
#ifdef __cplusplus
}
#endif
void Sleep(int ms)
{
    counter = ms;
    while(counter > 0) {
        __WFI();
    }
}


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
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
	std::string str;
	I2C i2c_temp(I2C_TEMP_ADDR_7BIT , I2C_BITRATE ,I2C_CLK_DIVIDER );
	 unsigned int flipper = 0;
	    uint8_t transmit[2] = {1, 0};
	    uint16_t transmit_s = 1;
	    uint8_t read = 0;
	    uint16_t read_s = 1;
	    char mes[127];
	    while(1){
       if(sw3.read()){
       	while (sw3.read());
       	        	uint8_t temperature[2];
       	        	uint8_t lm75TempRegisterAddress = 0;
//       	        	i2c_temp.SetupXferRecAndExecute(I2C_TEMP_ADDR_7BIT,transmit, transmit_s, &read, read_s);
//       	        	uart.write(std::to_string(read).c_str());
       	        	bool readStatus = i2c_temp.transaction(I2C_TEMP_ADDR_7BIT ,&lm75TempRegisterAddress, 1,temperature, 2);
       	        	if(readStatus){
       	        		uart.write("TRANSACTION SUCCEDDED!\r\n");
       	        		int8_t int_part = ( temperature[0] ^ 0x80 ) - 0x80;
       	        		uart.write(std::to_string(int_part).c_str());
       	        		uart.write("C \r\n");
       	        		Sleep(5);
       	        		}else if(!readStatus){
       	        			 uart.write("Error reading temperature");
       	        		}

       }

//
   }
        __asm volatile ("nop");
        return 0 ;
}



