#ifndef IO_INPUTFILEREADER_H
#define IO_INPUTFILEREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "../Model/Collection/chain.h"

using namespace std;
using namespace Model::Collection;

namespace IO
{

/**
 * Reads an input from specified file
 */
class InputFileReader
{
public:
    InputFileReader(string fileName);

    Chain<string> *read();

protected:
    string fileName;

};

}



#endif // IO_INPUTFILEREADER_H
