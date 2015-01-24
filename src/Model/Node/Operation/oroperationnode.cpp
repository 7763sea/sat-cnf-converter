#include "oroperationnode.h"
#include "../../../Model/Collection/chain.h"

using namespace Model::Node::Operation;
using namespace Model::Collection;

OrOperationNode::OrOperationNode(): AbstractOperationNode()
{
}

void OrOperationNode::debugOutput(int nestingLevel = 0)
{
    for(int i = 0; i < nestingLevel; i++) {
        cout <<  "-";
    }
    cout << " OR " << endl;
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        child->debugOutput(nestingLevel + 1);
    }
    delete iterator;
}

OrOperationNode *OrOperationNode::clone()
{
    OrOperationNode *result = new OrOperationNode();
    cloneChildren(result);
    return result;
}

int OrOperationNode::getType()
{
    return this->TYPE_OPERATION_OR;
}

string OrOperationNode::debugExpression()
{
    string result("(");
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    unsigned long long i = 0;
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        result += child->debugExpression();
        if(true == iterator->hasNext())
            result += " OR ";
        i++;
    }
    delete iterator;
    result += ")";
    return result;
}
