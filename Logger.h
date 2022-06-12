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
    void publish_arduino_log(String textLog)
    {
        this->logLength = textLog.length()+1;
        this->bufferLog = new char[this->logLength];
        textLog.toCharArray(this->bufferLog, this->logLength);
        this->str_ARDUINO_LOG_msg.data = this->bufferLog;
        logPublisher->publish(&this->str_ARDUINO_LOG_msg);
    }
    void publish_arduino_log_msg(std_msgs::String textLog)
    {
        logPublisher->publish(&textLog);
    }
private:
    ros::Publisher *logPublisher;
    std_msgs::String str_ARDUINO_LOG_msg;
    int logLength;
    char *bufferLog;

};
#endif
