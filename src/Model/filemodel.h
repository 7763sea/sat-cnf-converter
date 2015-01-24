#ifndef MODEL_FILEMODEL_H
#define MODEL_FILEMODEL_H

#include <iostream>
#include <string>

#include "Collection/chain.h"
#include "Node/abstractnode.h"

using namespace std;

using namespace Model::Collection;
using namespace Model::Node;

namespace Model
{

/**
 * @brief The FileModel class
 * Represents input and output files
 * Contains comments from input files and
 * graph structure of input expression
 */
class FileModel
{
public:
    FileModel();

    void addComment(string comment);
    void setRootGraphElement(AbstractNode *rootGraphElement);
    AbstractNode *getRootGraphElement();

    Chain<string> *getComments();

    virtual void debugOutput() = 0;
protected:
    Chain<string> *comments;
    AbstractNode *rootGraphElement;
};

}

#endif // MODEL_FILEMODEL_H
