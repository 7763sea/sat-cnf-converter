#ifndef EXCEPTION_EXPRESSIONEQUALSTRUEEXCEPTION_H
#define EXCEPTION_EXPRESSIONEQUALSTRUEEXCEPTION_H

#include <exception>

using namespace std;

namespace Exception
{

class ExpressionEqualsTrueException: public exception
{
public:
    ExpressionEqualsTrueException();
};

}

#endif // EXCEPTION_EXPRESSIONEQUALSTRUEEXCEPTION_H
