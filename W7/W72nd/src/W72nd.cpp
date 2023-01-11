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
        SimpleMenu menu; /* this could also be allocated from the heap */
        DecimalEdit *time = new DecimalEdit(lcd,uart, std::string("Time"),200,0,20);
        DecimalEdit *blank = new DecimalEdit(lcd,uart,std::string("Blank"),1,0,0.1);
        IntegerEdit *light = new IntegerEdit(lcd,uart, std::string("Light"),3,0);

        DigitalIoPin red(0, 25, false, true, true);
        DigitalIoPin green(0, 3, false, true, true);
        DigitalIoPin blue(1, 1, false, true, true);

        lcd->clear();
        menu.addItem(new MenuItem(time));
        menu.addItem(new MenuItem(blank));
        menu.addItem(new MenuItem(light));
        time->setValue(100);
        blank->setValue(0.9);
        light->setValue(0);
        int timer = 0;
        int delay = 0;
        bool led_status = false;
        float led_off = 0;
//        unsigned int timeout = 0;


            menu.event(MenuItem::show); // display first menu item
			/* simulate button presses */
            while(1){
            	Sleep(1);

            	led_off++;
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
            	switch (light->getValue())
            	{
            	case 0:
            		red.write(false);
            		green.write(false);
            		blue.write(false);
            		led_off = 0;
            		led_status = false;
            		break;

            	case 1:
            		green.write(false);
            		blue.write(false);
            		if(!led_status) {
            			if((led_off >= blank->getValue() * 1000) ) {
            				led_status = true;
            				red.write(true);
            				led_off = 0;
            				uart->write("shit!\r\n");

            			}
            		}
            		else if(led_status) {
            			if(led_off >= time->getValue()) {
            				led_status = false;
            				red.write(false);
            				led_off = 0;


            			}
            		}
            		break;
            	case 2:
            		red.write(false);
            		blue.write(false);
            		if(!led_status) {
            			if((led_off >= blank->getValue() * 1000) ) {
            				led_status = true;
            				green.write(true);
            				led_off = 0;


            			}
            		}
            		else if(led_status) {
            			if(led_off >= time->getValue()) {
            				led_status = false;
            				green.write(false);
            				led_off = 0;


            			}
            		}
            		break;
            	case 3:
            		red.write(false);
            		green.write(false);
            		if(!led_status) {
            			if((led_off >= blank->getValue() * 1000) ) {
            				led_status = true;
            				blue.write(true);
            				led_off = 0;


            			}
            		}
            		else if(led_status) {
            			if(led_off >= time->getValue()) {
            				led_status = false;
            				blue.write(false);
            				led_off = 0;


            			}
            		}
            		break;


            	}




            }


    return 0 ;
}
