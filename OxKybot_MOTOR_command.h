#ifndef __OXKYBOT_MOTOR_COMMAND_H__
#define __OXKYBOT_MOTOR_COMMAND_H__

#include "CMPS14_imu.h"
#include "OxKybot_MOTOR.h"
class OxKybot_MOTOR_command
{

public:
	OxKybot_MOTOR_command();
	void init();
	SlamPose getPosition();
	void setPositionClient(ros::ServiceClient<std_msgs::String, geometry_msgs::PoseStamped>* c);
	void setPosition(geometry_msgs::PoseStamped p);
	void setLogger(Logger l);
	void gotoAngle(int angle);
	void resetAngle();
	unsigned int getAngle();
	void forward(int speed,int angle);
	void backward(int speed,int angle);
	void turn_left(int speed);
	void turn_right(int speed);
	void motorBrake();
	void forward_joy();
	void backward_joy();
	void turn_left_joy();
	void turn_right_joy();
	void motor_left_joy(int SingnedSpeedPercent);
	void motor_right_joy(int SingnedSpeedPercent);
	
	void setTimer(TimeoutCallback* t);
	void loop();

private:
	OxKybot_MOTOR motorLeft;
	OxKybot_MOTOR motorRight;
	unsigned int actualAngle;
	SlamPose actualPose;
	TimeoutCallback* securityTimer;
	Logger logger;
	void refreshPosition();
	ros::ServiceClient<std_msgs::String, geometry_msgs::PoseStamped>* client;
	CMPS14_imu imu_sensor;

};
#endif
