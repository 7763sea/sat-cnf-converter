#include "sattocnftranslator.h"

using namespace Translator;

SatToCnfTranslator::SatToCnfTranslator(bool debugMode)
{
    numLastIterationUpdates = -1;
    this->debugMode = debugMode;
}


AbstractNode *SatToCnfTranslator::translate(AbstractNode *input)
{
    originalGraph = input;
    translatedGraph = input->clone();
    if(true == debugMode) {
        cout << "Graph before translation:" << translatedGraph->debugExpression() << endl;
    }

    translatedGraph = convertComplexToConjunction(translatedGraph, 0);
    if(true == debugMode) {
        cout << "Graph after complex operators were replaced:" << translatedGraph->debugExpression() << endl;
    }

    unsigned long long numModifications = 1;
    while(0 < numModifications) {
        numModifications = 0;
        translatedGraph = optimize(translatedGraph, &numModifications);
        if(true == debugMode) {
            cout << "Iteration passed. Graphg after optimization:" << translatedGraph->debugExpression() << endl;
        }
    }

    //If translated graph is OR operation, put it into AND operation
    if(AbstractNode::TYPE_OPERATION_OR == translatedGraph->getType()) {
        AndOperationNode *newAnd = new AndOperationNode();
        newAnd->addChild(translatedGraph->clone());
        translatedGraph = newAnd;
    } else if(AbstractNode::TYPE_TRUE == translatedGraph->getType()) {
        throw new ExpressionEqualsTrueException();
    } else if(AbstractNode::TYPE_FALSE == translatedGraph->getType()) {
        throw new ExpressionEqualsFalseException();
    }

    //Force remove of duplications at the end
    numModifications = 0;
    translatedGraph = TranslationUtil::removeDuplications(translatedGraph, true, &numModifications);


    return translatedGraph;
}

AbstractNode *SatToCnfTranslator::convertComplexToConjunction(AbstractNode *parentElement, int nestingLevel)
{
    string debugString("");
    for(int i = 0; i < nestingLevel; i++) {
        debugString += string("-");
    }
    debugString += string(" ");

    AbstractNode *newParentElement = parentElement->clone();
    ChainIterator<AbstractNode*> *iterator = newParentElement->getChildren()->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *childElement = iterator->next();

        if(NULL == childElement) //child element is not operation: omit it
            continue;
        childElement = convertComplexToConjunction(childElement, nestingLevel + 1);
        iterator->replaceCurrent(childElement);
    }
    delete iterator;

    switch(newParentElement->getType()) {
        case AbstractNode::TYPE_OPERATION_EQUIVALENCE:
            newParentElement = translateEquivalence(newParentElement);
            break;

        case AbstractNode::TYPE_OPERATION_XOR:
            newParentElement = translateXor(newParentElement);
            break;
    }
    return newParentElement;
}

AbstractNode *SatToCnfTranslator::translateEquivalence(AbstractNode *element)
{
    if(2 != element->getChildren()->getSize())
        return element;

    AndOperationNode *newConjunction = new AndOperationNode();

    ChainElement<AbstractNode*> *firstChainElement = element->getChildren()->getFirstChainElement();
    AbstractNode *firstChild = firstChainElement->getContent()->clone();
    AbstractNode *secondChild = firstChainElement->getNext()->getContent();

    //x1 EUQAL x2 = (NOT x1 OR x2) AND (x1 OR NOT x2)
    OrOperationNode *firstOr = new OrOperationNode();
    OrOperationNode *secondOr = new OrOperationNode();

    //First OR
    if(AbstractNode::TYPE_OPERATION_NOT == firstChild->getType()) {
        AbstractNode *grandChild = firstChild->getChildren()->getFirstElement();
        firstOr->addChild(grandChild->clone());
    } else {
        NotOperationNode *firstOneNot = new NotOperationNode();
        firstOneNot->addChild(firstChild->clone());
        firstOr->addChild(firstOneNot);
    }
    firstOr->addChild(secondChild->clone());

    //Second OR
    secondOr->addChild(firstChild->clone());
    if(AbstractNode::TYPE_OPERATION_NOT == secondChild->getType()) {
        AbstractNode *grandChild = secondChild->getChildren()->getFirstElement();
        secondOr->addChild(grandChild->clone());
    } else {
        NotOperationNode *secondTwoNot = new NotOperationNode();
        secondTwoNot->addChild(secondChild->clone());
        secondOr->addChild(secondTwoNot);
    }
    newConjunction->addChild(firstOr);
    newConjunction->addChild(secondOr);
    return newConjunction;
}

