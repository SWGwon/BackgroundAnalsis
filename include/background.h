#include <ctime>
#include <string>
#include <utility>
#include <vector>
#include <thread>

#include "TChain.h"
#include "Riostream.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <cmath>
#include <iostream>
#include <sstream>
#include <utility>
#include <limits>
#include <getopt.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>

#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TH1F.h"
#include "TFile.h"
#include "TGraph.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TProfile.h"
#include "TRandom.h"
#include <TMath.h>
#include "TSpline.h"
#include "TSystem.h"
#include <TError.h>
#include "THistPainter.h"
#include <TStyle.h>
#include <TROOT.h>

class Hit
{
    private:
        float timeWindow;           // time windows of the hit
        float timeWindowSmear;      // smeared time window 
        float X;                    // X position of hit
        float Y;                    // Y position of hit
        float Z;                    // Z position of hit
        float T;                    // true T of hit
        float vtxX;                 // X position of vertex
        float vtxY;                 // Y position of vertex
        float vtxZ;                 // Z position of vertex
        float vtxT;                 // ture T of vertex
        float leverArm;             // lever arm
        float parentId;             // parentId of hit
        float cubeE;    //neutron cube energy
        float trueE;    //neutron true energy
        float trueT;    //neutron true time
        float hitPDG;    //hit PDG
        float energyDeposit;        // energy deposited by the neutron
        bool isNeutron;
        bool isGamma;
        float category;     //kind of hit(1: signal; 2: secondary neutron; 3: primary gamma; 4: secondary gamma)

    public:
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetTOF(float timeWindow){this->timeWindow = timeWindow;};
        float GetTOF(){return this->timeWindow;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetTOFSmear(float timeWindowSmear){this->timeWindowSmear = timeWindowSmear;};
        float GetTOFSmear(){return this->timeWindowSmear;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetX(float X){this->X = X;};
        float GetX(){return this->X;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetY(float Y){this->Y = Y;};
        float GetY(){return this->Y;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetZ(float Z){this->Z = Z;};
        float GetZ(){return this->Z;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetT(float T){this->T = T;};
        float GetT(){return this->T;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetVtxX(float vtxX){this->vtxX = vtxX;};
        float GetVtxX(){return this->vtxX;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetVtxY(float vtxY){this->vtxY = vtxY;};
        float GetVtxY(){return this->vtxY;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetVtxZ(float vtxZ){this->vtxZ = vtxZ;};
        float GetVtxZ(){return this->vtxZ;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetVtxT(float vtxT){this->vtxT = vtxT;};
        float GetVtxT(){return this->vtxT;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetLeverArm(float leverArm){this->leverArm = leverArm;};
        float GetLeverArm(){return this->leverArm;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetParentId(float parentId){this->parentId = parentId;};
        float GetParentId(){return this->parentId;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetCubeE(float cubeE){this->cubeE = cubeE;};
        float GetCubeE(){return this->cubeE;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetTrueE(float trueE){this->trueE = trueE;};
        float GetTrueE(){return this->trueE;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetTrueT(float trueT){this->trueT = trueT;};
        float GetTrueT(){return this->trueT;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetHitPDG(float hitPDG){this->hitPDG = hitPDG;};
        float GetHitPDG(){return this->hitPDG;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetEnergyDeposit(float energyDeposit){this->energyDeposit = energyDeposit;};
        float GetEnergyDeposit(){return this->energyDeposit;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetIsNeutron(bool isNeutron){this->isNeutron = isNeutron;};
        bool IsNeutron(){return this->isNeutron;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetIsGamma(bool isGamma){this->isGamma = isGamma;};
        bool IsGamma(){return this->isGamma;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetCategory(float category){this->category = category;};
        float GetCategory(){return this->category;};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        float piDeath[3];      //pion death
        float protonDeath[3];      //proton Death

        bool isFromPion;
        bool isFromProton;

        int parentPdg;   // PDG of parent

        Hit():
            timeWindow(-1),
            timeWindowSmear(-1),    
            X(0),
            Y(0),
            Z(0),
            parentId(0),
            isNeutron(false),
            isGamma(false),
            T(0),
            energyDeposit(0),
            leverArm(0),  
            trueE(0), 
            cubeE(0),
            trueT(0), 
            hitPDG(0),
            parentPdg(123123123),
            category(-1),
            isFromPion(0),
            isFromProton(0)
    {
        for(int i = 0; i < 3; i++)
        {
            this->piDeath[i] = 0;   
            this->protonDeath[i] = 0; 
        }
    }
        ~Hit() {}
};

bool tSort(Hit Hit1, Hit Hit2);

//a, b are vector
double GetAngle(float a[], float b[]);

//a, b are vector
double GetDistance(float a[], Hit hit);
