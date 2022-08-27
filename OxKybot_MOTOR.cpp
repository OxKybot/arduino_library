
#include "OxKybot_MOTOR.h"

OxKybot_MOTOR::OxKybot_MOTOR(){}

void OxKybot_MOTOR::init(int _pinDigit, int _pinAnalog)
{
  this->actualSpeed = 0;
  this->actualState = STOP;
  this->transitionType = NO_TRANSITION;
  this->pinDigit = _pinDigit;
  this->pinAnalog = _pinAnalog;
  this->isRuningSlow = false;
}
void OxKybot_MOTOR::setLogger(Logger l)
{
  this->logger = l;
}
void OxKybot_MOTOR::loop()
{
  if(this->goalSpeed!=this->actualSpeed)
  {
    if(this->goalSpeed>this->actualSpeed)
    {
      this->actualSpeed++;
    }
    if(this->goalSpeed<this->actualSpeed)
    {
      this->actualSpeed--;
    }
    switch(this->actualState)
    {
      case FORWARD:
        motor_Forward(this->actualSpeed);
        break;
        case FORWARD:
        motor_Forward(this->actualSpeed);
        break;
    }
  }
}
void OxKybot_MOTOR::go_forward(int speed)
{
  this->transitionType = this->transitionStateMatrix[this->actualState][FORWARD];
  this->goalSpeed= speed;
  if(this->transitionType== NO_TRANSITION)
    {
      this->actualState = FORWARD;
    }
}

void OxKybot_MOTOR::go_backward(int speed)
{
  this->transitionType = this->transitionStateMatrix[this->actualState][BCKWARD];
  this->goalSpeed= speed;
  this->actualState = BCKWARD;
}
void OxKybot_MOTOR::motorBrake()
{
  this->transitionType = this->transitionStateMatrix[this->actualState][STOP];
  this->goalSpeed= 0;
  this->actualState = STOP;
}

void OxKybot_MOTOR::motor_Forward(int Speed)
{
//logger.publish_arduino_log("motor_Forward at speed : " + String(Speed) + " pd: "+String(this->pinDigit)+ " pa: "+String(this->pinAnalog));  
  analogWrite(this->pinAnalog, Speed);
  digitalWrite(this->pinDigit, LOW);
  
}

void OxKybot_MOTOR::motor_Backward(int Speed)
{
  //logger.publish_arduino_log("motor_Backward at speed : " + String(Speed) + " pd: "+String(this->pinDigit)+ " pa: "+String(this->pinAnalog));  
  
  analogWrite(this->pinAnalog, Speed);
  digitalWrite(this->pinDigit, HIGH);
}
void OxKybot_MOTOR::motor_Brake()
{
  digitalWrite(this->pinDigit, LOW);
  analogWrite(this->pinAnalog, 0);
}
