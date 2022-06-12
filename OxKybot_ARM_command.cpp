#include "OxKybot_ARM_command.h"

OxKybot_ARM_command::OxKybot_ARM_command()
{
}
void OxKybot_ARM_command::init()
{
  logger.publish_arduino_log("ARM init start");

  pinMode(AXIN1, OUTPUT);
  pinMode(AXIN2, OUTPUT);
  pinMode(AXENA, OUTPUT);
  pinMode(AXIN4, OUTPUT);
  pinMode(AXIN3, OUTPUT);
  pinMode(AXENB, OUTPUT);

  pinMode(DSIN1, OUTPUT);
  pinMode(DSIN2, OUTPUT);
  pinMode(DSENA, OUTPUT);
  pinMode(DSIN4, OUTPUT);
  pinMode(DSIN3, OUTPUT);
  pinMode(DSENB, OUTPUT);
  
  digitalWrite(LXL, HIGH);

  delay(150);

  sensor.init(true);

  delay(100);

  sensor.setAddress((uint8_t)01);

  delay(100);

  digitalWrite(LXR, HIGH);

  delay(150);

  sensor2.init(true);

  delay(100);

  sensor2.setAddress((uint8_t)02);

  sensor.startContinuous();

  sensor2.startContinuous();
  
  logger.publish_arduino_log("ARM init done");
}
void OxKybot_ARM_command::setLogger(Logger l)
{
  this->logger = l;
}
uint16_t OxKybot_ARM_command::read_left_arm_position()
{
  this->arm_left_pose = this->sensor.readRangeContinuousMillimeters();
  logger.publish_arduino_log("ARM left position : " + this->arm_left_pose);
  return this->arm_left_pose;
}
uint16_t OxKybot_ARM_command::read_right_arm_position()
{
  this->arm_right_pose = this->sensor2.readRangeContinuousMillimeters();
  logger.publish_arduino_log("ARM right position : " + this->arm_right_pose);
  return this->arm_right_pose;
}

void OxKybot_ARM_command::left_arm_goto_position(uint16_t p)
{
  logger.publish_arduino_log("ARM left new gaol position : " + p);
  read_left_arm_position();
  this->movingLeft = true;
  if (p > this->arm_left_pose)
  {
    axeL_Forward(SPEED_VALUE);
  }
  else
  {
    axeL_Backward(SPEED_VALUE);
  }
}
void OxKybot_ARM_command::right_arm_goto_position(uint16_t p)
{
  logger.publish_arduino_log("ARM right new gaol position : " + p);
  read_right_arm_position();
  this->movingRight = true;
  if (p > this->arm_right_pose)
  {
    axeR_Forward(SPEED_VALUE);
  }
  else
  {
    axeR_Backward(SPEED_VALUE);
  }
}
void OxKybot_ARM_command::loop()
{
  if (this->movingLeft)
  {
    read_left_arm_position();
    if (abs(this->arm_left_goal_pose - this->arm_left_pose) < DELAT_ARM)
    {
      this->movingLeft = false;
      axeL_Brake();     
    }
  }
  if (this->movingRight)
  {
    read_right_arm_position();
    if (abs(this->arm_right_goal_pose - this->arm_right_pose) < DELAT_ARM)
    {
      this->movingRight = false;
      axeR_Brake();
    }
  }
}

void OxKybot_ARM_command::desL_Forward(int Speed)
{
  logger.publish_arduino_log("DES left move forward");
  digitalWrite(DSIN1, HIGH);
  digitalWrite(DSIN2, LOW);
  analogWrite(DSENA, Speed);
}

void OxKybot_ARM_command::desL_Backward(int Speed)
{
  logger.publish_arduino_log("DES left move backward");
  digitalWrite(DSIN1, LOW);
  digitalWrite(DSIN2, HIGH);
  analogWrite(DSENA, Speed);
}
void OxKybot_ARM_command::desL_Brake()
{
  logger.publish_arduino_log("DES left stop");
  digitalWrite(DSIN1, LOW);
  digitalWrite(DSIN2, LOW);
}
void OxKybot_ARM_command::desR_Forward(int Speed)
{
  logger.publish_arduino_log("DES right move forward");
  digitalWrite(DSIN3, HIGH);
  digitalWrite(DSIN4, LOW);
  analogWrite(DSENB, Speed);
}

void OxKybot_ARM_command::desR_Backward(int Speed)
{
  logger.publish_arduino_log("DES right move backward");
  digitalWrite(DSIN3, LOW);
  digitalWrite(DSIN4, HIGH);
  analogWrite(DSENB, Speed);
}
void OxKybot_ARM_command::desR_Brake()
{
  logger.publish_arduino_log("DES right stop");
  digitalWrite(DSIN3, LOW);
  digitalWrite(DSIN4, LOW);
}

void OxKybot_ARM_command::axeL_Forward(int Speed)
{
  logger.publish_arduino_log("ARM left move forward");
  digitalWrite(AXIN1, HIGH);
  digitalWrite(AXIN2, LOW);
  analogWrite(AXENA, Speed);
}

void OxKybot_ARM_command::axeL_Backward(int Speed)
{
  logger.publish_arduino_log("ARM left move bacward");
  digitalWrite(AXIN1, LOW);
  digitalWrite(AXIN2, HIGH);
  analogWrite(AXENA, Speed);
}
void OxKybot_ARM_command::axeL_Brake()
{
  digitalWrite(AXIN1, LOW);
  digitalWrite(AXIN2, LOW);
  logger.publish_arduino_log("ARM left STOP");
}
void OxKybot_ARM_command::axeR_Forward(int Speed)
{
  logger.publish_arduino_log("ARM right move forward");
  digitalWrite(AXIN3, HIGH);
  digitalWrite(AXIN4, LOW);
  analogWrite(AXENB, Speed);
}

void OxKybot_ARM_command::axeR_Backward(int Speed)
{
  logger.publish_arduino_log("ARM right move bacward");
  digitalWrite(AXIN3, LOW);
  digitalWrite(AXIN4, HIGH);
  analogWrite(AXENB, Speed);
}
void OxKybot_ARM_command::axeR_Brake()
{
  logger.publish_arduino_log("ARM right STOP");
  digitalWrite(AXIN3, LOW);
  digitalWrite(AXIN4, LOW);
}
