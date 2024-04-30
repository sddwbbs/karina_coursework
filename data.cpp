#include "data.h"

Data::Data(int hours, int minutes, int seconds)
    : hours(hours), minutes(minutes), seconds(seconds) {}

int Data::toSeconds() const
{
    int result = hours * 3600 + minutes * 60 + seconds;
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

int Data::getHours() const
{
    return hours;
}

int Data::getMinutes() const
{
    return minutes;
}

int Data::getSeconds() const
{
    return seconds;
}
