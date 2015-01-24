#ifndef MODEL_NODE_OPERATION_NOTOPERATIONNODE_H
#define MODEL_NODE_OPERATION_NOTOPERATIONNODE_H

#include <iostream>

#include "../abstractnode.h"
#include "abstractoperationnode.h"

using namespace std;

namespace Model
{
namespace Node
{
namespace Operation
{

class NotOperationNode: public AbstractOperationNode
{
public:
    NotOperationNode();
    int getType();
    void debugOutput(int nestingLevel);
    string debugExpression();

    NotOperationNode *clone();
};

}
}
}

#endif // MODEL_NODE_OPERATION_NOTOPERATIONNODE_H
