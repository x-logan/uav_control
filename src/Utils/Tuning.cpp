/*
 * Tuning.cpp
 *
 *  Created on: 1 Mar 2016
 *      Author: pi
 */

#include "Tuning.h"

namespace Utils {

Tuning::Tuning() {
	// TODO Auto-generated constructor stub
	param_max_1 = 0.5;
	param_max_2 = 0.05;
	param_min_1 = 0;
	param_min_2 = 0;
	channel_number_1 = 11;
	channel_number_2 = 12;
	channel_max_1 = 1905;
	channel_max_2 = 1905;
	channel_min_1 = 1105;
	channel_min_2 = 1105;
	decimal_precision_1 = 2;
	decimal_precision_2 = 2;
	isEnable = false;



}

Tuning::~Tuning() {
	// TODO Auto-generated destructor stub
}

void Tuning::Update(mavros_msgs::RCIn msg ){



	newParam1 = ((param_max_1-param_min_1)*((msg.channels[channel_number_1-1]-channel_min_1)/(channel_max_1-channel_min_1)))+param_min_1;
	unsigned int newParamTemp = ((double)newParam1*pow(10,decimal_precision_1));
	newParam1 = (((double)newParamTemp)/pow(10,decimal_precision_1));

	newParam2 = ((param_max_2-param_min_2)*((msg.channels[channel_number_2-1]-channel_min_2)/(channel_max_2-channel_min_2)))+param_min_2;
	newParamTemp = ((double)newParam2*pow(10,decimal_precision_2));
	newParam2 = (((double)newParamTemp)/pow(10,decimal_precision_2));

}

double Tuning::GetParam1(){
	return newParam1;
}

double Tuning::GetParam2(){
	return newParam2;
}

bool Tuning::IsEnable(){
	return isEnable;
}

} /* namespace Utils */
