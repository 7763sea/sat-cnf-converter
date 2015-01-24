#include "inputfilereader.h"

using namespace IO;

InputFileReader::InputFileReader(string fileName)
{
    this->fileName = string(fileName);
}

Chain<string> *InputFileReader::read()
{
    if((4 > fileName.size()) || (fileName.substr(fileName.size() - 4).compare(".sat") != 0))
        throw string("Input file must have .sat extension");

    Chain<string> *result = new Chain<string>();

    ifstream file(fileName.c_str());
    if(!file)
        throw string("Cannot open file ") + fileName;

    string word;
    while (getline(file, word)) {
        result->add(word);
    }

    return result;
}
