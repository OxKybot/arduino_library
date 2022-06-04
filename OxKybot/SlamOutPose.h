#ifndef _SLAMOUTPOSE_h
#define _SLAMOUTPOSE_h
#include "SlamPose.h"


class SlamOutPoseResponse : public ros::Msg
{
public:
  SlamPose *output;

  SlamOutPoseResponse() : output()
  {
  }

  virtual int serialize(unsigned char *outbuffer) const
  {
    int offset = 0;
    varToArr(outbuffer + offset, MAX_POSE_SIZE);
    offset += 4;
    char *outputSerialised = output->serialize();
    memcpy(outbuffer + offset, outputSerialised, MAX_POSE_SIZE);
    offset += MAX_POSE_SIZE;
    return offset;
  }

  virtual int deserialize(unsigned char *inbuffer)
  {
    int offset = 0;
    uint32_t length_input;
    arrToVar(length_input, (inbuffer + offset));
    offset += 4;
    for (unsigned int k = offset; k < offset + length_input; ++k)
    {
      inbuffer[k - 1] = inbuffer[k];
    }
    inbuffer[offset + length_input - 1] = 0;
    char *charArrayInBuffer = (char *)(inbuffer + offset - 1);
    this->output->deserialize(charArrayInBuffer);
    offset += length_input;
    return offset;
  }
  const char *getType() { return "SlamOutPose"; };
#ifdef ESP8266
  const char *getMD5()
  {
    return ("0825d95fdfa2c8f4bbb4e9c74bccd3fd");
  };
#else
  const char *getMD5()
  {
    return PSTR("0825d95fdfa2c8f4bbb4e9c74bccd3fd");
  };
#endif
};

class SlamOutPose
{
public:
  typedef SlamOutPoseResponse Response;
};
#endif