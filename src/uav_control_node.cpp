/**
 * @file offb_node.cpp
 * @brief offboard example node, written with mavros version 0.14.2, px4 flight
 * stack and tested in Gazebo SITL
 */

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/NavSatFix.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/VFR_HUD.h>
#include <mavros_msgs/RCIn.h>
#include <mavros_msgs/ParamGet.h>
#include <mavros_msgs/ManualControl.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Quaternion.h>
#include "Controller/UAVController.h"
#include "Utils/Tuning.h"
#include "Utils/ButtonsDecode.h"

#include "Navigation/Path4D.h"
#include "Navigation/PathGenerator4D.h"
#include "Maps/MapTools.h"

mavros_msgs::State currentState;
mavros_msgs::VFR_HUD currentVfrHud;
mavros_msgs::RCIn currentRcIn;
mavros_msgs::ManualControl currentManualControl;
Utils::ButtonsDecode buttons;
geometry_msgs::PoseStamped currentPose;
sensor_msgs::NavSatFix currentGlobalPosition;

bool updateRc;

void state_cb(const mavros_msgs::State::ConstPtr& msg){
	currentState = *msg;
}

void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg){
	currentPose = *msg;
}

void manualControlCallback(const mavros_msgs::ManualControl::ConstPtr& msg){
	currentManualControl = *msg;
	buttons.Decode(*msg);
}

void vfrHudCallback(const mavros_msgs::VFR_HUD::ConstPtr& msg){
	currentVfrHud = *msg;
}

void rcInCallback(const mavros_msgs::RCIn::ConstPtr& msg){
	currentRcIn = *msg;
	updateRc = true;
}

void globalPositionCallback(const sensor_msgs::NavSatFix::ConstPtr& msg){
	currentGlobalPosition = *msg;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
    ROS_INFO("START\n");
    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
                ("mavros/state", 10, state_cb);
    ros::Subscriber pose_sub = nh.subscribe<geometry_msgs::PoseStamped>("mavros/local_position/pose", 10, poseCallback);
    ros::Subscriber manual_control = nh.subscribe<mavros_msgs::ManualControl>("mavros/manual_control/control", 10, manualControlCallback);
    ros::Subscriber vfrHudSub = nh.subscribe<mavros_msgs::VFR_HUD>("mavros/vfr_hud", 10, vfrHudCallback);
    ros::Subscriber rcInSub = nh.subscribe<mavros_msgs::RCIn>("mavros/rc/in", 10, rcInCallback);
    ros::Subscriber globalPositionSub = nh.subscribe<sensor_msgs::NavSatFix>("mavros/global_position/global", 10, globalPositionCallback);
    updateRc = false;

    ros::Publisher att_throttle_pub = nh.advertise<std_msgs::Float64>("mavros/setpoint_attitude/att_throttle", 10);
    ros::Publisher att_pub = nh.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_attitude/attitude",10);

    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
    ros::ServiceClient paramGet = nh.serviceClient<mavros_msgs::ParamGet>("mavros/param/get");

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(40.0);

    // Init UAVController
    UAVController Controller;

    // Tuning
    Utils::Tuning tuning;


    Navigation::PathGenerator4D pathgenerator4D;




    // wait for FCU connection
    while(ros::ok() && currentState.connected){
        ros::spinOnce();
        rate.sleep();
    }

    std_msgs::Float64 throttle_cmd;
    throttle_cmd.data = 1;

    geometry_msgs::PoseStamped att_cmd;


    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
        att_throttle_pub.publish(throttle_cmd);
        ros::spinOnce();
        rate.sleep();
    }

    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    mavros_msgs::ParamGet paramGetCmd;
    paramGetCmd.request.param_id = "TN";

    ros::Time last_request = ros::Time::now();
    ros::Time last_time = ros::Time::now();

    //set_mode_client.call(offb_set_mode);
    ROS_INFO("Sending Offboard command");

    while(ros::ok()){
        if( (ros::Time::now() - last_request > ros::Duration(1.0))){

        	ROS_INFO("Speed: %.2f, altitude: %.2f",currentVfrHud.airspeed,currentGlobalPosition.altitude);
            last_request = ros::Time::now();

            if(updateRc && tuning.IsEnable())
			{
				ROS_INFO("Param1: %.2f, Param2: %.2f",tuning.GetParam1(),tuning.GetParam2());



				tuning.Update(currentRcIn);
				Controller.UpdateAltitudeGains(0.05,tuning.GetParam1(),tuning.GetParam2(),10,-10);
				updateRc = false;


			}
        }


	//ROS_INFO("Controller Update values");

        Controller.UpdateSpeedValue(currentVfrHud.airspeed);
        ROS_INFO("Ail: %.2f, Elev: %.2f, Throttle: %.2f, Rud: %.2f",buttons.Aileron,buttons.Elevator,buttons.Throttle,buttons.Rudder);
        ROS_INFO("buttons: %X, %d, %d, %d, %d, %d, %d",currentManualControl.buttons, buttons.SW1, buttons.SW2, buttons.SW3, buttons.SW4, buttons.SW5, buttons.SW6);
        Controller.UpdateSpeedSetpoint((double)(currentManualControl.z)*30);
        Controller.UpdateAltitudeValue(currentGlobalPosition.altitude);
        Controller.UpdateAltitudeSetpoint(200);





        Controller.ControlStep(ros::Time::now() - last_time);
        last_time = ros::Time::now();
	//ROS_INFO("Controller ControlStep");


        tf::Quaternion q = tf::createQuaternionFromRPY((currentManualControl.x)*0.6,(currentManualControl.x)*0.6,0);

        att_cmd.pose.orientation.w = q.w();
        att_cmd.pose.orientation.x = q.x();
        att_cmd.pose.orientation.y = q.y();
        att_cmd.pose.orientation.z = q.z();

        throttle_cmd.data = Controller.GetSpeedControl();


        att_throttle_pub.publish(throttle_cmd);
        att_pub.publish(att_cmd);



        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
