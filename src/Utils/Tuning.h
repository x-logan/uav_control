/*
 * Tuning.h
 *
 *  Created on: 1 Mar 2016
 *      Author: Logan
 */

#ifndef SRC_UTILS_TUNING_H_
#define SRC_UTILS_TUNING_H_

#include <mavros_msgs/RCIn.h>
#include <math.h>

namespace Utils {

class Tuning {
public:
	Tuning();
	virtual ~Tuning();
	void Update(mavros_msgs::RCIn msg );
	double GetParam1();
	double GetParam2();
	bool IsEnable();


private:
	float param_max_1;
	float param_max_2;
	float param_min_1;
	float param_min_2;
	float channel_number_1;
	float channel_number_2;
	float channel_max_1;
	float channel_max_2;
	float channel_min_1;
	float channel_min_2;
	float decimal_precision_1;
	float decimal_precision_2;
	double newParam1;
	double newParam2;
	bool isEnable;



};

} /* namespace Utils */

#endif /* SRC_UTILS_TUNING_H_ */
