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

DriverSettings::DriverSettings(): polarPairs(7), rpmGoal(0), startPwm(200),
    startRpm(300), rpmUpSpeed(500)
{

}
