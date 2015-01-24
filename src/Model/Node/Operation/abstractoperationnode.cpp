#include "abstractoperationnode.h"

using namespace Model::Node::Operation;

AbstractOperationNode::~AbstractOperationNode()
{

}

AbstractOperationNode::AbstractOperationNode():AbstractNode()
{
}

int AbstractOperationNode::getType()
{
    return this->TYPE_OPERATION_ABSTRACT;
}
