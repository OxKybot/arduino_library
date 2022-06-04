#ifndef __CMPS14_IMU__
#define __CMPS14_IMU__
#include "All_dep.h"

// Register Function
// 0        Command register

// 1        Compass Bearing as a byte, i.e. 0-255 for a full circle
// 2,3      Compass Bearing as a word, i.e. 0-3599 for a full circle, representing 0-359.9 degrees. Register 2 being the high byte

// 4        Pitch angle - signed byte giving angle in degrees from the horizontal plane, Kalman filtered with Gyro
// 5        Roll angle - signed byte giving angle in degrees from the horizontal plane, Kalman filtered with Gyro

// 6,7      Magnetometer X axis raw output, 16 bit signed integer with register 6 being the upper 8 bits
// 8,9      Magnetometer Y axis raw output, 16 bit signed integer with register 8 being the upper 8 bits
// 10,11    Magnetometer Z axis raw output, 16 bit signed integer with register 10 being the upper 8 bits

// 12,13    Accelerometer  X axis raw output, 16 bit signed integer with register 12 being the upper 8 bits
// 14,15    Accelerometer  Y axis raw output, 16 bit signed integer with register 14 being the upper 8 bits
// 16,17    Accelerometer  Z axis raw output, 16 bit signed integer with register 16 being the upper 8 bits

// 18,19    Gyro X axis raw output, 16 bit signed integer with register 18 being the upper 8 bits
// 20,21    Gyro Y axis raw output, 16 bit signed integer with register 20 being the upper 8 bits
// 22,23    Gyro Z axis raw output, 16 bit signed integer with register 22 being the upper 8 bits

//---------------------------------

//Address of the CMPS14 compass on i2c
#define _i2cAddress 0x60

#define CONTROL_Register 0

#define BEARING_Register 2
#define PITCH_Register 4
#define ROLL_Register 5

#define MAGNETX_Register 6
#define MAGNETY_Register 8
#define MAGNETZ_Register 10

#define ACCELEROX_Register 12
#define ACCELEROY_Register 14
#define ACCELEROZ_Register 16

#define GYROX_Register 18
#define GYROY_Register 20
#define GYROZ_Register 22

#define ONE_BYTE 1
#define TWO_BYTES 2
#define FOUR_BYTES 4
#define SIX_BYTES 6
#define MAX_ANGLE 3600

class CMPS14_imu
{

public:
    CMPS14_imu();
    void init();
    unsigned int getBearing();
    byte getPitch();
    byte getRoll();
    int16_t getgyroX();
    int16_t getgyroY();
    int16_t getgyroZ();
    int16_t getAcceleroX();
    int16_t getAcceleroY();
    int16_t getAcceleroZ();
    int16_t getMagnetX();
    int16_t getMagnetY();
    int16_t getMagnetZ();
    void ReadCompass();
    void ReadAccelerator();
    void ReadGyro();
    void changeAddress(byte i2cAddress, byte newi2cAddress);
    void resetBearing();

private:
    
    //---------------------------------

    byte _byteHigh;
    byte _byteLow;

    // Please note without clear documentation in the technical documenation
    // it is notoriously difficult to get the correct measurement units.
    // I've tried my best, and may revise these numbers.

    unsigned int bearing;
    unsigned int bearingCompensation;
    int nReceived;
    signed char pitch;
    signed char roll;

    float magnetX;
    float magnetY;
    float magnetZ;

    float accelX;
    float accelY;
    float accelZ;
    // The acceleration along the X-axis, presented in mg
    // See BNO080_Datasheet_v1.3 page 21
    float accelScale; // 1 m/s^2

    float gyroX;
    float gyroY;
    float gyroZ;
    // 16bit signed integer 32,768
    // Max 2000 degrees per second - page 6
    float gyroScale; // 1 Dps
};
#endif