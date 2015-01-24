#ifndef EXCEPTION_EXPRESSIONEQUALSFALSEEXCEPTION_H
#define EXCEPTION_EXPRESSIONEQUALSFALSEEXCEPTION_H

#include <exception>

using namespace std;

namespace Exception
{

class ExpressionEqualsFalseException: public exception
{
public:
    ExpressionEqualsFalseException();
};

}

#endif // EXCEPTION_EXPRESSIONEQUALSFALSEEXCEPTION_H
