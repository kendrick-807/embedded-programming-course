#include "DigitalIoPin.h"
#include "chip.h"
#include "board.h"



DigitalIoPin::DigitalIoPin(int port, int pin, bool input, bool pullup, bool invert ): port(port), pin(pin), input(input), pullup(pullup), invert(invert){

	if(input == true){
		if(pullup == true && invert == true){
			Chip_IOCON_PinMuxSet(LPC_IOCON, port,pin, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
		}else if(invert == true && pullup == false){
			Chip_IOCON_PinMuxSet(LPC_IOCON, port,pin, (IOCON_MODE_PULLDOWN | IOCON_DIGMODE_EN | IOCON_INV_EN));
		}else if(invert == false && pullup == true){
			Chip_IOCON_PinMuxSet(LPC_IOCON, port,pin, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN ));
		}
		Chip_GPIO_SetPinDIRInput(LPC_GPIO,port,pin);
	}else if(input == false){
		Chip_GPIO_SetPinDIROutput(LPC_GPIO,port,pin);
	}
}

bool DigitalIoPin::read(){
	if(this->input == true)
	 return Chip_GPIO_GetPinState(LPC_GPIO,port,pin);
	else if(this->invert == true)
		return !(Chip_GPIO_GetPinState(LPC_GPIO,port,pin));
	else return Chip_GPIO_GetPinState(LPC_GPIO,port,pin);

}

void DigitalIoPin::write(bool value){

	if(this->input == true) return;
	if(this->invert == false) return Chip_GPIO_SetPinState(LPC_GPIO, port, pin, value);
	else return Chip_GPIO_SetPinState(LPC_GPIO, port, pin, !value);
}
