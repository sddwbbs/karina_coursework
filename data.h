#ifndef DATA_H
#define DATA_H

class Data
{
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
public:
    Data() = default;

    explicit Data(int hours, int minutes, int seconds);

    int toSeconds(const Data &dataObj) const;

    void setHours(int hours);

    void setMinutes(int minutes);

    void setSeconds(int seconds);

    int getHours();

    int getMinutes();

    int getSeconds();
};

#endif // DATA_H
