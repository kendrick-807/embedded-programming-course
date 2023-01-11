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

#include "DigitalIoPin.h"
#include "LiquidCrystal.h"
#include <cr_section_macros.h>


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
    // TODO: insert code here
    std::string s1 = "UP    ";
    std::string s2 = "UP    ";
    std::string s3 = "UP    ";
    // Force the counter to be placed into memory

    // Enter an infinite loop, just incrementing a counter
    LiquidCrystal lcd(&rs, &en, &d4, &d5, &d6, &d7);
    // configure display geometry
    lcd.begin(16, 2);
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
//    lcd.print("Shit! Just Testing!");
    volatile int i = 0;
    while(1) {

    	if(sw1.read()){
    		s1 = "DOWN ";
    	}else{
    		s1 = "UP   ";
    	}
    	if(sw2.read()){
    		s2 = "DOWN ";
    	}else{
    		s2 = "UP   ";
    	}
    	if(sw3.read()){
    		s3 = "DOWN  ";
    	}else{
    		s3 = "UP    ";
    	}
    	//    	std::string s4 = "B1	B2    B3    \n";
    	//    	std::string s5 = s1+s2+s3;
    	//    	std::string s6 = s4 + s5;
    	//    	lcd.print(s6.c_str());

    	lcd.print("B1   B2   B3");
    	lcd.setCursor(0, 1);
    	lcd.print(s1+s2+s3);
    	i++;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
    }

    return 0 ;
}
