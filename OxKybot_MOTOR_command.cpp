#include "OxKybot_MOTOR_command.h"

OxKybot_MOTOR_command::OxKybot_MOTOR_command() {}
void OxKybot_MOTOR_command::init()
{
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
  this->imu_sensor = CMPS14_imu();
  this->imu_sensor.init();
  this->motorLeft = OxKybot_MOTOR(MOE2,MOP2);
  this->motorRight = OxKybot_MOTOR(MOE1,MOP1);
  this->actualPose = SlamPose();
}
geometry_msgs::PoseStamped OxKybot_MOTOR_command::getPosition()
{
  refreshPosition();
  return this->actualPose;
}
void OxKybot_MOTOR_command::loop()
{
  this->motorLeft.loop();
  this->motorRight.loop();
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
  
  this->actualPose.setPose(p);
  this->logger.publish_arduino_log("position : " + this->actualPose.toString());
                                       
}
void OxKybot_MOTOR_command::setLogger(Logger l)
{
  this->logger = l;
  this->motorLeft.setLogger(l);
  this->motorRight.setLogger(l);
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
        turn_left(SLOW);
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
        turn_right(SLOW);
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
void OxKybot_MOTOR_command::turn_left(motor_speed Speed)
{
  this->motorRight.go_forward(speed);
  this->motorLeft.go_backward(speed);
  securityTimer->start();
}
void OxKybot_MOTOR_command::turn_right(motor_speed Speed)
{
  this->motorLeft.go_forward(speed);
  this->motorRight.go_backward(speed);
  securityTimer->start();
}

void OxKybot_MOTOR_command::forward(motor_speed Speed, int angle)
{
  gotoAngle(angle);
  this->motorLeft.go_forward(speed);
  this->motorRight.go_forward(speed);
  securityTimer->start();
}
void OxKybot_MOTOR_command::backward(motor_speed Speed, int angle)
{
  gotoAngle(angle);
  this->motorLeft.go_backward(speed);
  this->motorRight.go_backward(speed);
  securityTimer->start();
}

void OxKybot_MOTOR_command::motorBrake()
{
  this->motorLeft.motorBrake();
  this->motorRight.motorBrake();
  wdt_reset();
}
void OxKybot_MOTOR_command::turn_left_joy(motor_speed Speed)
{
  this->motorRight.go_forward(speed);
  this->motorLeft.go_backward(speed);
}
void OxKybot_MOTOR_command::turn_right_joy(motor_speed Speed)
{
  this->motorLeft.go_forward(speed);
  this->motorRight.go_backward(speed);
}
void OxKybot_MOTOR_command::forward_joy(motor_speed Speed)
{
  this->motorLeft.go_forward(speed);
  this->motorRight.go_forward(speed);
}
void OxKybot_MOTOR_command::backward_joy(motor_speed Speed)
{
  this->motorLeft.go_backward(speed);
  this->motorRight.go_backward(speed);
}
