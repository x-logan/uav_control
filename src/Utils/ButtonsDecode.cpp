/*
 * ButtonsDecode.cpp
 *
 *  Created on: 13/09/2016
 *      Author: Logan
 */

#include "ButtonsDecode.h"

namespace Utils {

ButtonsDecode::ButtonsDecode() {
	// TODO Auto-generated constructor stub
	Aileron=0;
	Elevator=0;
	Rudder=0;
	Throttle=0;
	SW1=0;
	SW2=0;
	SW3=0;
	SW4=0;
	SW5=0;
	SW6=0;
}

ButtonsDecode::~ButtonsDecode() {
	// TODO Auto-generated destructor stub
}

void ButtonsDecode::Decode(mavros_msgs::ManualControl msg ){
	Aileron=msg.y;
	Elevator=msg.x;
	Rudder = msg.r;
	Throttle = msg.z;
	SW1 = (msg.buttons & Button1)-2;
	SW2 = ((msg.buttons & Button2)>>2) -2;
	SW3 = ((msg.buttons & Button3)>>4) -2;
	SW4 = ((msg.buttons & Button4)>>6) -2;
	SW5 = ((msg.buttons & Button5)>>8) -2;
	SW6 = ((msg.buttons & Button6)>>10) -2;


}

} /* namespace Utils */
