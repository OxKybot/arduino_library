#include "OxKybot_MOTOR_command.h"

OxKybot_MOTOR_command::OxKybot_MOTOR_command() {}
void OxKybot_MOTOR_command::init()
{
  logger.publish_arduino_log("MOTOR init start");
  pinMode(MOE1, OUTPUT);
  pinMode(MOP1, OUTPUT);
  pinMode(MOE2, OUTPUT);
  pinMode(MOP2, OUTPUT);

  pinMode(LAMP, OUTPUT);
  pinMode(LXL, OUTPUT);
  pinMode(LXR, OUTPUT);

  digitalWrite(LAMP, LOW);
  digitalWrite(LXL, LOW);
  digitalWrite(LXR, LOW);

  delay(500);

  Wire.begin();

  delay(500);
  imu_sensor = CMPS14_imu();
  imu_sensor.init();
  motorRRuning =false;
  motorLRuning =false;
  logger.publish_arduino_log("MOTOR init done");
}
SlamPose OxKybot_MOTOR_command::getPosition()
{
  refreshPosition();
  return this->position;
}
void OxKybot_MOTOR_command::refreshPosition()
{
  std_msgs::String req;
  std_msgs::String res;
  client->call(req, res);
  setPosition(res);
}
void OxKybot_MOTOR_command::setTimer(TimeoutCallback *t)
{
  securityTimer = t;
}

void OxKybot_MOTOR_command::setPosition(std_msgs::String p)
{
  free(this->setPositionData);
  free(this->setPositionPtr);
  this->setPositionData = new char[100];
  this->setPositionData_string = String(p.data);
  strcpy(this->setPositionData, this->setPositionData_string.c_str());
  this->setPositionPtr = strtok(this->setPositionData, ",");
  this->position.poseX = atoi(this->setPositionPtr);
  this->setPositionPtr = strtok(NULL, ",");
  this->position.poseY = atoi(this->setPositionPtr);
  this->setPositionPtr = strtok(NULL, ",");
  this->position.angle = atoi(this->setPositionPtr);
  this->logger.publish_arduino_log("position : " + this->position.toString());
}
void OxKybot_MOTOR_command::setLogger(Logger l)
{
  this->logger = l;
}
void OxKybot_MOTOR_command::setPositionClient(ros::ServiceClient<std_msgs::String, std_msgs::String> *c)
{
  this->client = c;
  refreshPosition();
}

void OxKybot_MOTOR_command::resetAngle()
{
  this->imu_sensor.resetBearing();
  logger.publish_arduino_log("ANGLE has been reset");
}
void OxKybot_MOTOR_command::gotoAngle(int angle)
{
  
	unsigned int gotoAngleD1;
	unsigned int gotoAngleD2;
  this->actualAngle = this->imu_sensor.getBearing();
  logger.publish_arduino_log("MOTOR actual angle : "+ String(this->actualAngle) + " go to : "+String(angle));
  gotoAngleD1 = (MAX_ANGLE + angle - this->actualAngle) % MAX_ANGLE;
  gotoAngleD2 = (MAX_ANGLE + this->actualAngle - angle) % MAX_ANGLE;
  if (!(gotoAngleD1 < DELAT_ANGLE && gotoAngleD2 < DELAT_ANGLE))
  {
    
    if (gotoAngleD1 < gotoAngleD2)
    {
      logger.publish_arduino_log("MOTOR turn left");
      while (gotoAngleD1 > DELAT_ANGLE)
      {
        turn_left(SPEED_VALUE);
        this->actualAngle = this->imu_sensor.getBearing();
        gotoAngleD1 = (MAX_ANGLE + angle - actualAngle) % MAX_ANGLE;
        wdt_reset();
      }
    }
    else
    {
      logger.publish_arduino_log("MOTOR turn right");
      while (gotoAngleD2 > DELAT_ANGLE)
      {
        turn_right(SPEED_VALUE);
        this->actualAngle = this->imu_sensor.getBearing();
        gotoAngleD2 = (MAX_ANGLE + actualAngle - angle) % MAX_ANGLE;
        wdt_reset();
      }
    }
    motorBrake();
    this->logger.publish_arduino_log("MOTOR turn end");
  }
}
unsigned int OxKybot_MOTOR_command::getAngle()
{
  this->actualAngle = this->imu_sensor.getBearing();
  return this->actualAngle;
}
void OxKybot_MOTOR_command::turn_left(int Speed)
{
  motorR_Forward(SPEED_VALUE);
  motorL_Backward(SPEED_VALUE);
  securityTimer->start();
}
void OxKybot_MOTOR_command::turn_right(int Speed)
{
  motorL_Forward(SPEED_VALUE);
  motorR_Backward(SPEED_VALUE);
  securityTimer->start();
}

