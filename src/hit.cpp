#include "hit.h"

using namespace std;

////////////////////////////////////////////////////////////////////////
void Hit::SetTOF(float timeWindow)
{
    this->timeWindow = timeWindow;
}
float Hit::GetTOF()
{
    return this->timeWindow;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetTOFSmear(float timeWindowSmear)
{
    this->timeWindowSmear = timeWindowSmear;
}
float Hit::GetTOFSmear()
{
    return this->timeWindowSmear;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetX(float X)
{
    this->X = X;
}
float Hit::GetX()
{
    return this->X;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetY(float Y)
{
    this->Y = Y;
}
float Hit::GetY()
{
    return this->Y;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetZ(float Z)
{
    this->Z = Z;
}
float Hit::GetZ()
{
    return this->Z;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetT(float T)
{
    this->T = T;
}
float Hit::GetT()
{
    return this->T;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetVtxX(float vtxX)
{
    this->vtxX = vtxX;
}
float Hit::GetVtxX()
{
    return this->vtxX;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetVtxY(float vtxY)
{
    this->vtxY = vtxY;
}
float Hit::GetVtxY()
{
    return this->vtxY;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetVtxZ(float vtxZ)
{
    this->vtxZ = vtxZ;
}
float Hit::GetVtxZ()
{
    return this->vtxZ;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetVtxT(float vtxT)
{
    this->vtxT = vtxT;
}
float Hit::GetVtxT()
{
    return this->vtxT;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetLeverArm(float leverArm)
{
    this->leverArm = leverArm;
}
float Hit::GetLeverArm()
{
    return this->leverArm;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetParentId(float parentId)
{
    this->parentId = parentId;
}
float Hit::GetParentId()
{
    return this->parentId;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetCubeE(float cubeE)
{
    this->cubeE = cubeE;
}
float Hit::GetCubeE()
{
    return this->cubeE;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetTrueE(float trueE)
{
    this->trueE = trueE;
}
float Hit::GetTrueE()
{
    return this->trueE;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetHitE(float hitE)
{
    this->hitE = hitE;
}
float Hit::GetHitE()
{
    return this->hitE;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetTrueT(float trueT)
{
    this->trueT = trueT;
}
float Hit::GetTrueT()
{
    return this->trueT;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetHitPDG(float hitPDG)
{
    this->hitPDG = hitPDG;
}
float Hit::GetHitPDG()
{
    return this->hitPDG;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetEnergyDeposit(float energyDeposit)
{
    this->energyDeposit = energyDeposit;
}
float Hit::GetEnergyDeposit()
{
    return this->energyDeposit;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetIsNeutron(bool isNeutron)
{
    this->isNeutron = isNeutron;
}
bool Hit::IsNeutron()
{
    return this->isNeutron;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetIsGamma(bool isGamma)
{
    this->isGamma = isGamma;
}
bool Hit::IsGamma()
{
    return this->isGamma;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetCategory(float category)
{
    this->category = category;
}
float Hit::GetCategory()
{
    return this->category;
}
////////////////////////////////////////////////////////////////////////
void Hit::SetPDG(float pdg)
{
    this->hitPDG = pdg;
}
float Hit::GetPDG()
{
    return this->hitPDG;
}
