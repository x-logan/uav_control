/*
 * ButtonsDecode.h
 *
 *  Created on: 13/09/2016
 *      Author: Logan
 */

#ifndef SRC_BUTTONS_DECODE_H_
#define SRC_BUTTONS_DECODE_H_

#include <mavros_msgs/ManualControl.h>
#include <math.h>
#define Button1 3
#define Button2 768
#define Button3 48
#define Button4 3072
#define Button5 12
#define Button6 192

namespace Utils {

class ButtonsDecode {
public:
	ButtonsDecode();
	virtual ~ButtonsDecode();
	void Decode(mavros_msgs::ManualControl msg );
	float Aileron;
	float Elevator;
	float Rudder;
	float Throttle;
	int SW1;
	int SW2;
	int SW3;
	int SW4;
	int SW5;
	int SW6;


};

} /* namespace Utils */

#endif /* SRC_BUTTONS_DECODE_H_ */
