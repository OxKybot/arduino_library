
#include "OxKybot_MOTOR.h"

OxKybot_MOTOR::OxKybot_MOTOR(){}

void OxKybot_MOTOR::init(int _pinDigit, int _pinAnalog)
{
  this->actualSpeed = FAST;
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
  if(this->isRuningSlow)
  {
    logger.publish_arduino_log("isRuningSlow : " + String(this->isRuningSlow));
    if(this->actualState == FORWARD)
    {
      motor_Forward_slow();
    }
    if(this->actualState == BACKWARD)
    {
      motor_Backward_slow();
    }
  }    
}
void OxKybot_MOTOR::go_forward(motor_speed speed)
{
  logger.publish_arduino_log("go_forward at speed : " + String(speed));
  if(this->actualSpeed == FAST && speed == FAST)
  {
    if(this->actualState!=FORWARD)
    {
      if(this->actualState == STOP)
      {
        this->transitionType = STOP_TO_FORWARD;
        for(i=0; i<NB_PULSE_TRANSITION;i++)
        {
          motor_Forward_slow();
        } 
        motor_Forward(SPEED_VALUE);
      }
      else
      {
        this->transitionType = BACKWARD_TO_FORWARD;
        for(i=0; i<NB_PULSE_TRANSITION;i++)
        {
          motor_Backward_slow();
        } 
        for(i=0; i<NB_PULSE_TRANSITION;i++)
        {
          motor_Forward_slow();
        }
        motor_Forward(SPEED_VALUE);
      }      
    }
    this->actualSpeed = speed;
  }else
  {
    if(speed == FAST)
    {
      motor_Forward(SPEED_VALUE);
    }else{
      this->isRuningSlow=true;
    }
    this->actualSpeed = speed;
  }
  this->actualState = FORWARD;
}

void OxKybot_MOTOR::go_backward(motor_speed speed)
{
  logger.publish_arduino_log("go_backward at speed : " + String(speed));
  if(this->actualSpeed!= SLOW && speed!= SLOW)
  {
    if(this->actualState!=BACKWARD)
    {
      if(this->actualState == STOP)
      {
        this->transitionType = STOP_TO_BACKWARD;
        for(i=0; i<NB_PULSE_TRANSITION;i++)
        {
          motor_Backward_slow();
        } 
        motor_Backward(SPEED_VALUE);
      }
      else
      {
        this->transitionType = FORWARD_TO_BACKWARD;
        for(i=0; i<NB_PULSE_TRANSITION;i++)
        {
          motor_Forward_slow();
        } 
        for(i=0; i<NB_PULSE_TRANSITION;i++)
        {
          motor_Backward_slow();

        }
        motor_Backward(SPEED_VALUE);
      }
      
    }
    
  }else
  {
    if(speed != SLOW)
    {
      motor_Backward(SPEED_VALUE);
    }else{
      this->isRuningSlow=true;
    }
    this->actualSpeed = speed;
  }
  this->actualState = BACKWARD;
}
void OxKybot_MOTOR::motorBrake()
{
  if(this->actualState!=STOP)
  {
    if(this->actualState == FAST)
    {
      if(this->actualState == FORWARD)
      {
        this->transitionType = FORWARD_TO_STOP;
        for(i=0; i<NB_PULSE_TRANSITION;i++)
        {
          motor_Forward_slow();
        } 
      }
      else
      {
        this->transitionType = BACKWARD_TO_STOP;
        for(i=0; i<NB_PULSE_TRANSITION;i++)
        {
          motor_Backward_slow();
        } 
      }
    }
    else
    {
      this->motor_Brake();
      this->isRuningSlow=false;
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
logger.publish_arduino_log("motor_Forward at speed : " + String(Speed) + " pd: "+String(this->pinDigit)+ " pa: "+String(this->pinAnalog));  

  digitalWrite(this->pinDigit, LOW);
  analogWrite(this->pinAnalog, Speed);
}

void OxKybot_MOTOR::motor_Backward(int Speed)
{
  logger.publish_arduino_log("motor_Backward at speed : " + String(Speed) + " pd: "+String(this->pinDigit)+ " pa: "+String(this->pinAnalog));  

  digitalWrite(this->pinDigit, HIGH);
  analogWrite(this->pinAnalog, Speed);
}
void OxKybot_MOTOR::motor_Brake()
{
  digitalWrite(this->pinDigit, LOW);
  analogWrite(this->pinAnalog, 0);
}
