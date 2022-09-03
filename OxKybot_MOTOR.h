#ifndef __OXKYBOT_MOTOR_H__
#define __OXKYBOT_MOTOR_H__

#include "All_dep.h"

enum motor_state {
  FORWARD,
  BACKWARD,
  STOP
  };

enum transition_type{
  FORWARD_TO_STOP,
  BACKWARD_TO_STOP,
  SPEED_CHANGED,
  STOP_TO_FORWARD,
  STOP_TO_BACKWARD,
  NO_TRANSITION
  };

class OxKybot_MOTOR
{
public:
	OxKybot_MOTOR();
	void init(int _pinDigit, int _pinAnalog);
	void setLogger(Logger l);
	void motorBrake();
	void go_forward(int speed);
	void go_backward(int speed);
	void loop();
	boolean isRuningSlow;
  



private:
	//usage: transitionStateMatrix[old_state][new_state]
	int transitionStateMatrix[3][3] = {
		{SPEED_CHANGED,FORWARD_TO_STOP,FORWARD_TO_STOP},
		{BACKWARD_TO_STOP,SPEED_CHANGED,BACKWARD_TO_STOP},
		{STOP_TO_FORWARD,STOP_TO_BACKWARD,NO_TRANSITION}
	};
	unsigned long currentMillis;
	unsigned long startMillis;
	unsigned long stepDuration;
	int pinDigit;
	int pinAnalog;
	int actualSpeed;
	int goalSpeed;
	transition_type transitionType;
	motor_state actualState;
	void doStep();
	void commandChanged();
	void motor_Forward(int speedPercent);
	void motor_Brake();
	void motor_Backward(int speedPercent);
	int calculateSpeed(int speedPercent);
	Logger logger;


};
#endif
