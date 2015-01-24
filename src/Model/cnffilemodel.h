#ifndef MODEL_CNFFILEMODEL_H
#define MODEL_CNFFILEMODEL_H

#include "filemodel.h"

namespace Model
{

class CnfFileModel: public FileModel
{
public:
    CnfFileModel();

    unsigned long long getNumVariables();
    void setNumVariables(unsigned long long numVariables);

    unsigned long long getNumClauses();
    void setNumClauses(unsigned long long numClauses);

    void debugOutput();
protected:
    unsigned long long numVariables;
    unsigned long long numClauses;
};

}

#endif // MODEL_CNFFILEMODEL_H
