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
	void forward(motor_speed speed,int angle);
	void backward(motor_speed speed,int angle);
	void turn_left(motor_speed speed);
	void turn_right(motor_speed speed);
	void motorBrake();
	void forward_joy();
	void backward_joy();
	void turn_left_joy();
	void turn_right_joy();
	void motor_left_motorBrake();
	void motor_left_forward_joy(int speedPercent);
	void motor_left_backward_joy(int speedPercent);
	void motor_right_motorBrake();
	void motor_right_forward_joy(int speedPercent);
	void motor_right_backward_joy(int speedPercent);
	
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
