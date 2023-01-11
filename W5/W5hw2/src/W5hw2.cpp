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
#include <ctime>
#include <cr_section_macros.h>
#include "RealTimeClock.h"
#include "DigitalIoPin.h"
#include "LiquidCrystal.h"
static RealTimeClock *rtc;
#ifdef __cplusplus
extern "C" {
#endif
/**
* @brief Handle interrupt from SysTick timer
* @return Nothing
*/
void SysTick_Handler(void)
{
if(rtc != NULL) rtc->tick();
// you may add you own stuff here, for example the sleep counter
}
#ifdef __cplusplus
}
#endif

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

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
    uint32_t sysTickRate;
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / 1000);

    RealTimeClock clk(1000);
    rtc = &clk;
    Chip_RIT_Init(LPC_RITIMER);
    DigitalIoPin rs(0, 8, false, false, false);
    DigitalIoPin en(1, 6, false, false, false);
    DigitalIoPin d4(1, 8, false, false, false);
    DigitalIoPin d5(0, 5, false, false, false);
    DigitalIoPin d6(0, 6, false, false, false);
    DigitalIoPin d7(0, 7, false, false, false);
    DigitalIoPin sw1(0, 17 ,true ,true, true);
    DigitalIoPin sw2(1, 11 ,true ,true, true);
    DigitalIoPin sw3(1, 9 ,true ,true, true);
    LiquidCrystal lcd(&rs, &en, &d4, &d5, &d6, &d7);
    tm currentTime;
    // configure display geometry
    lcd.begin(16, 2);
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 0);
    // TODO: insert code here
    char str[33];
    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
    	__WFI();
    	clk.gettime(&currentTime);
    	snprintf(str,33,"%2d:%02d:%02d       ",currentTime.tm_hour,currentTime.tm_min,currentTime.tm_sec);
    	lcd.print(str);
        lcd.setCursor(0, 0);
        i++ ;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}
