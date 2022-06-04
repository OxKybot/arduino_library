#ifndef __OXKYBOT_PROG_PLANTATION_COMMAND_H__
#define __OXKYBOT_PROG_PLANTATION_COMMAND_H__

#include "OxKybot_MOTOR_command.h"

class OxKybot_PROG_PLANTATION_command
{

public:
    OxKybot_PROG_PLANTATION_command(OxKybot_MOTOR_command _motors);


private:
    OxKybot_MOTOR_command motors;
};
#endif