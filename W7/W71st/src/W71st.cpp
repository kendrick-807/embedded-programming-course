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
#include "SimpleMenu.h"
#include "IntegerEdit.h"
#include "LiquidCrystal.h"
#include "DigitalIoPin.h"
#include "DecimalEdit.h"
#include <atomic>
static volatile std::atomic_int counter;
static volatile std::atomic_int tick;
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Handle interrupt from SysTick timer
 * @return  Nothing
 */
void SysTick_Handler(void)
{
    if(counter > 0) counter--;
    tick++;
}
#ifdef __cplusplus
}
#endif
int millis(void)
{
    return tick;
}
int reset(void){
	return 0;
}
void Sleep(int ms)
{
    counter = ms;
    while(counter > 0) {
        __WFI();
    }
}
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
    LpcPinMap none = {-1, -1}; // unused pin has negative values in it
	LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
	LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
	LpcUartConfig cfg = { LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin, none, none };
	LpcUart *uart = new LpcUart(cfg);
    Chip_RIT_Init(LPC_RITIMER);
    uint32_t sysTickRate;
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / 1000);
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

    // Force the counter to be placed into memory

    // Enter an infinite loop, just incrementing a counter
    LiquidCrystal *lcd = new LiquidCrystal(&rs, &en, &d4, &d5, &d6, &d7);
    // configure display geometry
    lcd->begin(16, 2);
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd->setCursor(0, 0);
    // Print a message to the LCD.
//    lcd.print("Shit! Just Testing!");
        SimpleMenu menu; /* this could also be allocated from the heap */
        IntegerEdit *time = new IntegerEdit(lcd,uart, std::string("Time"),10,0);
        IntegerEdit *blank = new IntegerEdit(lcd,uart,std::string("Blank"),200,100);
        IntegerEdit *light = new IntegerEdit(lcd,uart, std::string("Light"),2,0);
        menu.addItem(new MenuItem(time));
        menu.addItem(new MenuItem(blank));
        menu.addItem(new MenuItem(light));
        time->setValue(5);
        blank->setValue(150);
        light->setValue(1);
        int timer = 0;
        int delay = 0;
//        unsigned int timeout = 0;


            menu.event(MenuItem::show); // display first menu item
			/* simulate button presses */
            while(1){
                       	timer = millis();

                       	if(timer == 10000 || timer == delay){
                       		if(timer != 0 ){
                           		menu.event(MenuItem::back);
                           		delay = timer + 10000;
                       		}
                       	}

                       	if(sw1.read()){
                       		delay = timer + 10000;
                       		while(sw1.read());
                       		menu.event(MenuItem::up);


                       	}

                       	if(sw2.read()){
                       		delay = timer + 10000;
                       		while(sw2.read());
                       		menu.event(MenuItem::ok);

                       	}

                       	if(sw3.read()){
                       		delay = timer + 10000;
                       		while(sw3.read());
                       		menu.event(MenuItem::down);

                       	}


                       }



    return 0 ;
}
