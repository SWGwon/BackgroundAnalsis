#include "background.h"

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

bool tSort(Hit Hit1, Hit Hit2)
{
    return(Hit1.GetT() < Hit2.GetT());
}

//a, b are vector
double GetAngle(float a[], float b[])
{
    float norm_a[3];
    float norm_b[3];
    
    //normalize
    norm_a[0] = a[0]/(pow(pow(a[0],2)+pow(a[1],2)+pow(a[2],2),0.5));
    norm_a[1] = a[1]/(pow(pow(a[0],2)+pow(a[1],2)+pow(a[2],2),0.5));
    norm_a[2] = a[2]/(pow(pow(a[0],2)+pow(a[1],2)+pow(a[2],2),0.5));

    norm_b[0] = b[0]/(pow(pow(b[0],2)+pow(b[1],2)+pow(b[2],2),0.5));
    norm_b[1] = b[1]/(pow(pow(b[0],2)+pow(b[1],2)+pow(b[2],2),0.5));
    norm_b[2] = b[2]/(pow(pow(b[0],2)+pow(b[1],2)+pow(b[2],2),0.5));

    //get angle
    double angle = TMath::ACos(norm_a[0]*norm_b[0]+ norm_a[1]*norm_b[1]+norm_a[2]*norm_b[2])/TMath::Pi();
    if(angle >= 0 && angle <= 1)
        return angle;
    else
        return -1000;
}

//a, b are vector
double GetDistance(float a[], Hit hit)
{
    return pow(pow(a[0]-hit.GetX(),2)+pow(a[1]-hit.GetY(),2)+pow(a[2]-hit.GetZ(),2),0.5);
}
