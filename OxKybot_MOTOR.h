#ifndef __OXKYBOT_MOTOR_H__
#define __OXKYBOT_MOTOR_H__

#include "All_dep.h"

enum motor_speed {
  SLOW,
  FAST
  };
enum motor_state {
  FORWARD,
  BACKWARD,
  STOP
  };
enum motor_transition_type {
  FORWARD_TO_STOP,
  BACKWARD_TO_STOP,
  FORWARD_TO_BACWARD,
  BACKWARD_TO_FORWARD,
  STOP_TO_FORWARD,
  STOP_TO_BACKWARD,
  NO_TRANSITION
  };

class OxKybot_MOTOR
{

public:
	OxKybot_MOTOR(int _pinDigit, int _pinAnalog);
	void setLogger(Logger l);
	void motorBrake();
	void go_forward(int Speed);
	void go_backward(int Speed);
	void loop();
  



private:
  int pinDigit;
  int pinAnalog;
  int i;
  motor_transition_type transitionType;
  motor_speed actualSpeed;
  motor_state actualState;
  void motor_Forward_slow();
  void motor_Backward_slow();
  void motor_Forward(int Speed);
  void motor_Brake();
  void motor_Backward(int Speed);
  Logger logger;


};
#endif
