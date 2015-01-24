#include "translationutil.h"
#include "../Model/Collection/chain.h"

using namespace Utils;
using namespace Model::Collection;

TranslationUtil::TranslationUtil()
{
}

AbstractNode *TranslationUtil::applyDeMorgansLaws(AbstractNode *operation)
{
    //Apply rules on children
    ChainIterator<AbstractNode*> *iterator = operation->getChildren()->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *newChild = TranslationUtil::applyDeMorgansLaws(iterator->next());
        iterator->replaceCurrent(newChild);
    }
    delete iterator;

    //Apply rules on node itself
    AbstractNode *newOperation = NULL;
    if(AbstractNode::TYPE_OPERATION_AND == operation->getType()) {
        newOperation = new OrOperationNode();
    } else if(AbstractNode::TYPE_OPERATION_OR == operation->getType()) {
        newOperation = new AndOperationNode();
    } else {
        return operation;
    }
    NotOperationNode *rootNotOperation = new NotOperationNode();

    //Copy children
    ChainIterator<AbstractNode*> *iteratorSecond = operation->getChildren()->getIterator();
    while(true == iteratorSecond->hasNext()) {
        AbstractNode *child = iteratorSecond->next();
        if(AbstractNode::TYPE_OPERATION_NOT == child->getType()) {
            //Purpose: eliminate such expressions as NOT(NOT(x))
            AbstractNode *grandChild = child->getChildren()->getFirstElement();
            newOperation->addChild(grandChild);
        } else {
            AbstractNode *childNot = new NotOperationNode();
            childNot->addChild(child);
            newOperation->addChild(childNot);
        }

    }
    delete iteratorSecond;
    rootNotOperation ->addChild(newOperation);
    delete operation;
    return rootNotOperation;
}

AbstractNode *TranslationUtil::convertToBinaryTree(AbstractNode *operation)
{
    if(AbstractNode::TYPE_VARIABLE == operation->getType())
        return operation;

    AbstractNode *newElement = operation->clone();
    ChainIterator<AbstractNode*> *iterator = newElement->getChildren()->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        if(AbstractNode::TYPE_VARIABLE != child->getType()) {
            child = TranslationUtil::convertToBinaryTree(child);
            iterator->replaceCurrent(child);
        }
    }
    delete iterator;

    unsigned long long childrenSize = newElement->getChildren()->getSize();
    if(childrenSize < 2)
        return newElement;

    AbstractNode *newParentNode = NULL;
    iterator = newElement->getChildren()->getIterator();
    while(NULL != iterator->current() && NULL != iterator->getCurrentChainElement()->getNext()) {
        iterator->next();
        AbstractNode *newNode = NodeFactory::getInstance(newElement);
        if(NULL == newParentNode) {
            AbstractNode *firstBinabyChild = iterator->current(); //TODO: compare with original!
            firstBinabyChild = firstBinabyChild->clone();
            newNode->addChild(firstBinabyChild);
        } else {
            newNode->addChild(newParentNode);
        }
        AbstractNode *secondBinabyChild = iterator->getCurrentChainElement()->getNext()->getContent(); //TODO: compare with original!
        secondBinabyChild = secondBinabyChild->clone();
        newNode->addChild(secondBinabyChild);

        newParentNode = newNode;
    }
    delete iterator;
    delete operation;
    return newParentNode;
}

AbstractNode *TranslationUtil::removeDuplications(AbstractNode *node, bool forceCheck, unsigned long long *numModifications)
{
    AbstractNode *newNode = node->clone();
    Chain<AbstractNode*> *buffer = new Chain<AbstractNode*>();
    Chain<string> *expressionsBuffer = new Chain<string>();

    //Fill buffer with unique children
    ChainIterator<AbstractNode*> *iterator = newNode->getChildren()->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        string childExpression = child->debugExpression();

        //Avoid performance loose when trying to look for duplicates in complicated expressions
        bool isElementFound = false;
        if(true == child->isSingleVariable() || true == forceCheck) {
            //Check if node already exists in buffer

            ChainIterator<string> *stringIterator = expressionsBuffer->getIterator();
            while(true == stringIterator->hasNext()) {
                string bufferExpression = stringIterator->next();
                if(StringUtil::equals(bufferExpression, childExpression)) {
                    isElementFound = true;
                    break;
                }
            }
        }

        if(true == isElementFound) {
            //Don't add duplicated element. Consequently, array was changed.
            *numModifications = *numModifications + 1;
        } else {
            expressionsBuffer->add(childExpression);
            buffer->add(child->clone());
        }
    }

    delete iterator;
    //Clear children
    iterator = newNode->getChildren()->getIterator();
    while(true == iterator->hasNext()) {
        iterator->next();
        iterator->removeCurrent();
    }

    delete iterator;
    //Append children from buffer
    iterator = buffer->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        newNode->addChild(child->clone());
    }

    delete iterator;
    delete buffer;
    delete expressionsBuffer;
    delete node;
    return newNode;
}

