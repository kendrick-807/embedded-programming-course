/*
 * SimpleMenu.cpp
 *
 *  Created on: 3.2.2016
 *      Author: krl
 */

#include "SimpleMenu.h"

SimpleMenu::SimpleMenu() {
	position = 0;
	counter = 0;
}

SimpleMenu::~SimpleMenu() {
	// TODO Auto-generated destructor stub
}

void SimpleMenu::addItem(MenuItem *item) {
	items.push_back(item);
}

void SimpleMenu::event(MenuItem::menuEvent e) {
	if(items.size() <= 0) return;

//	if(e == MenuItem::ok){
//				counter++;
//				if(counter == 2){
//					for(auto item : items){
//						item->LPC_print();
//						counter = 0;
//					}
//				}
//			}



	if(!items[position]->event(e)) {
		if(e == MenuItem::up) position++;
		else if(e == MenuItem::down) position--;


		if(position < 0) position = items.size() - 1;
		if(position >= (int) items.size()) position = 0;

		items[position]->event(MenuItem::show);




	}else{
		if(e == MenuItem::ok){
			counter++;
			if(counter == 2){
				for(auto item : items){
					item->LPC_print();
					counter = 0;
				}
			}

		}
		if(e == MenuItem::back){
			counter = 0;
		}

	}
}
