#ifndef __OXKYBOT_JOYSTICK_COMMAND_H__
#define __OXKYBOT_JOYSTICK_COMMAND_H__

#include "OxKybot_MOTOR_command.h"
#include "OxKybot_ARM_command.h"

class OxKybot_JOYSTICK_command
{

public:
    OxKybot_JOYSTICK_command();
    void set_motors(OxKybot_MOTOR_command _motors);
    void set_arm(OxKybot_ARM_command _arm);
    void motor_from_Joymsg(const sensor_msgs::Joy &joy);
    void motor_slow_from_Joymsg(const sensor_msgs::Joy &joy);
    void axe_from_Joymsg(const sensor_msgs::Joy &joy, bool isLeft);
    void angle_from_Joymsg(const sensor_msgs::Joy &joy);

private:
    OxKybot_MOTOR_command motors;
    OxKybot_ARM_command arm;
    void motor_from_joy(motor_speed speed,const sensor_msgs::Joy &joy);
};
#endif