AbstractNode *TranslationUtil::sortChildren(AbstractNode *node)
{
    //Sort is appliable only for elements with simple children
    if(false == node->consistsFromSimpleElements())
        return node;

    AbstractNode *newNode = node->clone();
    //Clear children
    ChainIterator<AbstractNode*> *removeIterator = newNode->getChildren()->getIterator();
    while(true == removeIterator->hasNext()) {
        removeIterator->next();
        removeIterator->removeCurrent();
    }
    delete removeIterator;

    AbstractNode *buffer = node->clone();
    while(0 < buffer->getChildren()->getSize()) {
        int minValue = -1;
        unsigned long long minValueIndex = -1;
        unsigned long long valueIndex = -1;
        ChainIterator<AbstractNode*> *iterator = buffer->getChildren()->getIterator();
        while(true == iterator->hasNext()) {
            valueIndex++;
            AbstractNode *child = iterator->next();
            AbstractNode *childVariable = NULL;
            bool isOperationNot = false; //Extra points for operations NOT
            if(AbstractNode::TYPE_VARIABLE == child->getType()) {
                childVariable = child;
            } else if(AbstractNode::TYPE_OPERATION_NOT == child->getType()) {
                AbstractNode *grandChild = child->getChildren()->getFirstElement();
                childVariable = grandChild;
                isOperationNot = true;
            }
            VariableNode *childVariableCast = static_cast<VariableNode*>(childVariable);
            int value = childVariableCast->getVariable() * 2;
            if(true == isOperationNot)
                value++;

            if(value < minValue || -1 == minValue) {
                minValue = value;
                minValueIndex = valueIndex;
            }
        }
        delete iterator;

        AbstractNode *minElement = buffer->getChildren()->seek(minValueIndex)->getContent();
        minElement = minElement->clone();
        newNode->addChild(minElement);

        iterator = buffer->getChildren()->getIterator();
        unsigned long long index = -1;
        while(true == iterator->hasNext()) {
            iterator->next();
            index++;
            if(index == minValueIndex) {
                iterator->removeCurrent();
                break;
            }
        }
        delete iterator;
    }    
    delete node;
    return newNode;
}