void OxKybot_MOTOR_command::forward(int Speed, int angle)
{
  gotoAngle(angle);
  motorL_Forward(SPEED_VALUE);
  motorR_Forward(SPEED_VALUE);
  securityTimer->start();
}
void OxKybot_MOTOR_command::backward(int Speed, int angle)
{
  gotoAngle(angle);
  motorL_Backward(SPEED_VALUE);
  motorR_Backward(SPEED_VALUE);
  securityTimer->start();
}

void OxKybot_MOTOR_command::motorBrake()
{
  motorR_Brake();
  motorL_Brake();
  wdt_reset();
}
void OxKybot_MOTOR_command::turn_left_joy(int Speed)
{
  motorR_Forward(SPEED_VALUE);
  motorL_Backward(SPEED_VALUE);
}
void OxKybot_MOTOR_command::turn_right_joy(int Speed)
{
  motorL_Forward(SPEED_VALUE);
  motorR_Backward(SPEED_VALUE);
}
void OxKybot_MOTOR_command::forward_joy(int Speed)
{
  motorL_Forward(SPEED_VALUE);
  motorR_Forward(SPEED_VALUE);
}
void OxKybot_MOTOR_command::backward_joy(int Speed)
{
  motorL_Backward(SPEED_VALUE);
  motorR_Backward(SPEED_VALUE);
}
void OxKybot_MOTOR_command::motor_easy_start(int pin)
{
  for(int i=MIN_SPEED_VALUE;i>MIDDLE_SPEED_VALUE;i--)
    {
      wdt_reset();
      analogWrite(pin, i);
      delay(DELAY_TO_STOP);
    }
}
void OxKybot_MOTOR_command::motor_easy_stop(int pin)
{
  for(int i=MIDDLE_SPEED_VALUE;i>MIN_SPEED_VALUE;i--)
    {
      wdt_reset();
      analogWrite(pin, i);
      delay(DELAY_TO_STOP);
    }
}
void OxKybot_MOTOR_command::motorL_Forward(int Speed)
{
  digitalWrite(MOE1, HIGH);
  if(!motorLRuning)
  {
    motor_easy_start(MOP1);
  }
  analogWrite(MOP1, Speed);
  motorLRuning= true;
}
void OxKybot_MOTOR_command::motorL_Backward(int Speed)
{
  digitalWrite(MOE1, LOW);
  if(!motorLRuning)
  {
    motor_easy_start(MOP1);
  } 
  analogWrite(MOP1, Speed);
  motorLRuning = true;
}
void OxKybot_MOTOR_command::motorL_Brake()
{
  if(motorLRuning)
  {
    motor_easy_stop(MOP1);
  }
  digitalWrite(MOE1, LOW);
  analogWrite(MOP1, 0);
  motorLRuning = false;
}
void OxKybot_MOTOR_command::motorR_Backward(int Speed)
{
  digitalWrite(MOE2, HIGH);
  if(!motorRRuning)
  {
    motor_easy_start(MOP2);
  }
  analogWrite(MOP2, Speed);
  motorRRuning = true;
}

void OxKybot_MOTOR_command::motorR_Forward(int Speed)
{
  digitalWrite(MOE2, LOW);
  if(!motorRRuning)
  {
    motor_easy_start(MOP2);
  }
  analogWrite(MOP2, Speed);
  motorRRuning = true;
}
void OxKybot_MOTOR_command::motorR_Brake()
{
  if(motorRRuning)
  {
    motor_easy_stop(MOP2);
  }
  digitalWrite(MOE2, LOW);
  analogWrite(MOP2, 0);
  motorRRuning = false;
}
