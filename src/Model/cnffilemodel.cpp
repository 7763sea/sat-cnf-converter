#include "cnffilemodel.h"

using namespace Model;

CnfFileModel::CnfFileModel()
{
}

unsigned long long CnfFileModel::getNumVariables()
{
    return numVariables;
}

void CnfFileModel::setNumVariables(unsigned long long numVariables)
{
    this->numVariables = numVariables;
}

unsigned long long CnfFileModel::getNumClauses()
{
    return numClauses;
}

void CnfFileModel::setNumClauses(unsigned long long numClauses)
{
    this->numClauses = numClauses;
}

void CnfFileModel::debugOutput()
{

}
