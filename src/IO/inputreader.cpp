#include "inputreader.h"

using namespace IO;

InputReader::InputReader()
{
}

Chain<string> *InputReader::read()
{
    Chain<string> *result = new Chain<string>();

    string inputString;
    while(getline(cin, inputString)) {
        result->add(inputString);
    }
    return result;
}
