#ifndef __OXKYBOT_PROG_PLANTATION_COMMAND_H__
#define __OXKYBOT_PROG_PLANTATION_COMMAND_H__

#include<All_dep.h>

class OxKybot_ARM_command
{

public:
    OxKybot_ARM_command();
    void init();
    uint16_t read_left_arm_position();
	uint16_t read_right_arm_position();
	void left_arm_goto_position(uint16_t p);
	void right_arm_goto_position(uint16_t p);
	void loop();
	void setLogger(Logger l);
	void desL_Forward(int Speed);
	void desL_Backward(int Speed);
	void desL_Brake();
	void desR_Forward(int Speed);
	void desR_Backward(int Speed);
	void desR_Brake();
	void axeL_Forward(int Speed);
	void axeL_Backward(int Speed);
	void axeL_Brake();
	void axeR_Forward(int Speed);
	void axeR_Backward(int Speed);
	void axeR_Brake();
	

private:
	Logger logger;
	bool movingLeft=false;
	bool movingRight=false;
    uint16_t arm_left_pose;
    uint16_t arm_right_pose;
	uint16_t arm_left_goal_pose;
    uint16_t arm_right_goal_pose;
    VL53L0X sensor;
	VL53L0X sensor2;

};
#endif