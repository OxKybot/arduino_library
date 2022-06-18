#include <Wire.h>
#include <VL53L0X.h>
#include <ros.h>
#include <sensor_msgs/Joy.h>
#include "All_pins.h"
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Empty.h>
#include <avr/wdt.h>
#include "SlamOutPose.h"
#include "Logger.h"
#include <TimeoutCallback.h>

#define SPEED_VALUE 255
#define MIN_SPEED_VALUE 128
#define MIDDLE_SPEED_VALUE 135
#define DELAY_TO_STOP 20
#define DELAY_TO_RUN 10
#define DELAT_ANGLE 50
#define DELAT_ARM 5
#define STEP_DURATION 1100UL
