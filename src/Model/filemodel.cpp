#include "filemodel.h"

using namespace std;
using namespace Model;

FileModel::FileModel()
{
    comments = new Chain<string>();
}

void FileModel::addComment(string comment)
{
    this->comments->add(comment);
}

void FileModel::setRootGraphElement(AbstractNode *rootGraphElement)
{
    this->rootGraphElement = rootGraphElement;
}

AbstractNode *FileModel::getRootGraphElement()
{
    return rootGraphElement;
}

Chain<string> *FileModel::getComments()
{
    return comments;
}
