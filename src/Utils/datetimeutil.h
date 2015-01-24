#ifndef UTILS_DATETIMEUTIL_H
#define UTILS_DATETIMEUTIL_H

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

namespace Utils
{

/**
 * @brief Functions for working with Date and Time
 */
class DateTimeUtil
{
public:
    DateTimeUtil();

    /**
     * @brief Returns current date and time as string
     * @return
     */
    static string getCurrentTime();
};

}

#endif // UTILS_DATETIMEUTIL_H
