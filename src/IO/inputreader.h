#ifndef IO_INPUTREADER_H
#define IO_INPUTREADER_H

#include <iostream>
#include <string>

#include "../Model/Collection/chain.h"

using namespace std;

using namespace Model::Collection;

namespace IO
{

/**
 * @brief The InputReader class
 * Reads an input file and returns an array(vector) of strings representing the input
 */
class InputReader
{
public:
    InputReader();

    Chain<string> *read();
};

}

#endif // IO_INPUTREADER_H
