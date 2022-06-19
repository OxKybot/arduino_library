
#include "OxKybot_MOTOR.h"

OxKybot_MOTOR::OxKybot_MOTOR(int _pinDigit, int _pinAnalog)
{
  this->actualSpeed = FAST;
  this->actualState = STOP;
  this->transitionType = NO_TRANSITION;
  this->pinDigit = _pinDigit;
  this->pinAnalog = _pinAnalog;
}
void OxKybot_MOTOR::loop()
{
  if(this->transitionType == NO_TRANSITION && this->actualSpeed == SLOW)
  {
    if(this->actualState == FORWARD)
    {
      motor_Forward_slow();
    }
    if(this->actualState == BACKWARD)
    {
      motor_Backward_slow();
    }
  }
  if(this->transitionType == FORWARD_TO_STOP)
  {
    for(i=0; i<NB_PULSE_TRANSITION;i++)
    {
      motor_Forward_slow();
    } 
    this->transitionType = NO_TRANSITION;
  }
  if(this->transitionType == BACKWARD_TO_STOP)
  {
    for(i=0; i<NB_PULSE_TRANSITION;i++)
    {
      motor_Backward_slow();
    } 
    this->transitionType = NO_TRANSITION;
  }
  if(this->transitionType == STOP_TO_FORWARD)
  {
    for(i=0; i<NB_PULSE_TRANSITION;i++)
    {
      motor_Forward_slow();
    } 
    motor_Forward(SPEED_VALUE);
    this->transitionType = NO_TRANSITION;
  }
  if(this->transitionType == STOP_TO_BACKWARD)
  {
    for(i=0; i<NB_PULSE_TRANSITION;i++)
    {
      motor_Backward_slow();
    } 
    motor_Backward(SPEED_VALUE);
    this->transitionType = NO_TRANSITION;
  }
  if(this->transitionType == motor_transition_type::FORWARD_TO_BACKWARD)
  {
    for(i=0; i<NB_PULSE_TRANSITION;i++)
    {
      motor_Forward_slow();
    } 
    for(i=0; i<NB_PULSE_TRANSITION;i++)
    {
      motor_Backward_slow();
      
    }
    motor_Backward(SPEED_VALUE);
    this->transitionType = NO_TRANSITION;
  }
  if(this->transitionType == BACKWARD_TO_FORWARD)
  {
    for(i=0; i<NB_PULSE_TRANSITION;i++)
    {
      motor_Backward_slow();
    } 
    for(i=0; i<NB_PULSE_TRANSITION;i++)
    {
      motor_Forward_slow();
    }
    motor_Forward(SPEED_VALUE);
    this->transitionType = NO_TRANSITION;
  }
  
}
void OxKybot_MOTOR::go_forward(motor_speed speed)
{
  if(this->actualSpeed!= SLOW && speed!= SLOW)
  {
    if(this->actualState!=FORWARD)
    {
      if(this->actualState == STOP)
      {
        this->transitionType = STOP_TO_FORWARD;
      }
      else
      {
        this->transitionType = FORWARD_TO_BACKWARD;
      }      
    }
    this->actualSpeed = speed;
  }
  this->actualState = FORWARD;
}

void OxKybot_MOTOR::go_backward(motor_speed speed)
{
  if(this->actualSpeed!= SLOW && speed!= SLOW)
  {
    if(this->actualState!=BACKWARD)
    {
      if(this->actualState == STOP)
      {
        this->transitionType = STOP_TO_BACKWARD;
      }
      else
      {
        this->transitionType = BACKWARD_TO_FORWARD;
      }
      
    }
    this->actualSpeed = speed;
  }
  this->actualState = BACKWARD;
}
void OxKybot_MOTOR::motorBrake()
{
  if(this->actualState!=STOP)
  {
    if(this->actualState!= SLOW)
    {
      if(this->actualState == FORWARD)
      {
        this->transitionType = FORWARD_TO_STOP;
      }
      else
      {
        this->transitionType = BACKWARD_TO_STOP;
      }
    }
    else
    {
      this->motor_Brake();
      this->actualSpeed = FAST;
    }
    this->actualState = STOP;
  }
}
void OxKybot_MOTOR::motor_Forward_slow()
{
  motor_Forward(MIN_SPEED_VALUE);
  delay(DELAY_TO_RUN);
  motor_Brake();
  delay(DELAY_TO_STOP);
  motor_Brake();
  delay(DELAY_TO_STOP);
}
void OxKybot_MOTOR::motor_Backward_slow()
{
  motor_Backward(MIN_SPEED_VALUE);
  delay(DELAY_TO_RUN);
  motor_Brake();
  delay(DELAY_TO_STOP);
  motor_Brake();
  delay(DELAY_TO_STOP);
}
void OxKybot_MOTOR::motor_Forward(int Speed)
{
  digitalWrite(this->pinDigit, LOW);
  analogWrite(this->pinAnalog, Speed);
}

void OxKybot_MOTOR::motor_Backward(int Speed)
{
  digitalWrite(this->pinDigit, HIGH);
  analogWrite(this->pinAnalog, Speed);
}
void OxKybot_MOTOR::motor_Brake()
{
  digitalWrite(this->pinDigit, LOW);
  analogWrite(this->pinAnalog, 0);
}
