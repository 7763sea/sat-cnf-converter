#include "datetimeutil.h"

using namespace Utils;

DateTimeUtil::DateTimeUtil()
{
}

string DateTimeUtil::getCurrentTime()
{
    char str[80];
    time_t localtime;
    time(&localtime);
    std::time_t now = std::time(NULL);
    std::tm * ptm = std::localtime(&now);
    std::strftime(str, 32, "%d.%m.%Y %H:%M:%S", ptm);

    string currentTime(str);
    //Remove line break at the end
    currentTime = currentTime.substr(0, currentTime.size() - 1);
    return currentTime;
}
