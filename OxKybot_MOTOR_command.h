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
	void setPositionClient(ros::ServiceClient<std_msgs::String, std_msgs::String>* c);
	void setPosition(std_msgs::String p);
	void setLogger(Logger l);
	void gotoAngle(int angle);
	void resetAngle();
	unsigned int getAngle();
	void forward(int Speed,int angle);
	void backward(int Speed,int angle);
	void turn_left(int Speed);
	void turn_right(int Speed);
	void motorBrake();
	void forward_joy(int Speed);
	void backward_joy(int Speed);
	void turn_left_joy(int Speed);
	void turn_right_joy(int Speed);
	void setTimer(TimeoutCallback* t);



private:
	geometry_msgs::PoseStamped actualPose;
	TimeoutCallback* securityTimer;
	void motorL_Forward(int Speed);
	void motorL_Backward(int Speed);
	void motorL_Brake();
	void motorR_Backward(int Speed);
	void motorR_Forward(int Speed);
	void motor_easy_start(int pin);
	void motor_easy_stop(int pin);
	void motorR_Brake();
	bool motorRRuning;
	bool motorLRuning;

	Logger logger;
	void refreshPosition();
	ros::ServiceClient<std_msgs::String, geometry_msgs::PoseStamped>* client;
	CMPS14_imu imu_sensor;

};
#endif
