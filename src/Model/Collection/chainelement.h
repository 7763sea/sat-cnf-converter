#ifndef MODEL_COLLECTION_CHAINELEMENT_H
#define MODEL_COLLECTION_CHAINELEMENT_H

#include <iostream>

#include "../../Model/Node/abstractnode.h"

using namespace Model::Node;

namespace Model
{
namespace Collection
{

using namespace std;

/**
 * Element of chain
 */
template <typename T>
class ChainElement
{
public:
    ChainElement(T content)
    {
        previous = NULL;
        next = NULL;
        this->content = content;
    }

    ~ChainElement()
    {
        if(NULL != next)
            next->setPrevious(previous);
        if(NULL != previous)
            previous->setNext(next);
    }

    ChainElement<T> *getPrevious()
    {
        return previous;
    }

    ChainElement<T> *getNext()
    {
        return next;
    }

    void setPrevious(ChainElement<T> *previous)
    {
        this->previous = previous;
    }

    void setNext(ChainElement<T> *next)
    {
        this->next = next;
    }

    T getContent()
    {
        return content;
    }

    void setContent(T content)
    {
        this->content = content;
    }

    ChainElement<T> *seek(unsigned long long position, unsigned long long recursionPosition)
    {
        throw string("Warning: ChainElement::seek does not works!");
        cout << "POS " << recursionPosition << "/" << position << endl;

        if(recursionPosition > position)
            return NULL;
        if(recursionPosition == position)
            return this;
        return seek(position, recursionPosition + 1);
    }

protected:
    ChainElement *previous;
    ChainElement *next;
    T content;


};

}
}


#include "chainelement.cpp"

#endif // MODEL_COLLECTION_CHAINELEMENT_H
