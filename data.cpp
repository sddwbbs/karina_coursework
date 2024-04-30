#include "data.h"

Data::Data(int hours, int minutes, int seconds)
    : hours(hours), minutes(minutes), seconds(seconds) {}

int Data::toSeconds(const Data &dataObj) const
{
    int result = dataObj.hours * 3600 + dataObj.minutes * 60 + dataObj.seconds;
    return result;
}

void Data::setHours(int hours)
{
    this->hours = hours;
}

void Data::setMinutes(int minutes)
{
    this->minutes = minutes;
}

void Data::setSeconds(int seconds)
{
    this->seconds = seconds;
}

int Data::getHours()
{
    return hours;
}

int Data::getMinutes()
{
    return minutes;
}

int Data::getSeconds()
{
    return seconds;
}
