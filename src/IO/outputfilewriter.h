#ifndef IO_OUTPUTFILEWRITER_H
#define IO_OUTPUTFILEWRITER_H

#include <iostream>
#include <string>
#include <fstream>

#include "../Model/Collection/chain.h"

using namespace std;
using namespace Model::Collection;

namespace IO
{

class OutputFileWriter
{
public:
    OutputFileWriter();

    void write(string originalFileName, Chain<string> *lines);
};

}

#endif // IO_OUTPUTFILEWRITER_H
