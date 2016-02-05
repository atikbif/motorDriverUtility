#ifndef DRIVERSETTINGS_H
#define DRIVERSETTINGS_H


class DriverSettings
{
    int polarPairs;
    int rpmGoal;
    int startPwm;
    int startRpm;
    int rpmUpSpeed;
    static const int polarPairsMin = 1, polarPairsMax = 64;
    static const int rpmGoalMin = 0 , rpmGoalMax = 20000;
    static const int startPwmMin = 100, startPwmMax = 600;
    static const int startRpmMin = 100, startRpmMax = 1000;
    static const int rpmUpSpeedMin = 5, rpmUpSpeedMax = 1000;
public:
    DriverSettings();
    int getPolarPairs() const;
    void setPolarPairs(int value);
    int getRpmGoal() const;
    void setRpmGoal(int value);
    int getStartPwm() const;
    void setStartPwm(int value);
    int getStartRpm() const;
    void setStartRpm(int value);
    int getRpmUpSpeed() const;
    void setRpmUpSpeed(int value);
    static int getPolarPairsMin();
    static int getPolarPairsMax();
    static int getRpmGoalMin();
    static int getRpmGoalMax();
    static int getStartPwmMin();
    static int getStartPwmMax();
    static int getStartRpmMin();
    static int getStartRpmMax();
    static int getRpmUpSpeedMin();
    static int getRpmUpSpeedMax();
};

#endif // DRIVERSETTINGS_H
