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
geometry_msgs::PoseStamped OxKybot_MOTOR_command::getPosition()
{
  refreshPosition();
  return this->actualPose;
}
void OxKybot_MOTOR_command::refreshPosition()
{
  std_msgs::String req;
  geometry_msgs::PoseStamped res;
  client->call(req, res);
  setPosition(res);
}
void OxKybot_MOTOR_command::setTimer(TimeoutCallback *t)
{
  securityTimer = t;
}
void OxKybot_MOTOR_command::setPosition(geometry_msgs::PoseStamped p)
{
  
  this->actualPose = p;
  this->logger.publish_arduino_log("position : X=" + String(this->actualPose.pose.position.x) + "Y=" +String(this->actualPose.pose.position.y) + "A=" + String(this->actualPose.pose.orientation.z));
                                       
}
void OxKybot_MOTOR_command::setLogger(Logger l)
{
  this->logger = l;
}
void OxKybot_MOTOR_command::setPositionClient(ros::ServiceClient<std_msgs::String, geometry_msgs::PoseStamped> *c)
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
  for(int i=MIDDLE_SPEED_VALUE;i>MIN_SPEED_VALUE;i--)
    {
      motorR_Brake();
      motorL_Brake();
      delay(DELAY_TO_STOP);
      forward_joy(128); 
      delay(DELAY_TO_STOP);
    }
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
  //this->logger.publish_arduino_log("easy start");
}
void OxKybot_MOTOR_command::motor_easy_stop(int pin)
{
  /*this->logger.publish_arduino_log("easy stop start");
  for(int i=MIDDLE_SPEED_VALUE;i>MIN_SPEED_VALUE;i--)
    {
      motorBrake();
      delay(DELAY_TO_STOP);
      forward_joy(128);
    }
  this->logger.publish_arduino_log("easy stop FINISHED");*/
}
void OxKybot_MOTOR_command::motorL_Forward(int Speed)
{
  digitalWrite(MOE1, HIGH);
  analogWrite(MOP1, Speed);
  motorLRuning= true;
}
void OxKybot_MOTOR_command::motorL_Backward(int Speed)
{
  digitalWrite(MOE1, LOW);
  analogWrite(MOP1, Speed);
  motorLRuning = true;
}
void OxKybot_MOTOR_command::motorL_Brake()
{
  if(motorLRuning)
  digitalWrite(MOE1, LOW);
  analogWrite(MOP1, 0);
  motorLRuning = false;
}
void OxKybot_MOTOR_command::motorR_Backward(int Speed)
{
  digitalWrite(MOE2, LOW);
  analogWrite(MOP2, Speed);
  motorRRuning = true;
}

void OxKybot_MOTOR_command::motorR_Forward(int Speed)
{
  digitalWrite(MOE2, HIGH);
  analogWrite(MOP2, Speed);
  motorRRuning = true;
}
void OxKybot_MOTOR_command::motorR_Brake()
{
  digitalWrite(MOE2, LOW);
  analogWrite(MOP2, 0);
  motorRRuning = false;
}
