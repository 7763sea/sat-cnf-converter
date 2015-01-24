#ifndef MODEL_NODE_OPERATION_XOROPERATIONNODE_H
#define MODEL_NODE_OPERATION_XOROPERATIONNODE_H

#include <iostream>

#include "abstractoperationnode.h"

using namespace std;

namespace Model
{
namespace Node
{
namespace Operation
{

class XorOperationNode: public AbstractOperationNode
{
public:
    XorOperationNode();
    int getType();
    void debugOutput(int nestingLevel);
    string debugExpression();

    XorOperationNode *clone();
};

}
}
}

#endif // MODEL_NODE_OPERATION_XOROPERATIONNODE_H
