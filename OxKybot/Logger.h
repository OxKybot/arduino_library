#ifndef _LOGGER_h
#define _LOGGER_h
#include <string.h>
#include <ros.h>
#include <std_msgs/String.h>

class Logger
{
public:
    Logger() {}
    Logger(ros::Publisher *_logPublisher, std_msgs::String _str_ARDUINO_LOG_msg)
    {
        this->logPublisher = _logPublisher;
        this->str_ARDUINO_LOG_msg = _str_ARDUINO_LOG_msg;
    }
    ros::Publisher *logPublisher;
    std_msgs::String str_ARDUINO_LOG_msg;
    void publis_arduino_log(String textLog)
    {
        int logLength = textLog.length()+1;
        char *bufferLog = new char[logLength];
        textLog.toCharArray(bufferLog, logLength);
        str_ARDUINO_LOG_msg.data = bufferLog;
        logPublisher->publish(&str_ARDUINO_LOG_msg);
    }
    void publis_arduino_log_msg(std_msgs::String textLog)
    {
        logPublisher->publish(&textLog);
    }
};
#endif