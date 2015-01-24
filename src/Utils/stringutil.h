#ifndef UTILS_STRINGUTIL_H
#define UTILS_STRINGUTIL_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace Utils
{

/**
 * @brief The StringUtil class
 * Functions for strings
 */
class StringUtil
{
public:
    StringUtil();

    /**
     * @brief trim removes spaces and tabs from begin and and of string
     * @param input
     * @return string
     */
    static string trim(string input);

    /**
     * @brief trimBrackets removes brackets from begin and end of stirng
     * @param input
     * @return
     */
    static string trimBrackets(string input);

    /**
     * @brief beginsWith checks if first characters of
     * string "haystack" begin with "needle"
     * @param haystack
     * @param needle
     * @return
     */
    static bool beginsWith(string haystack, string needle);

    /**
     * @brief equals checks if two string sare equal
     * @param str1
     * @param str2
     * @return
     */
    static bool equals(string str1, string str2);

    /**
     * @brief converts integer variable to string
     * @param input
     * @return
     */
    static string intToString(unsigned long long input);
};


}

#endif // UTILS_STRINGUTIL_H
