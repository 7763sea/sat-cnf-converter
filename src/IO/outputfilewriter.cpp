#include "outputfilewriter.h"

using namespace IO;

OutputFileWriter::OutputFileWriter()
{
}

void OutputFileWriter::write(string originalFileName, Chain<string> *lines)
{
    string originalFileShortName = originalFileName.substr(0, originalFileName.size() - 4);
    string newFileName = originalFileShortName + string(".cnf");

    ofstream outputFile(newFileName.c_str());
    ChainIterator<string> *iterator = lines->getIterator();
    while(true == iterator->hasNext()) {
        string line = iterator->next();
        outputFile << line;
        if(true == iterator->hasNext())
            outputFile << endl;
    }
    delete iterator;
    outputFile.close();
}
