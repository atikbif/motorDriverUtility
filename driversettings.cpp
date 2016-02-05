#include "driversettings.h"


int DriverSettings::getPolarPairs() const
{
    return polarPairs;
}

void DriverSettings::setPolarPairs(int value)
{
    if((value>=polarPairsMin)&&(value<=polarPairsMax))  polarPairs = value;
}

int DriverSettings::getRpmGoal() const
{
    return rpmGoal;
}

void DriverSettings::setRpmGoal(int value)
{
    if((value>=rpmGoalMin)&&(value<=rpmGoalMax)) rpmGoal = value;
    if(value && value<300) rpmGoal = 300;
}

int DriverSettings::getStartPwm() const
{
    return startPwm;
}

void DriverSettings::setStartPwm(int value)
{
    if((value>=startPwmMin)&&(value<=startPwmMax)) startPwm = value;
}

int DriverSettings::getStartRpm() const
{
    return startRpm;
}

void DriverSettings::setStartRpm(int value)
{
    if((value>=startRpmMin)&&(value<=startRpmMax)) startRpm = value;
}

int DriverSettings::getRpmUpSpeed() const
{
    return rpmUpSpeed;
}

void DriverSettings::setRpmUpSpeed(int value)
{
    if((value>=rpmUpSpeedMin)&&(value<=rpmUpSpeedMax)) rpmUpSpeed = value;
}

int DriverSettings::getPolarPairsMin()
{
    return polarPairsMin;
}

int DriverSettings::getPolarPairsMax()
{
    return polarPairsMax;
}

int DriverSettings::getRpmGoalMin()
{
    return rpmGoalMin;
}

int DriverSettings::getRpmGoalMax()
{
    return rpmGoalMax;
}

int DriverSettings::getStartPwmMin()
{
    return startPwmMin;
}

int DriverSettings::getStartPwmMax()
{
    return startPwmMax;
}

int DriverSettings::getStartRpmMin()
{
    return startRpmMin;
}

int DriverSettings::getStartRpmMax()
{
    return startRpmMax;
}

int DriverSettings::getRpmUpSpeedMin()
{
    return rpmUpSpeedMin;
}

int DriverSettings::getRpmUpSpeedMax()
{
    return rpmUpSpeedMax;
}

DriverSettings::DriverSettings(): polarPairs(7), rpmGoal(0), startPwm(200),
    startRpm(300), rpmUpSpeed(500)
{

}
