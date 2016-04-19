/*
 * UAVController.h
 *
 *  Created on: 29 Feb 2016
 *      Author: Logan
 */

#ifndef SRC_UAVCONTROLLER_H_
#define SRC_UAVCONTROLLER_H_

#include <ros/ros.h>
#include <control_toolbox/pid.h>

class UAVController {
public:
	UAVController();
	virtual ~UAVController();

	void ControlStep(ros::Duration Dt);

	// Update current values
	void UpdateAltitudeValue(double value);
	void UpdateSpeedValue(double value);

	// Update setpoints
	void UpdateAltitudeSetpoint(double AltitudeValue);
	void UpdateSpeedSetpoint(double SpeedValue);

	// Update Gains
	void UpdateAltitudeGains(double P, double I, double D, double Imax, double Imin);
	void UpdateSpeedGains(double P, double I, double D, double Imax, double Imin);

	// Get Controls
	double GetAltitudeControl();
	double GetSpeedControl();


private:
	control_toolbox::Pid altitude_pid;
	double altitude_error;
	double altitudeSetpoint;
	double altitudeValue;
	control_toolbox::Pid speed_pid;
	double speed_error;
	double speedSetpoint;
	double speedValue;




};

#endif /* SRC_UAVCONTROLLER_H_ */
