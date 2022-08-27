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
  FORWARD_TO_BACKWARD,
  BACKWARD_TO_FORWARD,
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
	  {NO_TRANSITION,FORWARD_TO_BACKWARD,FORWARD_TO_STOP},
	  {BACKWARD_TO_FORWARD,NO_TRANSITION,BACKWARD_TO_STOP},
	  {STOP_TO_FORWARD,STOP_TO_BACKWARD,NO_TRANSITION}
  };
  int pinDigit;
  int pinAnalog;
  int i;
  transition_type transitionType;
  int actualSpeed;
  int goalSpeed;
  motor_state actualState;
  void motor_Forward(int speed);
  void motor_Brake();
  void motor_Backward(int speed);
  Logger logger;
  

};
#endif
