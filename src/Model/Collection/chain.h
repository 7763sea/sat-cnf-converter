#ifndef MODEL_COLLECTION_CHAIN_H
#define MODEL_COLLECTION_CHAIN_H

#include <stddef.h>
#include <iostream>
#include <memory>

#include "chainelement.h"
#include "chainiterator.h"

using namespace std;

namespace Model
{
namespace Collection
{

/**
 * Chain of elements. Allows to save infinite number of elements
 */
template <typename T>
class Chain
{
public:
    Chain()
    {
        firstChainElement = NULL;
        lastChainElement = NULL;
        size = 0;
    }

    ~Chain()
    {
        ChainElement<T> *elem = firstChainElement;
        while(NULL != elem) {
            ChainElement<T> *nextElem = elem->getNext();
            delete elem;
            elem = nextElem;
        }
    }

    T getFirstElement()
    {
        return firstChainElement ? firstChainElement->getContent() : NULL;
    }

    T getLastElement()
    {
        return lastChainElement ? lastChainElement->getContent() : NULL;
    }

    ChainElement<T> *getFirstChainElement()
    {
        return firstChainElement;
    }

    void setFirstChainElement(ChainElement<T> *element)
    {
        this->firstChainElement = element;
    }

    ChainElement<T> *getLastChainElement()
    {
        return lastChainElement;
    }

    void setLastChainElement(ChainElement<T> *element)
    {
        this->lastChainElement = element;
    }

    ChainElement<T> *seek(unsigned long long position)
    {
        unsigned long long i = 0;
        ChainElement<T> *result = firstChainElement;
        while(i < position) {
            result = result->getNext();
            i++;
        }
        return result;
    }

    unsigned long long getSize()
    {
        return size;
    }

    void setSize(unsigned long long size)
    {
        this->size = size;
    }

    void add(T element)
    {
        ChainElement<T> *newElement = new ChainElement<T>(element);
        if(lastChainElement == NULL) {
            firstChainElement = newElement;
        } else {
            lastChainElement->setNext(newElement);
        }
        newElement->setPrevious(lastChainElement);
        lastChainElement = newElement;
        size++;
    }

    ChainIterator<T> *getIterator()
    {
        ChainIterator<T> *iterator = new ChainIterator<T>(this);
        return iterator;
    }

protected:

    ChainElement<T> *firstChainElement;
    ChainElement<T> *lastChainElement;
    unsigned long long size;
};

}
}

#include "chain.cpp"

#endif // MODEL_COLLECTION_CHAIN_H
