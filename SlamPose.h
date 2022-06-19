#ifndef _SLAMPOSE_h
#define _SLAMPOSE_h
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "All_dep.h"
class SlamPose
{
public:
    SlamPose() 
    {
        this->poseX = 0;
        this->poseY = 0;
        this->angle = 0;
    }
    int poseX;
    int poseY;
    int angle;
    void setPose(geometry_msgs::PoseStamped p)
    {
        this->actualPose = p;
        this->poseX = this->actualPose.pose.position.x * POSITION_FACTOR;
        this->poseY = this->actualPose.pose.position.y * POSITION_FACTOR;
        this->angle = this->actualPose.pose.orientation.z * POSITION_FACTOR;
    }
    String toString()
    {
        return "X=" + String(this->poseX) + ",Y=" + String(this->poseY) + ",A=" + String(this->angle);
    }
    
private:
    geometry_msgs::PoseStamped actualPose;
   
};
#endif
