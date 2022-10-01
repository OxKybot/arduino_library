
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
void OxKybot_MOTOR::commandChanged(transition_type type)
{
  if(type == STOP_TO_FORWARD)
  {
    this->actualState = FORWARD;
    motor_Forward(1);
  }
  if(type == STOP_TO_BACKWARD)
  {
    this->actualState = BACKWARD;
    motor_Backward(1);
  }
  if(type == SPEED_CHANGED)
  {
    this->stepDuration = TRANSITION_DURATION / abs(this->actualSpeed-this->goalSpeed);
  }else
  {
    this->stepDuration = TRANSITION_DURATION / this->actualSpeed;
  }
  this->startMillis = millis();
  
}
void OxKybot_MOTOR::setLogger(Logger l)
{
  this->logger = l;
}

void OxKybot_MOTOR::doStep()
{
  if(this->goalSpeed!=this->actualSpeed)
  {
    this->actualSpeed += this->goalSpeed>this->actualSpeed ? 1 : -1;
    if(this->actualSpeed == 0)
    {
      motorBrake();
    }
    switch(this->actualState)
    {
      case FORWARD:
        motor_Forward(this->actualSpeed);
        break;
       case BACKWARD:
        motor_Backward(this->actualSpeed);
        break;
      default:
        this->transitionType = NO_TRANSITION;
        break;
    }
  } else
  {
    this->transitionType = NO_TRANSITION;
  }
}
void OxKybot_MOTOR::loop()
{
  if(this->actualState != STOP && this->transitionType != NO_TRANSITION)
  {
    this->currentMillis =  millis();
    if (((this->currentMillis - this->startMillis) % this->stepDuration) == 0)
    {
      doStep();
    }
  }
}
void OxKybot_MOTOR::go_forward(int speed)
{
  if(this->actualState != FORWARD || this->goalSpeed != speed)
  {
    this->transitionType = this->transitionStateMatrix[this->actualState][FORWARD];
    this->goalSpeed= speed;
    commandChanged(this->transitionType);
  }
}

void OxKybot_MOTOR::go_backward(int speed)
{
  if(this->actualState != BACKWARD || this->goalSpeed != speed)
  {
    this->transitionType = this->transitionStateMatrix[this->actualState][BACKWARD];
    this->goalSpeed= speed;
    commandChanged(this->transitionType);
  }
}
void OxKybot_MOTOR::motorBrake()
{
  if(this->actualState != STOP)
  {
    this->transitionType = this->transitionStateMatrix[this->actualState][STOP];
    this->goalSpeed= 0;
    commandChanged(this->transitionType);
  }
}

void OxKybot_MOTOR::motor_Forward(int speedPercent)
{
//logger.publish_arduino_log("motor_Forward at speed : " + String(Speed) + " pd: "+String(this->pinDigit)+ " pa: "+String(this->pinAnalog)); 
  
  analogWrite(this->pinAnalog, calculateSpeed(speedPercent));
  digitalWrite(this->pinDigit, LOW);
  
}

void OxKybot_MOTOR::motor_Backward(int speedPercent)
{
  //logger.publish_arduino_log("motor_Backward at speed : " + String(Speed) + " pd: "+String(this->pinDigit)+ " pa: "+String(this->pinAnalog));  
  
  analogWrite(this->pinAnalog, calculateSpeed(speedPercent));
  digitalWrite(this->pinDigit, HIGH);
}
void OxKybot_MOTOR::motor_Brake()
{
  digitalWrite(this->pinDigit, LOW);
  analogWrite(this->pinAnalog, 0);
  this->actualState = STOP;
}
int OxKybot_MOTOR::calculateSpeed(int speedPercent)
{
  return (SPEED_VALUE-MIN_SPEED_VALUE)*speedPercent/100+MIN_SPEED_VALUE;
}
