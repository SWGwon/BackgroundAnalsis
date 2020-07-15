#ifndef _hit_
#define _hit_

#include <ctime>
#include <string>
#include <utility>
#include <vector>
#include <thread>
#include <float.h>

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
        float TSmear;               // smeared T of hit
        float vtxX;                 // X position of vertex
        float vtxY;                 // Y position of vertex
        float vtxZ;                 // Z position of vertex
        float vtxT;                 // ture T of vertex
        float leverArm;             // lever arm
        float parentId;             // parentId of hit
        float parentPdg;             // parentPdg of hit
        float cubeE;    //neutron cube energy
        float trueE;    //neutron true energy
        float hitE;    //neutron hit energy
        float trueT;    //neutron true time
        float hitPDG;    //hit PDG
        float energyDeposit;        // energy deposited by the neutron
        bool isNeutron;
        bool isGamma;
        float category;     //kind of hit(1: signal; 2: secondary neutron; 3: primary gamma; 4: secondary gamma)

    public:
////////////////////////////////////////////////////////
        void SetTOF(float timeWindow);
        float GetTOF();
////////////////////////////////////////////////////////
        void SetTOFSmear(float timeWindowSmear);
        float GetTOFSmear();
////////////////////////////////////////////////////////
        void SetX(float X);
        float GetX();
////////////////////////////////////////////////////////
        void SetY(float Y);
        float GetY();
////////////////////////////////////////////////////////
        void SetZ(float Z);
        float GetZ();
////////////////////////////////////////////////////////
        void SetT(float T);
        float GetT();
////////////////////////////////////////////////////////
        void SetTSmear(float TSmear);
        float GetTSmear();
////////////////////////////////////////////////////////
        void SetVtxX(float vtxX);
        float GetVtxX();
////////////////////////////////////////////////////////
        void SetVtxY(float vtxY);
        float GetVtxY();
////////////////////////////////////////////////////////
        void SetVtxZ(float vtxZ);
        float GetVtxZ();
////////////////////////////////////////////////////////
        void SetVtxT(float vtxT);
        float GetVtxT();
////////////////////////////////////////////////////////
        void SetLeverArm(float leverArm);
        float GetLeverArm();
////////////////////////////////////////////////////////
        void SetParentId(float parentId);
        float GetParentId();
////////////////////////////////////////////////////////
        void SetParentPdg(float parentPdg);
        float GetParentPdg();
////////////////////////////////////////////////////////
        void SetCubeE(float cubeE);
        float GetCubeE();
////////////////////////////////////////////////////////
        void SetTrueE(float trueE);
        float GetTrueE();
////////////////////////////////////////////////////////
        void SetHitE(float hitE);
        float GetHitE();
////////////////////////////////////////////////////////
        void SetTrueT(float trueT);
        float GetTrueT();
////////////////////////////////////////////////////////
        void SetHitPDG(float hitPDG);
        float GetHitPDG();
////////////////////////////////////////////////////////
        void SetEnergyDeposit(float energyDeposit);
        float GetEnergyDeposit();
////////////////////////////////////////////////////////
        void SetIsNeutron(bool isNeutron);
        bool IsNeutron();
////////////////////////////////////////////////////////
        void SetIsGamma(bool isGamma);
        bool IsGamma();
////////////////////////////////////////////////////////
        void SetCategory(float category);
        float GetCategory();
////////////////////////////////////////////////////////
        void SetPDG(float pdg);
        float GetPDG();
////////////////////////////////////////////////////////
        float piDeath[3];      //pion death
        float protonDeath[3];      //proton Death

        bool isFromPion;
        bool isFromProton;


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

#endif
