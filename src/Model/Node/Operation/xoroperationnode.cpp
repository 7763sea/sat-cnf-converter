#include "xoroperationnode.h"
#include "../../../Model/Collection/chain.h"

using namespace Model::Node::Operation;
using namespace Model::Collection;

XorOperationNode::XorOperationNode(): AbstractOperationNode()
{
}

void XorOperationNode::debugOutput(int nestingLevel = 0)
{
    for(int i = 0; i < nestingLevel; i++) {
        cout <<  "-";
    }
    cout << " XOR " << endl;
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        child->debugOutput(nestingLevel + 1);
    }
    delete iterator;
}

XorOperationNode *XorOperationNode::clone()
{
    XorOperationNode *result = new XorOperationNode();
    cloneChildren(result);
    return result;
}

int XorOperationNode::getType()
{
    return this->TYPE_OPERATION_XOR;
}

string XorOperationNode::debugExpression()
{
    string result("(");

    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        result += child->debugExpression();
        if(true == iterator->hasNext())
            result += " XOR ";
    }

    result += ")";
    return result;
}
