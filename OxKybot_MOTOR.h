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
enum motor_speed {
  SLOW,
  FAST
  };
class OxKybot_MOTOR
{
public:
	OxKybot_MOTOR();
	void init(int _pinDigit, int _pinAnalog);
	void setLogger(Logger l);
	void motorBrake();
	void go_forward(motor_speed speed);
	void go_backward(motor_speed speed);
	void loop();
  



private:
  int pinDigit;
  int pinAnalog;
  int i;
  transition_type transitionType;
  motor_speed actualSpeed;
  motor_state actualState;
  void motor_Forward_slow();
  void motor_Backward_slow();
  void motor_Forward(int speed);
  void motor_Brake();
  void motor_Backward(int speed);
  Logger logger;


};
#endif
