#ifndef __OXKYBOT_MOTOR_COMMAND_H__
#define __OXKYBOT_MOTOR_COMMAND_H__

#include "All_dep.h"
#include "CMPS14_imu.h"
class OxKybot_MOTOR_command
{

public:
	OxKybot_MOTOR_command();
	void init();
	geometry_msgs::PoseStamped getPosition();
	void setPositionClient(ros::ServiceClient<std_msgs::String, geometry_msgs::PoseStamped>* c);
	void setPosition(geometry_msgs::PoseStamped p);
	void setLogger(Logger l);
	void gotoAngle(int angle);
	void resetAngle();
	unsigned int getAngle();
	void forward(motor_speed Speed,int angle);
	void backward(motor_speed Speed,int angle);
	void turn_left(motor_speed Speed);
	void turn_right(motor_speed Speed);
	void motorBrake();
	void forward_joy(motor_speed Speed);
	void backward_joy(motor_speed Speed);
	void turn_left_joy(motor_speed Speed);
	void turn_right_joy(motor_speed Speed);
	void setTimer(TimeoutCallback* t);
	void loop();

private:
	OxKybot_MOTOR motorLeft;
	OxKybot_MOTOR motorRight
	unsigned int actualAngle;
	geometry_msgs::PoseStamped actualPose;
	TimeoutCallback* securityTimer;
	Logger logger;
	void refreshPosition();
	ros::ServiceClient<std_msgs::String, geometry_msgs::PoseStamped>* client;
	CMPS14_imu imu_sensor;

};
#endif
