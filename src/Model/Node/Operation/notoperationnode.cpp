#include "notoperationnode.h"
#include "../../../Model/Collection/chain.h"

using namespace Model::Node::Operation;
using namespace Model::Node;
using namespace Model::Collection;

NotOperationNode::NotOperationNode(): AbstractOperationNode()
{

}

void NotOperationNode::debugOutput(int nestingLevel = 0)
{
    for(int i = 0; i < nestingLevel; i++) {
        cout <<  "-";
    }
    cout << " NOT " << endl;
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        child->debugOutput(nestingLevel + 1);
    }
    delete iterator;
}

NotOperationNode *NotOperationNode::clone()
{
    NotOperationNode *result = new NotOperationNode();
    cloneChildren(result);
    return result;
}

int NotOperationNode::getType()
{
    return this->TYPE_OPERATION_NOT;
}

string NotOperationNode::debugExpression()
{
    AbstractNode *child = children->getFirstElement();
    string result = child ? child->debugExpression() : string("EMPTY");
    result = string("!") += result;
    return result;
}
