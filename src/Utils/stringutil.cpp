#include "stringutil.h"

using namespace Utils;

StringUtil::StringUtil()
{
}

string StringUtil::trim(string input)
{
    string result(input);
    while(0 < result.size()) {
        if(0 == result.substr(0, 1).compare(" ")
                || 0 == result.substr(0, 1).compare("\t")) {
            result = result.substr(1);
        } else if(0 == result.substr(result.size() - 1, 1).compare(" ")
                || 0 == result.substr(result.size() - 1, 1).compare("\t")) {
            result = result.substr(0, result.size() - 1);
        } else {
            break;
        }
    }
    return result;
}

string StringUtil::trimBrackets(string input)
{
    input = StringUtil::trim(input);

    bool isInBrackets = (0 == input.substr(0, 1).compare("("))
        && (0 == input.substr(input.size() - 1, 1).compare(")"));
    if(isInBrackets)
        input = input.substr(1, input.size() - 2);

    input = StringUtil::trim(input);
    return input;
}

bool StringUtil::beginsWith(string haystack, string needle)
{
    return haystack.size() >= needle.size() && haystack.substr(0, needle.size()).compare(needle) == 0;
}

bool StringUtil::equals(string str1, string str2)
{
    return str1.size() == str2.size() && 0 == str1.compare(str2);
}

string StringUtil::intToString(unsigned long long input)
{
    string result("");
    ostringstream convert;
    convert << input;
    result = convert.str();
    return result;
}
