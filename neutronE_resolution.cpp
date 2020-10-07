#include "include/hit.h"
#include "include/functions.h"

using namespace std;

int main()
{
    TH2F * lev_time = new TH2F("lever_arm_vs_time","lever arm vs. time;Lever Arm[cm];Time[ns]",20,0,200,25,0,25);
    TH2F * lev_time_smeared = new TH2F("lever_arm_vs_time_smeared","lever arm vs. time(smeared);Lever Arm[cm];Time[ns]",20,0,200,25,0,25);
    TH2F * asdf = new TH2F("adsf","(true-smear)/true;Lever Arm[cm];Time[ns]",20,0,200,25,0,25);

    float _3DST_x1 = -120;
    float _3DST_x2 = 120;
    float _3DST_y1 = -120;
    float _3DST_y2 = 120;
    float _3DST_z1 = -100;
    float _3DST_z2 = 100;
    float FV_x = 200;
    float FV_y = 200;
    float FV_z = 180;

    TH1F hist_rms[20][25];
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            hist_rms[i][j].SetBins(100,-5,5);
        }
    }
    float energyHitCut = 0.5; //energy deposit threshold for cube
    const double c_velocity = 29.9792458;
    gErrorIgnoreLevel = kWarning;

    int filenum;
    cout<<"---------------------------"<<endl;
    cout<<"file loading..."<<endl;

    TChain tree("tree");
    for(int i = 1; i < 1000; i++)
    {
        tree.Add(Form("/pnfs/dune/persistent/users/gyang/3DST/dump/standardGeo13/PROD102/RHC_%d.root",i));
    }
    //tree.Add("/pnfs/dune/persistent/users/gyang/3DST/dump/standardGeo13/PROD102/RHC_*extendCube.root");


    //SetBranchAddress
    float t_vtx[3]; tree.SetBranchAddress("vtx",&t_vtx);
    int t_nFS; tree.SetBranchAddress("nFS",&t_nFS);
    int t_fsPdg[1000]; tree.SetBranchAddress("fsPdg",&t_fsPdg);
    float t_neutronHitX[1000]; tree.SetBranchAddress("neutronHitX",&t_neutronHitX);
    float t_neutronHitY[1000]; tree.SetBranchAddress("neutronHitY",&t_neutronHitY);
    float t_neutronHitZ[1000]; tree.SetBranchAddress("neutronHitZ",&t_neutronHitZ);
    float t_neutronHitT[1000]; tree.SetBranchAddress("neutronHitT",&t_neutronHitT);
    float t_neutronHitSmearT[1000]; tree.SetBranchAddress("neutronHitSmearT",&t_neutronHitSmearT);
    float t_neutronCubeE[1000]; tree.SetBranchAddress("neutronCubeE",&t_neutronCubeE);
    float t_neutronTrueE[1000]; tree.SetBranchAddress("neutronTrueE",&t_neutronTrueE);
    float t_neutronParentId[1000]; tree.SetBranchAddress("neutronParentId",&t_neutronParentId);
    float t_neutronParentPDG[1000]; tree.SetBranchAddress("neutronParentPDG",&t_neutronParentPDG);
    float t_gammaHitX[1000]; tree.SetBranchAddress("gammaHitX",&t_gammaHitX);
    float t_gammaHitY[1000]; tree.SetBranchAddress("gammaHitY",&t_gammaHitY);
    float t_gammaHitZ[1000]; tree.SetBranchAddress("gammaHitZ",&t_gammaHitZ);
    float t_gammaHitT[1000]; tree.SetBranchAddress("gammaHitT",&t_gammaHitT);
    float t_gammaHitSmearT[1000]; tree.SetBranchAddress("gammaHitSmearT",&t_gammaHitSmearT);
    float t_gammaCubeE[1000]; tree.SetBranchAddress("gammaCubeE",&t_gammaCubeE);
    float t_gammaHitPDG[1000]; tree.SetBranchAddress("gammaHitPDG",&t_gammaHitPDG);
    float t_gammaTrueE[1000]; tree.SetBranchAddress("gammaTrueE",&t_gammaTrueE);
    float t_gammaParentId[1000]; tree.SetBranchAddress("gammaParentId",&t_gammaParentId);
    float t_gammaParentPDG[1000]; tree.SetBranchAddress("gammaParentPDG",&t_gammaParentPDG);
    float t_vtxTime; tree.SetBranchAddress("vtxTime",&t_vtxTime);
    float t_vtxTimeSmear; tree.SetBranchAddress("vtxTimeSmear",&t_vtxTimeSmear);

    cout<<"file loading is done"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<endl;
    cout<<"total entries: "<<tree.GetEntries()<<endl;
    cout<<"event loop starts"<<endl;

    for(int event = 0; event < tree.GetEntries(); event++)
    {
        tree.GetEntry(event);

        cout<<"\033[1Aevent: "<<((double)event*100/tree.GetEntries())<<"%          \033[1000D"<<endl;

        //out of fiducial volume
        if(t_vtx[0] < _3DST_x1+_3DST_x2-FV_x/2 || t_vtx[0] > _3DST_x1+_3DST_x2+FV_x/2)
            continue;
        if(t_vtx[1] < _3DST_y1+_3DST_y2-FV_y/2 || t_vtx[1] > _3DST_y1+_3DST_y2+FV_y/2)
            continue;
        if(t_vtx[2] < _3DST_z1+_3DST_z2-FV_z/2 || t_vtx[2] > _3DST_z1+_3DST_z2+FV_z/2)
            continue;

        //check whether it's CC event or not
        bool is_CC = false;
        for(int inFS = 0; inFS < t_nFS; inFS++)
        {
            if(t_fsPdg[inFS] == -13)    //electronPDG=11,muonPDG=13
            {
                is_CC = true;
                break;
            }
        }

        //if it's not CC skip this event
        if(!is_CC)
            continue;

        Hit temp_neutron_Hit;   
        std::vector<Hit> vectorHit;    //vector of all neutron+gamma hits

        //push_back satisying hits to vectorHit
        for(int n_neutronHit = 0; n_neutronHit < 1000; n_neutronHit++)
        {
            //out of 3dst
                if(t_neutronHitX[n_neutronHit] < _3DST_x1 || t_neutronHitX[n_neutronHit] > _3DST_x2)
                    continue;
                if(t_neutronHitY[n_neutronHit] < _3DST_y1 || t_neutronHitY[n_neutronHit] > _3DST_y2)
                    continue;
                if(t_neutronHitZ[n_neutronHit] < _3DST_z1 || t_neutronHitZ[n_neutronHit] > _3DST_z2)
                    continue;
                if(t_neutronHitX[n_neutronHit] == 0)
                    continue;
                if(t_neutronHitY[n_neutronHit] == 0)
                    continue;
                if(t_neutronHitZ[n_neutronHit] == 0)
                    continue;

            //energy threshold
            if(t_neutronCubeE[n_neutronHit] < energyHitCut || t_neutronCubeE[n_neutronHit] == 0)
                continue;

            //calculate lever arm
            float leverArm = pow(
                    pow(t_neutronHitX[n_neutronHit]+gRandom->Gaus(0,1./pow(12.,0.5)) - t_vtx[0],2)+
                    pow(t_neutronHitY[n_neutronHit]+gRandom->Gaus(0,1./pow(12.,0.5)) - t_vtx[1],2)+
                    pow(t_neutronHitZ[n_neutronHit]+gRandom->Gaus(0,1./pow(12.,0.5)) - t_vtx[2],2),0.5);

            float true_leverArm = pow(
                    pow(t_neutronHitX[n_neutronHit]- t_vtx[0],2)+
                    pow(t_neutronHitY[n_neutronHit]- t_vtx[1],2)+
                    pow(t_neutronHitZ[n_neutronHit]- t_vtx[2],2),0.5);

            //calculate signal window; time of flight
            float tof = t_neutronHitT[n_neutronHit] - t_vtxTime;
            //float tofSmear = t_neutronHitSmearT[n_neutronHit] - t_vtxTimeSmear;
            float tofSmear = t_neutronHitT[n_neutronHit]+gRandom->Gaus(0,0.5)/pow(t_neutronCubeE[n_neutronHit]/1.5,0.5) - t_vtxTime+gRandom->Gaus(0,0.5);

            //Fix a bug from edep-sim
            if(tof == 1)
                tof = 0.5;

            if(tof > 0)
            {
                temp_neutron_Hit.SetTOF(tof);
                temp_neutron_Hit.SetTOFSmear(tofSmear);
                temp_neutron_Hit.SetLeverArm(leverArm);

                temp_neutron_Hit.SetVtxX(t_vtx[0]);
                temp_neutron_Hit.SetVtxY(t_vtx[1]);
                temp_neutron_Hit.SetVtxZ(t_vtx[2]);

                temp_neutron_Hit.SetTrueT(t_neutronHitT[n_neutronHit]);
                temp_neutron_Hit.SetTrueE(t_neutronTrueE[n_neutronHit]);
                temp_neutron_Hit.SetCubeE(t_neutronCubeE[n_neutronHit]);

                temp_neutron_Hit.SetParentId(t_neutronParentId[n_neutronHit]);
                temp_neutron_Hit.SetParentPdg(t_neutronParentPDG[n_neutronHit]);

                temp_neutron_Hit.SetVtxT(t_vtxTime);
                temp_neutron_Hit.SetT(t_neutronHitT[n_neutronHit]);
                temp_neutron_Hit.SetX(t_neutronHitX[n_neutronHit]);
                temp_neutron_Hit.SetY(t_neutronHitY[n_neutronHit]);
                temp_neutron_Hit.SetZ(t_neutronHitZ[n_neutronHit]);
                temp_neutron_Hit.SetParentId(t_neutronParentId[n_neutronHit]);
                temp_neutron_Hit.SetIsNeutron(true);
                temp_neutron_Hit.SetCubeE(t_neutronCubeE[n_neutronHit]);

                vectorHit.push_back(temp_neutron_Hit);
            }
        }

        if(vectorHit.size() == 0)
            continue;

        //this makes beta <<< 1, 1 spill is 10us, skip this event
        if(vectorHit.at(0).GetTrueT() > 10000)
            continue;

        //sort by time smear
        if(vectorHit.size() != 0)
            std::sort(vectorHit.begin(), vectorHit.end(), tSortSmear);

        //select earliest hit 
        Hit earliest_hit;
        earliest_hit = vectorHit.at(0);

        if(earliest_hit.IsNeutron())
        {
            if(earliest_hit.GetParentId() == -1)
            {
                earliest_hit.SetCategory(1);
            }
            if(earliest_hit.GetParentId() >= 0)
                earliest_hit.SetCategory(2);
        }
        if(earliest_hit.IsGamma())
        {
            if(earliest_hit.GetParentId() == -1)
                earliest_hit.SetCategory(3);
            if(earliest_hit.GetParentId() > 0)
                earliest_hit.SetCategory(4);
        }

        if(earliest_hit.GetCategory() == -1000)
            continue;
        if(earliest_hit.GetHitPDG() > 10000)
            continue;

        //E = 0.7245*(lever arm/time)^2 MeV
        //signal
        if(earliest_hit.GetCategory() == 1)
        {
            lev_time->Fill(earliest_hit.GetLeverArm(),earliest_hit.GetTOF());
            lev_time_smeared->Fill(earliest_hit.GetLeverArm(),earliest_hit.GetTOFSmear());
            //(true-smear)/true
            float beta = earliest_hit.GetLeverArm()/(c_velocity*earliest_hit.GetTOF());
            float beta_smear = (earliest_hit.GetLeverArm())/(c_velocity*earliest_hit.GetTOFSmear());
            float true_E, smear_E;
            true_E = 939.565*(1./pow(1-pow(beta,2),0.5)-1);
            smear_E = 939.565*(1./pow(1-pow(beta_smear,2),0.5)-1);
            //cout<<"trueE :"<<true_E<<endl;
            //cout<<"smearE: "<<smear_E<<endl;
            for(int i = 0; i < 20; i++)
            {
                if(10*i< earliest_hit.GetLeverArm() && earliest_hit.GetLeverArm() < 10*(i+1))
                {
                    for(int j = 0; j < 25; j++)
                    {
                        if(j < earliest_hit.GetTOFSmear() && earliest_hit.GetTOFSmear() < j+1)
                        {
                            hist_rms[i][j].Fill((true_E-smear_E)/true_E);
                        }
                    }
                }
            }
        }

    }//end of event iterate

    cout<<"event loop is aone"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"making output files"<<endl;

    TCanvas * can1 = new TCanvas;
    lev_time->Draw("colz");
    can1->SaveAs("lever_arm_vs_time.pdf");

    TCanvas * can2 = new TCanvas;
    lev_time_smeared->Draw("colz");
    can2->SaveAs("lever_arm_vs_time_smeared.pdf");

    TCanvas * can3 = new TCanvas;
    hist_rms[10][10].Draw("colz");
    can3->SaveAs("hist_rms[10][10].pdf");
    cout<<hist_rms[10][10].GetRMS()<<endl;

    TH2F * rms = new TH2F("rms","Standard Deviation Energy (signal);Lever Arm[cm];Time[ns]",20,0,200,25,0,25);
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            rms->SetBinContent(i+1,j+1,hist_rms[i][j].GetRMS());
        }
    }

    TCanvas * can4 = new TCanvas;
    rms->SetStats(0);
    rms->GetZaxis()->SetRangeUser(0,0.6);
    //rms->GetZaxis()->SetRangeUser(0,0.3);
    rms->Draw("colz");
    can4->SaveAs("rms.C");

    cout<<"making output files is done"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"all done"<<endl;

    return 0;
}