AbstractNode *SatToCnfTranslator::translateXor(AbstractNode *element)
{
    if(2 != element->getChildren()->getSize())
        return element;

    AndOperationNode *newConjunction = new AndOperationNode();

    ChainElement<AbstractNode*> *firstChainElement = element->getChildren()->getFirstChainElement();
    AbstractNode *firstChild = firstChainElement->getContent()->clone();
    AbstractNode *secondChild = firstChainElement->getNext()->getContent();

    // x1 XOR x2 = (NOT x1 OR NOT x2) AND (x1 OR x2)

    OrOperationNode *firstOr = new OrOperationNode();
    OrOperationNode *secondOr = new OrOperationNode();

    //First OR
    if(AbstractNode::TYPE_OPERATION_NOT == firstChild->getType()) {
        AbstractNode *grandChild = firstChild->getChildren()->getFirstElement();
        firstOr->addChild(grandChild->clone());
    } else {
        NotOperationNode *firstOneNot = new NotOperationNode();
        firstOneNot->addChild(firstChild->clone());
        firstOr->addChild(firstOneNot);
    }
    if(AbstractNode::TYPE_OPERATION_NOT == secondChild->getType()) {
        AbstractNode *grandChild = secondChild->getChildren()->getFirstElement();
        firstOr->addChild(grandChild->clone());
    } else {
        NotOperationNode *secondOneNot = new NotOperationNode();
        secondOneNot->addChild(secondChild->clone());
        firstOr->addChild(secondOneNot);
    }

    //Second OR
    secondOr->addChild(firstChild->clone());
    secondOr->addChild(secondChild->clone());

    newConjunction->addChild(firstOr);
    newConjunction->addChild(secondOr);

    return newConjunction;
}

AbstractNode *SatToCnfTranslator::eliminateComplexNotOperators(AbstractNode *element, unsigned long long *numModifications)
{
    AbstractNode *newElement = element->clone();
    //Apply replacement operation to children
    ChainIterator<AbstractNode*> *iterator = newElement->getChildren()->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        child = eliminateComplexNotOperators(child, numModifications);
        iterator->replaceCurrent(child);
    }
    delete iterator;

    if(AbstractNode::TYPE_OPERATION_NOT != newElement->getType())
        return newElement;

    AbstractNode *childElement = newElement->getChildren()->getFirstElement();
    if(AbstractNode::TYPE_OPERATION_NOT == childElement->getType()) {
        AbstractNode *grandChildElement = childElement->getChildren()->getFirstElement();
        newElement = grandChildElement->clone();
        *numModifications = *numModifications + 1;
    } else if(AbstractNode::TYPE_OPERATION_AND == childElement->getType()
            || AbstractNode::TYPE_OPERATION_OR == childElement->getType() ) {
        AbstractNode *deMorganNode = TranslationUtil::applyDeMorgansLaws(childElement);
        AbstractNode *deModganChildNode = deMorganNode->getChildren()->getFirstElement();
        newElement = deModganChildNode->clone();
        *numModifications = *numModifications + 1;
    }
    delete element;
    return newElement;
}

