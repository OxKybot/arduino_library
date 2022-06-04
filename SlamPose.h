#ifndef _SLAMPOSE_h
#define _SLAMPOSE_h
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define MAX_POSE_SIZE 100
class SlamPose
{
public:
    SlamPose() {}
    int poseX;
    int poseY;
    int angle;
    char *serialize()
    {
        String stringPose = "" + String(this->poseX) + "," + String(this->poseY) + "," + String(this->angle);
        char *bufferPose = new char[MAX_POSE_SIZE];
        stringPose.toCharArray(bufferPose, MAX_POSE_SIZE);
        return bufferPose;
    }
    String toString()
    {
        return "" + String(this->poseX) + "," + String(this->poseY) + "," + String(this->angle);
    }
    void deserialize( char *inbuffer)
    {
        char *ptr = strtok(inbuffer, ",");
        this->poseX = atoi(ptr);
        ptr = strtok(NULL, ",");
        this->poseY = atoi(ptr);
        ptr = strtok(NULL, ",");
        this->angle = atoi(ptr);
    }
    const char *getType() { return "SlamOutPose"; };
    const char *getMD5()
    {
      return PSTR("0825d95fdfa2c8f4bbb4e9c74bccd3fd");
    };
};
#endif
