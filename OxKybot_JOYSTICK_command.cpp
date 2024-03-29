#include "OxKybot_JOYSTICK_command.h"

OxKybot_JOYSTICK_command::OxKybot_JOYSTICK_command()
{
    this->isDirectionStarted = false;
}
void OxKybot_JOYSTICK_command::set_motors(OxKybot_MOTOR_command _motors)
{
    motors = _motors;
}
void OxKybot_JOYSTICK_command::set_arm(OxKybot_ARM_command _arm)
{
    arm = _arm;
}
void OxKybot_JOYSTICK_command::motor_from_Joymsg(const sensor_msgs::Joy &joy)
{
    gestionCroixDirectionnel(joy.axes[7],joy.axes[8]);
    motors.motor_left_joy(joy.axes[2]*100);
    motors.motor_right_joy(joy.axes[6]*100);
}

void OxKybot_JOYSTICK_command::gestionCroixDirectionnel(int hori, int verti)
{
    if(verti != 0 || hori != 0)
    {
        this->isDirectionStarted = true;
    }
    if(this->isDirectionStarted)
    {
        if (verti == 0 && hori == 0)
        {
            motors.motorBrake();
            this->isDirectionStarted = false;
        }
        if (verti == 1 && hori == 0)
        {
            motors.forward_joy();
        }

        if (verti == 0 && hori == 1)
        {
            motors.turn_left_joy();
        }
        if (verti == 0 && hori == -1)
        {
            motors.turn_right_joy();
        }
        if (verti == -1 && hori == 0)
        {
            motors.backward_joy();
        }
    }
}
void OxKybot_JOYSTICK_command::angle_from_Joymsg(const sensor_msgs::Joy &joy)
{

  if (joy.axes[1] == 1 && joy.axes[0] == 0)
  {
    motors.gotoAngle(0);
  }
  if (joy.axes[1] == 1 && joy.axes[0] == 1)
  {
    motors.gotoAngle(450);
  }
  if (joy.axes[1] == 1 && joy.axes[0] == -1)
  {
    motors.gotoAngle(3150);
  }
  if (joy.axes[1] == 0 && joy.axes[0] == 1)
  {
    motors.gotoAngle(900);
  }
  if (joy.axes[1] == 0 && joy.axes[0] == -1)
  {
    motors.gotoAngle(2700);
  }
  if (joy.axes[1] == -1 && joy.axes[0] == 0)
  {
    motors.gotoAngle(1800);
  }
  if (joy.axes[1] == -1 && joy.axes[0] == 1)
  {
    motors.gotoAngle(2250);
  }
  if (joy.axes[1] == -1 && joy.axes[0] == -1)
  {
    motors.gotoAngle(1350);
  }
}
void OxKybot_JOYSTICK_command::axe_from_Joymsg(const sensor_msgs::Joy &joy, bool isLeft)
{
  if (isLeft)
  {
    if (joy.axes[8] == 0)
    {
      arm.desL_Brake();
    }
    if (joy.axes[8] == 1)
    {
      arm.desL_Backward(SPEED_VALUE);
    }
    if (joy.axes[8] == -1)
    {
      arm.desL_Forward(SPEED_VALUE);
    }
    if (joy.axes[7] == 0)
    {
      arm.axeL_Brake();
    }
    if (joy.axes[7] == 1)
    {
      arm.axeL_Backward(SPEED_VALUE);
    }
    if (joy.axes[7] == -1)
    {
      arm.axeL_Forward(SPEED_VALUE);
    }
  }
  else
  {
    if (joy.axes[8] == 0)
    {
      arm.desR_Brake();
    }
    if (joy.axes[8] == 1)
    {
      arm.desR_Backward(SPEED_VALUE);
    }
    if (joy.axes[8] == -1)
    {
      arm.desR_Forward(SPEED_VALUE);
    }
    if (joy.axes[7] == 0)
    {
      arm.axeR_Brake();
    }
    if (joy.axes[7] == 1)
    {
      arm.axeR_Backward(SPEED_VALUE);
    }
    if (joy.axes[7] == -1)
    {
      arm.axeR_Forward(SPEED_VALUE);
    }
  }
}
