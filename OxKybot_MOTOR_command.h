#ifndef __OXKYBOT_MOTOR_COMMAND_H__
#define __OXKYBOT_MOTOR_COMMAND_H__

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
	void forward(motor_speed speed,int angle);
	void backward(motor_speed speed,int angle);
	void turn_left(motor_speed speed);
	void turn_right(motor_speed speed);
	void motorBrake();
	void forward_joy(motor_speed speed);
	void backward_joy(motor_speed speed);
	void turn_left_joy(motor_speed speed);
	void turn_right_joy(motor_speed speed);
	void setTimer(TimeoutCallback* t);
	void loop();

private:
	OxKybot_MOTOR motorLeft;
	OxKybot_MOTOR motorRight
	unsigned int actualAngle;
	SlamPose actualPose;
	TimeoutCallback* securityTimer;
	Logger logger;
	void refreshPosition();
	ros::ServiceClient<std_msgs::String, geometry_msgs::PoseStamped>* client;
	CMPS14_imu imu_sensor;

};
#endif
