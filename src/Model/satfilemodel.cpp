#include "satfilemodel.h"

using namespace Model;

SatFileModel::SatFileModel():
    FileModel()
{
    this->numVariables = 0;
    this->expression = "";
}

int SatFileModel::getNumVariables()
{
    return numVariables;
}

void SatFileModel::setNumVariables(int numVariables)
{
    this->numVariables = numVariables;
}

void SatFileModel::debugOutput()
{
    cout << endl << "Printing a File Model:" << endl << endl;

    ChainIterator<string> *commentsIterator = comments->getIterator();
    while(true == commentsIterator->hasNext()) {
        string comment(commentsIterator->next());
        cout << "COMMENT: " << comment << endl;
    }

    cout << "Number of variables: " << numVariables << endl << endl;
    cout << "Expression: " << endl << expression << endl << endl;
    cout << "Graph structure: " << endl;
    rootGraphElement->debugOutput(0);
    cout << endl << "Text representation: " << endl;
    cout << rootGraphElement->debugExpression() << endl;
}

string SatFileModel::getExpresion()
{
    return expression;
}

void SatFileModel::setExpression(string expression)
{
    this->expression = expression;
}
