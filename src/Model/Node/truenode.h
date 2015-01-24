#ifndef MODEL_NODE_TRUENODE_H
#define MODEL_NODE_TRUENODE_H

#include <iostream>
#include <sstream>
#include "abstractnode.h"

using namespace std;

namespace Model
{
namespace Node
{

class TrueNode: public AbstractNode
{
public:
    TrueNode();
    void debugOutput(int nestingLevel);
    string debugExpression();

    int getType();
    TrueNode *clone();
};

}}

#endif // MODEL_NODE_TRUENODE_H
