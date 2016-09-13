/*
 * UAVController.cpp
 *
 *  Created on: 29 Feb 2016
 *      Author: Logan
 */

#include "UAVController.h"


UAVController::UAVController() {
	// TODO Auto-generated constructor stub

	speed_pid.initPid(0.32,0.01,0.05,0.25,-0.25);
	altitude_pid.initPid(0.05,0,0.01,10,-10);

}

UAVController::~UAVController() {
	// TODO Auto-generated destructor stub
}

void UAVController::ControlStep(ros::Duration dt)
{
	ROS_INFO("SPEED PID: %.4f-%.4f=%.4f",speedValue,speedSetpoint,speedValue-speedSetpoint);
	speed_pid.computeCommand(speedValue-speedSetpoint,dt);
	if(speed_pid.getCurrentCmd()>1)
		speed_pid.setCurrentCmd(1);
	else if(speed_pid.getCurrentCmd()<0)
		speed_pid.setCurrentCmd(0);
	ROS_INFO("SPEED PID");

	altitude_pid.computeCommand(altitudeValue-altitudeSetpoint,dt);
	if(altitude_pid.getCurrentCmd()>.8)
		altitude_pid.setCurrentCmd(.8);
		else if(altitude_pid.getCurrentCmd()<-.8)
			altitude_pid.setCurrentCmd(-.8);
   	//ROS_INFO("ALTITUDE PID");
	double pe = 0;
	double ie = 0;
	double de = 0;
	altitude_pid.getCurrentPIDErrors(&pe,&ie,&de);
	//ROS_INFO("dt: %.4f, cmd: %.2f, error: %.4f, pe:%.4f, ie:%.4f, pe:%.4f ",dt.toSec(), altitude_pid.getCurrentCmd(),altitudeValue-altitudeSetpoint, pe,ie,de);
}

// Update current values
void UAVController::UpdateAltitudeValue(double value)
{
	altitudeSetpoint = value;
}
void UAVController::UpdateSpeedValue(double value)
{
	speedSetpoint = value;

}

// Update setpoints
void UAVController::UpdateAltitudeSetpoint(double value)
{
	altitudeValue = value;

}
void UAVController::UpdateSpeedSetpoint(double value)
{
	speedValue = value;

}

// Get controls
double UAVController::GetAltitudeControl()
{
	return altitude_pid.getCurrentCmd();
}

double UAVController::GetSpeedControl()
{
	return speed_pid.getCurrentCmd();
}

void UAVController::UpdateAltitudeGains(double P, double I, double D, double Imax, double Imin){
	altitude_pid.setGains(P,I,D,Imax,Imin);
}

void UAVController::UpdateSpeedGains(double P, double I, double D, double Imax, double Imin){
	speed_pid.setGains(P,I,D,Imax,Imin);
}

