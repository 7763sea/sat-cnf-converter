#include "andoperationnode.h"
#include "../../../Model/Collection/chain.h"

using namespace Model::Node::Operation;
using namespace Model::Collection;

AndOperationNode::AndOperationNode(): AbstractOperationNode()
{
}

void AndOperationNode::debugOutput(int nestingLevel = 0)
{
    for(int i = 0; i < nestingLevel; i++) {
        cout <<  "-";
    }
    cout << " AND " << endl;
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        child->debugOutput(nestingLevel + 1);
    }
    delete iterator;
}

AndOperationNode *AndOperationNode::clone()
{
    AndOperationNode *result = new AndOperationNode();
    cloneChildren(result);
    return result;
}

int AndOperationNode::getType()
{
    return this->TYPE_OPERATION_AND;
}

string AndOperationNode::debugExpression()
{
    string result("(");
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();

        result += child->debugExpression();
        if(true == iterator->hasNext())
            result += " AND ";
    }
    delete iterator;
    result += ")";
    return result;
}
