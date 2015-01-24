#ifndef MODEL_SATFILEMODEL_H
#define MODEL_SATFILEMODEL_H

#include "filemodel.h"
#include "Collection/chainiterator.h"

using namespace Model::Collection;

namespace Model
{

/**
 * @brief The SatFileModel class
 * Contains information about SAT file
 */
class SatFileModel: public FileModel
{
public:
    SatFileModel();

    int getNumVariables();
    void setNumVariables(int numVariables);

    string getExpresion();
    void setExpression(string expression);

    void debugOutput();

protected:
    /**
     * @brief numVariables - number of variables in input SAT file
     */
    int numVariables;

    /**
     * @brief expression - expression in SAT format
     */
    string expression;

};

}

#endif // MODEL_SATFILEMODEL_H
