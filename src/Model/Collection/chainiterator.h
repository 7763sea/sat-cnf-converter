#ifndef MODEL_COLLECTION_CHAINITERATOR_H
#define MODEL_COLLECTION_CHAINITERATOR_H

#include <iostream>

#include "chainelement.h"
#include "../../Model/Node/abstractnode.h"

using namespace Model::Node;

using namespace std;

namespace Model
{
namespace Collection
{
    template <typename T>
    class Chain;

/**
 * Iterator for collection of chains
 */
template <typename T>
class ChainIterator
{
public:
    ChainIterator(Chain<T> *chain)
    {
        this->chain = chain;
        position = 0;
        currentChainElement = NULL;
        isIterationStarted = false;
    }

    T current()
    {
        return NULL == currentChainElement ? NULL : currentChainElement->getContent();
    }

    ChainElement<T> *getCurrentChainElement()
    {
        return currentChainElement;
    }

    T next()
    {
        if(position == chain->getSize())
            return NULL;

        if(true == isIterationStarted && NULL != currentChainElement) {
            currentChainElement = currentChainElement->getNext();
            position++;
        } else {
            position = 0;
            isIterationStarted = true;
            currentChainElement = chain->getFirstChainElement();
        }
        if(NULL == currentChainElement)
            return NULL;
        return current();
    }

    void removeCurrent()
    {
        if(NULL == currentChainElement)
            return;

        if(NULL != currentChainElement->getNext())
            currentChainElement->getNext()->setPrevious(currentChainElement->getPrevious());
        if(NULL != currentChainElement->getPrevious())
            currentChainElement->getPrevious()->setNext(currentChainElement->getNext());

        if(chain->getFirstChainElement() == currentChainElement)
            chain->setFirstChainElement(currentChainElement->getNext());
        if(chain->getLastChainElement() == currentChainElement)
            chain->setLastChainElement(currentChainElement->getPrevious());

        ChainElement<T> *previous = currentChainElement->getPrevious();
        delete currentChainElement;
        if(NULL == previous) {
            position = 0;
            isIterationStarted = false;
            currentChainElement = chain->getFirstChainElement();
        } else {
            currentChainElement = previous;
        }

        chain->setSize(chain->getSize() - 1);
        if(0 < position)
            position--;

        if(0 == chain->getSize()) {
            isIterationStarted = false;
            position = 0;
            currentChainElement = NULL;
        }

    }

    void replaceCurrent(T newObject)
    {
        if(NULL == currentChainElement)
            return;

        ChainElement<T> *previous = currentChainElement->getPrevious();
        ChainElement<T> *next = currentChainElement->getNext();
        ChainElement<T> *newElement = new ChainElement<T>(newObject);

        newElement->setPrevious(previous);
        if(NULL != previous) {
            previous->setNext(newElement);
        }

        newElement->setNext(next);
        if(NULL != next) {
            next->setPrevious(newElement);
        }

        if(chain->getFirstChainElement() == currentChainElement) {
            chain->setFirstChainElement(newElement);
        }

        if(chain->getLastChainElement() == currentChainElement) {
            chain->setLastChainElement(newElement);
        }

        currentChainElement->setPrevious(NULL);
        currentChainElement->setNext(NULL);
        delete currentChainElement;
        currentChainElement = newElement;
    }


    bool hasNext()
    {
        if(false == isIterationStarted) {
            return (0 < chain->getSize());
        };
        if(true == (currentChainElement && currentChainElement->getNext()))
            return true;

        return false;
    }

protected:
    Chain<T> *chain;
    ChainElement<T> *currentChainElement;
    unsigned long long position;
    bool isIterationStarted;
};

}}

#include "chainiterator.cpp"


#endif // MODEL_COLLECTION_CHAINITERATOR_H
