#ifndef MODEL_NODE_FALSENODE_H
#define MODEL_NODE_FALSENODE_H

#include <iostream>
#include <sstream>
#include "abstractnode.h"

using namespace std;

namespace Model
{
namespace Node
{

class FalseNode: public AbstractNode
{
public:
    FalseNode();
    void debugOutput(int nestingLevel);
    string debugExpression();

    int getType();
    FalseNode *clone();
};

}}

#endif // MODEL_NODE_FALSENODE_H