AbstractNode *SatToCnfTranslator::optimize(AbstractNode *element, unsigned long long *numModifications)
{
    AbstractNode *newElement = element->clone();
    ChainIterator<AbstractNode*> *iterator = newElement->getChildren()->getIterator();
    //Apply replacement operation to children
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        unsigned long long numChildModifications = 0;
        child = optimize(child, &numChildModifications);
        iterator->replaceCurrent(child);        
    }
    delete iterator;

    //If OR operation is DNF, translate it to CNF
    if(element->isDisjunctionOfComplexConjunctions() && 0 == *numModifications) {
        newElement = translateDnfToCnf(newElement, numModifications);
    }

    switch(newElement->getType()) {
        case AbstractNode::TYPE_OPERATION_OR:
            newElement = optimizeOr(newElement, numModifications);
            break;
        case AbstractNode::TYPE_OPERATION_AND:
            newElement = optimizeAnd(newElement, numModifications);
            break;
    }
    //Further procesing
    newElement = eliminateComplexNotOperators(newElement, numModifications);;
    newElement = TranslationUtil::eliminateOppositeMembers(newElement, numModifications);
    newElement = TranslationUtil::eliminateMembersWithConstants(newElement, numModifications);
    newElement = TranslationUtil::removeDuplications(newElement, false, numModifications);
    newElement = TranslationUtil::sortChildren(newElement);
    delete element;
    return newElement;
}

AbstractNode *SatToCnfTranslator::translateDnfToCnf(AbstractNode *element, unsigned long long *numModifications)
{
    if(AbstractNode::TYPE_OPERATION_OR != element->getType())
        return element;

    //Fill array with elements
    Chain<Chain<AbstractNode*>*> *allElements = new Chain<Chain<AbstractNode*>*>();
    Chain<unsigned long long> *lengths = new Chain<unsigned long long>();


    ChainIterator<AbstractNode*> *childrenIterator = element->getChildren()->getIterator();
    while(true == childrenIterator->hasNext()) {
        AbstractNode *child = childrenIterator->next();
        if(child->isSingleVariable()) {
            Chain<AbstractNode*> *childProxy = new Chain<AbstractNode*>();
            childProxy->add(child);
            allElements->add(childProxy);
            lengths->add(childProxy->getSize());
        } else {
            allElements->add(child->getChildren());
            lengths->add(child->getChildren()->getSize());
        }
    }
    delete childrenIterator;

    //Calculate total number of elements in conjunction
    unsigned long long int sizeOfNewConjunction = 1;
    ChainIterator<Chain<AbstractNode*>*> *iterator = allElements->getIterator();
    while(true == iterator->hasNext()) {
        Chain<AbstractNode*> *conjunction = iterator->next();
        sizeOfNewConjunction = sizeOfNewConjunction * conjunction->getSize();
    }
    delete iterator;

    /*
     *
    AndOperationNode *newElement = new AndOperationNode();
    ChainIterator<AbstractNode*> *disjIterator = disjunctions->getIterator();
    while(true == disjIterator->hasNext()) {
        AbstractNode *disjunction = disjIterator->next();
        disjunction = disjunction->clone();
        newElement->addChild(disjunction);
    }
    delete disjIterator;
     */

    //Iterate through elements in disjunction and build elements for conjunction
    Chain<AbstractNode*> *disjunctions = new Chain<AbstractNode*>();
    AndOperationNode *newElement = new AndOperationNode();
    for(unsigned long long i = 0; i < sizeOfNewConjunction; i++) {
        OrOperationNode *newDisjunction = new OrOperationNode();

        //Calculate indexes for new disjunction. Using division by module
        unsigned long long int remain = i; //Remain from division by module
        ChainIterator<Chain<AbstractNode*>*> *chainIterator = allElements->getIterator();
        while(true == chainIterator->hasNext()) {          
            Chain<AbstractNode*> *conjunction = chainIterator->next();
            //Calculate a number for division by
            //Look further elements and multiply their lengths
            unsigned long long int rankFactor  = 1;
            ChainElement<Chain<AbstractNode*>*> *factorConjunctionChainElement = chainIterator
                ->getCurrentChainElement()->getNext();
            while(NULL != factorConjunctionChainElement) {
                Chain<AbstractNode*> *factorConjunction = factorConjunctionChainElement->getContent();
                rankFactor = rankFactor * factorConjunction->getSize();
                factorConjunctionChainElement = factorConjunctionChainElement->getNext();
            }
            unsigned long long elementIndex = (int)floor(remain / rankFactor);
            remain = remain % rankFactor;

            AbstractNode *conjunctionElement = conjunction->seek(elementIndex)->getContent();
            AbstractNode *clonedNode = conjunctionElement->clone();
            newDisjunction->addChild(clonedNode);
        }
        delete chainIterator;
        //disjunctions->add(newDisjunction);
        newElement->addChild(newDisjunction);
    }

//    AndOperationNode *newElement = new AndOperationNode();
//    ChainIterator<AbstractNode*> *disjIterator = disjunctions->getIterator();
//    while(true == disjIterator->hasNext()) {
//        AbstractNode *disjunction = disjIterator->next();
//        disjunction = disjunction->clone();
//        newElement->addChild(disjunction);
//    }
//    delete disjIterator;

    delete allElements;
    delete lengths;
    delete disjunctions;
    delete element;
    *numModifications = *numModifications + 1;
    return newElement;
}