AbstractNode *TranslationUtil::eliminateOppositeMembers(AbstractNode *node, unsigned long long *numModifications)
{

    //Function is appliable only for functions like AND and OR
    if(!(AbstractNode::TYPE_OPERATION_AND == node->getType()
            || AbstractNode::TYPE_OPERATION_OR == node->getType()))
        return node;

    AbstractNode *newNode = node->clone();
    bool isNodeUpdated = true;
    while(true == isNodeUpdated) { //Continue loop unless all opposite elements are updated

        isNodeUpdated = false;
        unsigned long long firstVariablePosition = -1;
        ChainIterator<AbstractNode*> *iterator = newNode->getChildren()->getIterator();
        AbstractNode *child = iterator->next();
        while(NULL != child) { //Check all elements

            child = iterator->current();
            if(NULL == child)
                break;

            firstVariablePosition++;
            bool isOppositeElementFound = false;
            if(false == child->isSingleVariable()) {
                //Current node is not a variable. Omit it.
                iterator->next();
                continue;
            }

            //Get the first variable
            VariableNode *firstVariable = NULL;
            bool isFirstNotOperation = false;
            if(AbstractNode::TYPE_VARIABLE == child->getType()) {
                firstVariable = static_cast<VariableNode*>(child);
            } else if(AbstractNode::TYPE_OPERATION_NOT == child->getType()) {
                isFirstNotOperation = true;
                firstVariable = static_cast<VariableNode*>(child->getChildren()->getFirstElement());
            }

            //Get the second variable
            VariableNode *secondVariable;
            bool isSecondNotOperation = false;
            AbstractNode *second = NULL;
            ChainElement<AbstractNode*> *secondChainElement = iterator
                    ->getCurrentChainElement()->getNext();
            if(NULL != secondChainElement) {
                second = secondChainElement->getContent();
            }

            unsigned long long secondVariablePosition = -1;
            while(second != NULL) {

                secondVariablePosition++;
                if(false == second->isSingleVariable()) {
                    secondChainElement = secondChainElement->getNext();
                    second = NULL == secondChainElement ? NULL : secondChainElement->getContent();
                    continue;
                }

                if(AbstractNode::TYPE_OPERATION_NOT == second->getType()) {
                    isSecondNotOperation = true;
                    secondVariable = static_cast<VariableNode*>(second->getChildren()->getFirstElement());
                } else {
                    isSecondNotOperation = false;
                    secondVariable = static_cast<VariableNode*>(second);
                }

                isOppositeElementFound = firstVariable->getVariable() == secondVariable->getVariable() &&
                        isFirstNotOperation == !isSecondNotOperation;

                if(true == isOppositeElementFound) {
                    break;
                }
                secondChainElement = secondChainElement->getNext();
                second = NULL == secondChainElement ? NULL : secondChainElement->getContent();
            }

            //If opposite element is found, replace two children elements with new one
            if(true == isOppositeElementFound) {
                AbstractNode *updatedElement = NULL;
                if(AbstractNode::TYPE_OPERATION_AND == newNode->getType()) {
                    //x AND NOT x = FALSE
                    updatedElement = new FalseNode();
                } else if(AbstractNode::TYPE_OPERATION_OR == newNode->getType()) {
                    //x OR NOT x = TRUE
                    updatedElement = new TrueNode();
                }

                ChainIterator<AbstractNode*> *iterator = newNode->getChildren()->getIterator();
                unsigned long long loopIndex = -1;
                while(true == iterator->hasNext()) {
                    loopIndex++;
                    iterator->next();
                    if(loopIndex == firstVariablePosition) {
                        iterator->replaceCurrent(updatedElement);
                    } else if(loopIndex == secondVariablePosition) {
                        iterator->removeCurrent();
                    }
                }
                isNodeUpdated = true;
                *numModifications = *numModifications + 1;
            }
            child = iterator->next(); //Opposite elements not found: move to next element
        }
        delete iterator;
    }
    delete node;
    return newNode;
}

AbstractNode *TranslationUtil::eliminateMembersWithConstants(AbstractNode *node, unsigned long long *numModifications)
{

    //Function is appliable only for functions like AND and OR
    if(!(AbstractNode::TYPE_OPERATION_AND == node->getType()
            || AbstractNode::TYPE_OPERATION_OR == node->getType()))
        return node;

    bool isConjunction = AbstractNode::TYPE_OPERATION_AND == node->getType();
    bool isDisjunction = AbstractNode::TYPE_OPERATION_OR == node->getType();

    AbstractNode *newNode = node->clone();
    Chain<AbstractNode*> *newNodeChildren = newNode->getChildren();
    ChainIterator<AbstractNode*> *iterator = newNode->getChildren()->getIterator();
    AbstractNode *child = iterator->next();
    while(NULL != child) { //Check all elements

        bool isIncrementNeeded = true;
        AbstractNode *child = iterator->current();
        if(NULL == child)
            break;

        if(AbstractNode::TYPE_TRUE == child->getType() && true == isConjunction) {
            // a AND TRUE = a
            *numModifications = *numModifications + 1;
            if(1 < newNodeChildren->getSize()) {
                iterator->removeCurrent();
                isIncrementNeeded = false;
            } else {
                delete newNode;
                newNode = new TrueNode();
                break;
            }
        } else if(AbstractNode::TYPE_TRUE == child->getType() && true == isDisjunction) {
            //a OR TRUE = TRUE
            delete newNode;
            newNode = new TrueNode();
            *numModifications = *numModifications + 1;
            break;
        } else if(AbstractNode::TYPE_FALSE == child->getType() && true == isConjunction) {
            //a AND FALSE = FALSE
            delete newNode;
            newNode = new FalseNode();
            *numModifications = *numModifications + 1;
            break;
        } else if(AbstractNode::TYPE_FALSE == child->getType() && true == isDisjunction) {
            //a OR FALSE = a
            *numModifications = *numModifications + 1;
            if(1 < newNodeChildren->getSize()) {
                iterator->removeCurrent();
                isIncrementNeeded = false;
            } else {
                delete newNode;
                newNode = new FalseNode();
                break;
            }
        }

        if(true == isIncrementNeeded) {
            child = iterator->next();
        }

    }
    delete iterator;
    delete node;
    return newNode;
}