AbstractNode *SatToCnfTranslator::optimizeAnd(AbstractNode *element, unsigned long long *numModifications)
{
    if(AbstractNode::TYPE_OPERATION_AND != element->getType())
        return element;
    AbstractNode *newElement = element->clone();

    unsigned long long numChildren = element->getChildren()->getSize();
    // *() = FALSE
    if(0 == numChildren) {
        delete newElement;
        newElement = new FalseNode();
        return newElement;
    }

    ChainIterator<AbstractNode*> *iterator = newElement->getChildren()->getIterator();
    AbstractNode *child = iterator->next();
    while(NULL != child) {
        child = iterator->current();
        if(NULL == child)
            break;

        //Move all AND children elements to upper level
        if(AbstractNode::TYPE_OPERATION_AND == child->getType()) {
            ChainIterator<AbstractNode*> *childIterator = child->getChildren()->getIterator();
            while(true == childIterator->hasNext()) {
                newElement->addChild(childIterator->next());
            }
            iterator->removeCurrent();
            numChildren = element->getChildren()->getSize();
            *numModifications = *numModifications + 1;
        } else {
            child = iterator->next();
        }
    }
    delete iterator;

    delete element;
    return newElement;
}

AbstractNode *SatToCnfTranslator::optimizeOr(AbstractNode *element, unsigned long long *numModifications)
{
    if(AbstractNode::TYPE_OPERATION_OR != element->getType())
        return element;
    AbstractNode *newElement = element->clone();


    unsigned long long numChildren = element->getChildren()->getSize();
    // +() = TRUE
    if(0 == numChildren) {
        delete newElement;
        newElement = new TrueNode();
        return newElement;
    }

    ChainIterator<AbstractNode*> *outerIterator = newElement->getChildren()->getIterator();
    AbstractNode *child = outerIterator->next();
    while(NULL != child) {

        child = outerIterator->current();
        if(NULL == child)
            break;

        //Move all OR children elements to upper level
        if(AbstractNode::TYPE_OPERATION_OR == child->getType()) {
            ChainIterator<AbstractNode*> *iterator = child->getChildren()->getIterator();
            while(true == iterator->hasNext()) {
                AbstractNode *grandChild = iterator->next();
                newElement->addChild(grandChild->clone());
            }
            delete iterator;
            outerIterator->removeCurrent();
            numChildren = element->getChildren()->getSize();
            *numModifications = *numModifications + 1;
        } else {
            child = outerIterator->next();
        }
    }
    delete outerIterator;
    delete element;
    return newElement;
}
