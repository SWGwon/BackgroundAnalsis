#include "include/hit.h"
#include "include/functions.h"


using namespace std;

int main()
{
    TH2F * lev_time = new TH2F("lever_arm_vs_time","lever arm vs. time;Lever Arm[cm];Time[ns]",20,0,200,25,0,25);
    TH2F * lev_time_smeared = new TH2F("lever_arm_vs_time_smeared","lever arm vs. time(smeared);Lever Arm[cm];Time[ns]",20,0,200,25,0,25);
    TH2F * asdf = new TH2F("adsf","(true-smear)/true;Lever Arm[cm];Time[ns]",20,0,200,25,0,25);

    TH1F hist_rms[20][25];
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            hist_rms[i][j].SetBins(1000,-5,5);
        }
    }
    float energyHitCut = 0.5; //energy deposit threshold for cube
    const double c_velocity = 29.9792458;
    //histograms{

    //}
    gErrorIgnoreLevel = kWarning;

    int filenum;
    cout<<"filenum :"<<endl;
    cin>>filenum;
    cout<<"---------------------------"<<endl;
    cout<<"file loading..."<<endl;

    TChain tree("tree");
    for(int i = 1; i != filenum+1; i++)
    { //cout<<"\033[1APROD"<<101<<": "<<(double)(i*100/filenum)<<"%\033[1000D"<<endl;
        string file = Form("/Users/gwon/Geo12/PROD101/RHC_%d_wGamma_2ndVersion_wNuE.root",i);
        //string file = Form("/Users/gwon/Geo12/PROD101/RHC_%d_wGamma_2ndVersion.root",i);
        //string file = Form("/pnfs/dune/persistent/users/gyang/3DST/dump/standardGeo12/PROD101/RHC_%d_wGamma_2ndVersion.root",i);
        tree.Add(TString(file));
    }
    //tree.Add("/Users/gwon/Geo12/PROD101/RHC_*_wGamma_2ndVersion.root");

    //vectors I defined
    float vec_piDeath_to_hit[3];
    float vec_protonDeath_to_hit[3];
    float vec_vtx_to_piDeath[3];
    float vec_vtx_to_protonDeath[3];

    //SetBranchAddress
    int t_ifileNo; tree.SetBranchAddress("ifileNo",&t_ifileNo);
    int t_ievt; tree.SetBranchAddress("ievt",&t_ievt);
    float t_p3lep[3]; tree.SetBranchAddress("p3lep",&t_p3lep);
    float t_p3pi[3]; tree.SetBranchAddress("p3pi",&t_p3pi);
    float t_p3proton[3]; tree.SetBranchAddress("p3proton",&t_p3proton);
    float t_vtx[3]; tree.SetBranchAddress("vtx",&t_vtx);
    float t_lepDeath[3]; tree.SetBranchAddress("lepDeath",&t_lepDeath);
    int t_lepPdg; tree.SetBranchAddress("lepPdg",&t_lepPdg);
    float t_lepKE; tree.SetBranchAddress("lepKE",&t_lepKE);
    int t_piPdg; tree.SetBranchAddress("piPdg",&t_piPdg);
    float t_piKE; tree.SetBranchAddress("piKE",&t_piKE);
    float t_piDeath[3]; tree.SetBranchAddress("piDeath",&t_piDeath);
    int t_protonPdg; tree.SetBranchAddress("protonPdg",&t_protonPdg);
    float t_protonKE; tree.SetBranchAddress("protonKE",&t_protonKE);
    float t_protonDeath[3]; tree.SetBranchAddress("protonDeath",&t_protonDeath);
    int t_muexit; tree.SetBranchAddress("muexit",&t_muexit);
    float t_muonExitPt[3]; tree.SetBranchAddress("muonExitPt",&t_muonExitPt);
    float t_muonExitMom[3]; tree.SetBranchAddress("muonExitMom",&t_muonExitMom);
    int t_muonReco; tree.SetBranchAddress("muonReco",&t_muonReco);
    float t_muGArLen; tree.SetBranchAddress("muGArLen",&t_muGArLen);
    int t_piexit; tree.SetBranchAddress("piexit",&t_piexit);
    float t_pionExitPt[3]; tree.SetBranchAddress("pionExitPt",&t_pionExitPt);
    float t_pionExitMom[3]; tree.SetBranchAddress("pionExitMom",&t_pionExitMom);
    int t_pionReco; tree.SetBranchAddress("pionReco",&t_pionReco);
    float t_piGArLen; tree.SetBranchAddress("piGArLen",&t_piGArLen);
    int t_protonexit; tree.SetBranchAddress("protonexit",&t_protonexit);
    float t_protonExitPt[3]; tree.SetBranchAddress("protonExitPt",&t_protonExitPt);
    float t_protonExitMom[3]; tree.SetBranchAddress("protonExitMom",&t_protonExitMom);
    int t_protonReco; tree.SetBranchAddress("protonReco",&t_protonReco);
    float t_protonGArLen; tree.SetBranchAddress("protonGArLen",&t_protonGArLen);
    float t_hadTot; tree.SetBranchAddress("hadTot",&t_hadTot);
    float t_hadTot_TPC; tree.SetBranchAddress("hadTot_TPC",&t_hadTot_TPC);
    float t_hadTot_3DST; tree.SetBranchAddress("hadTot_3DST",&t_hadTot_3DST);
    float t_hadTot_ECAL; tree.SetBranchAddress("hadTot_ECAL",&t_hadTot_ECAL);
    float t_hadTot_allECAL; tree.SetBranchAddress("hadTot_allECAL",&t_hadTot_allECAL);
    float t_hadTot_leak; tree.SetBranchAddress("hadTot_leak",&t_hadTot_leak);
    float t_hadCollar; tree.SetBranchAddress("hadCollar",&t_hadCollar);
    float t_hadCollar_side[4]; tree.SetBranchAddress("hadCollar_side",&t_hadCollar_side);
    float t_lepCollar_side[4]; tree.SetBranchAddress("lepCollar_side",&t_lepCollar_side);
    int t_nFS; tree.SetBranchAddress("nFS",&t_nFS);
    int t_fsPdg[1000]; tree.SetBranchAddress("fsPdg",&t_fsPdg);
    float t_fsPx[1000]; tree.SetBranchAddress("fsPx",&t_fsPx);
    float t_fsPy[1000]; tree.SetBranchAddress("fsPy",&t_fsPy);
    float t_fsPz[1000]; tree.SetBranchAddress("fsPz",&t_fsPz);
    float t_fsE[1000]; tree.SetBranchAddress("fsE",&t_fsE);
    float t_fsTrkLen[1000]; tree.SetBranchAddress("fsTrkLen",&t_fsTrkLen);
    float t_neutronHitX[1000]; tree.SetBranchAddress("neutronHitX",&t_neutronHitX);
    float t_neutronHitY[1000]; tree.SetBranchAddress("neutronHitY",&t_neutronHitY);
    float t_neutronHitZ[1000]; tree.SetBranchAddress("neutronHitZ",&t_neutronHitZ);
    float t_neutronHitT[1000]; tree.SetBranchAddress("neutronHitT",&t_neutronHitT);
    float t_neutronHitSmearT[1000]; tree.SetBranchAddress("neutronHitSmearT",&t_neutronHitSmearT);
    float t_neutronHitE[1000]; tree.SetBranchAddress("neutronHitE",&t_neutronHitE);
    float t_neutronCubeE[1000]; tree.SetBranchAddress("neutronCubeE",&t_neutronCubeE);
    float t_neutronRecoE[1000]; tree.SetBranchAddress("neutronRecoE",&t_neutronRecoE);
    float t_neutronHitPDG[1000]; tree.SetBranchAddress("neutronHitPDG",&t_neutronHitPDG);
    float t_neutronTrueE[1000]; tree.SetBranchAddress("neutronTrueE",&t_neutronTrueE);
    float t_neutronParentId[1000]; tree.SetBranchAddress("neutronParentId",&t_neutronParentId);
    float t_neutronParentPDG[1000]; tree.SetBranchAddress("neutronParentPDG",&t_neutronParentPDG);
    float t_neutronStartingPointX[1000]; tree.SetBranchAddress("neutronStartingPointX",&t_neutronStartingPointX);
    float t_neutronStartingPointY[1000]; tree.SetBranchAddress("neutronStartingPointY",&t_neutronStartingPointY);
    float t_neutronStartingPointZ[1000]; tree.SetBranchAddress("neutronStartingPointZ",&t_neutronStartingPointZ);
    float t_neutronStartingPointT[1000]; tree.SetBranchAddress("neutronStartingPointT",&t_neutronStartingPointT);
    float t_gammaHitX[1000]; tree.SetBranchAddress("gammaHitX",&t_gammaHitX);
    float t_gammaHitY[1000]; tree.SetBranchAddress("gammaHitY",&t_gammaHitY);
    float t_gammaHitZ[1000]; tree.SetBranchAddress("gammaHitZ",&t_gammaHitZ);
    float t_gammaHitT[1000]; tree.SetBranchAddress("gammaHitT",&t_gammaHitT);
    float t_gammaHitSmearT[1000]; tree.SetBranchAddress("gammaHitSmearT",&t_gammaHitSmearT);
    float t_gammaHitE[1000]; tree.SetBranchAddress("gammaHitE",&t_gammaHitE);
    float t_gammaCubeE[1000]; tree.SetBranchAddress("gammaCubeE",&t_gammaCubeE);
    float t_gammaRecoE[1000]; tree.SetBranchAddress("gammaRecoE",&t_gammaRecoE);
    float t_gammaHitPDG[1000]; tree.SetBranchAddress("gammaHitPDG",&t_gammaHitPDG);
    float t_gammaTrueE[1000]; tree.SetBranchAddress("gammaTrueE",&t_gammaTrueE);
    float t_gammaParentId[1000]; tree.SetBranchAddress("gammaParentId",&t_gammaParentId);
    float t_gammaParentPDG[1000]; tree.SetBranchAddress("gammaParentPDG",&t_gammaParentPDG);
    float t_gammaStartingPointX[1000]; tree.SetBranchAddress("gammaStartingPointX",&t_gammaStartingPointX);
    float t_gammaStartingPointY[1000]; tree.SetBranchAddress("gammaStartingPointY",&t_gammaStartingPointY);
    float t_gammaStartingPointZ[1000]; tree.SetBranchAddress("gammaStartingPointZ",&t_gammaStartingPointZ);
    float t_gammaStartingPointT[1000]; tree.SetBranchAddress("gammaStartingPointT",&t_gammaStartingPointT);
    float t_vtxTime; tree.SetBranchAddress("vtxTime",&t_vtxTime);
    float t_hitLocationX[1000]; tree.SetBranchAddress("hitLocationX",&t_hitLocationX);
    float t_hitLocationY[1000]; tree.SetBranchAddress("hitLocationY",&t_hitLocationY);
    float t_hitLocationZ[1000]; tree.SetBranchAddress("hitLocationZ",&t_hitLocationZ);
    float t_hitE[1000]; tree.SetBranchAddress("hitE",&t_hitE);
    float t_hitT[1000]; tree.SetBranchAddress("hitT",&t_hitT);
    float t_nuEnergy; tree.SetBranchAddress("nuEnergy",&t_nuEnergy);

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
        if(abs(t_vtx[0]) > 100 || abs(t_vtx[1]) > 100 || abs(t_vtx[2]) > 90)
            continue;

        //check whether it's CC event or not
        bool is_CC = false;
        for(int inFS = 0; inFS < t_nFS; inFS++)
        {
            if(abs(t_fsPdg[inFS]) == 11 || abs(t_fsPdg[inFS]) == 13)    //electronPDG=11,muonPDG=13
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
            if(abs(t_neutronHitX[n_neutronHit]) > 120 || 
                    abs(t_neutronHitY[n_neutronHit]) > 120 || 
                    abs(t_neutronHitZ[n_neutronHit]) > 100)
                continue;

            //starting point == -1 is default value so remove it
            if(t_neutronStartingPointX[n_neutronHit] == -1 || 
                    t_neutronStartingPointY[n_neutronHit] == -1 || 
                    t_neutronStartingPointZ[n_neutronHit] == -1 )
                continue;

            //energy threshold
            if(t_neutronCubeE[n_neutronHit] < energyHitCut || t_neutronCubeE[n_neutronHit] == 0)
                continue;

            //calculate lever arm
            float leverArm = pow(
                    pow(t_neutronHitX[n_neutronHit] - t_vtx[0],2)+
                    pow(t_neutronHitY[n_neutronHit] - t_vtx[1],2)+
                    pow(t_neutronHitZ[n_neutronHit] - t_vtx[2],2),0.5);

            //calculate signal window; time of flight
            float tof = t_neutronHitT[n_neutronHit] - t_vtxTime - 1;
            float tofSmear = t_neutronHitSmearT[n_neutronHit] - t_vtxTime - 1;

            //Fix a bug from edep-sim
            if(tof == 1)
                tof = 0.5;

            if(tof > 0)
            {
                temp_neutron_Hit.SetTOF(tof);
                temp_neutron_Hit.SetTOFSmear(tofSmear);
                temp_neutron_Hit.SetLeverArm(leverArm);
                temp_neutron_Hit.SetEnergyDeposit(t_neutronHitE[n_neutronHit]);

                temp_neutron_Hit.SetVtxX(t_vtx[0]);
                temp_neutron_Hit.SetVtxY(t_vtx[1]);
                temp_neutron_Hit.SetVtxZ(t_vtx[2]);

                temp_neutron_Hit.piDeath[0] = t_piDeath[0];
                temp_neutron_Hit.piDeath[1] = t_piDeath[1];
                temp_neutron_Hit.piDeath[2] = t_piDeath[2];

                temp_neutron_Hit.protonDeath[0] = t_protonDeath[0];
                temp_neutron_Hit.protonDeath[1] = t_protonDeath[1];
                temp_neutron_Hit.protonDeath[2] = t_protonDeath[2];

                temp_neutron_Hit.SetTrueT(t_neutronHitT[n_neutronHit]);
                temp_neutron_Hit.SetTrueE(t_neutronTrueE[n_neutronHit]);
                temp_neutron_Hit.SetCubeE(t_neutronCubeE[n_neutronHit]);

                temp_neutron_Hit.SetParentId(t_neutronParentId[n_neutronHit]);
                temp_neutron_Hit.parentPdg = t_neutronParentPDG[n_neutronHit];
                temp_neutron_Hit.SetHitPDG(t_neutronHitPDG[n_neutronHit]);

                temp_neutron_Hit.SetVtxT(t_vtxTime);
                if(t_neutronStartingPointX[n_neutronHit] == t_piDeath[0])
                    temp_neutron_Hit.isFromPion = 1;
                else
                    temp_neutron_Hit.isFromPion = 0;
                if(t_neutronStartingPointX[n_neutronHit] == t_protonDeath[0])
                    temp_neutron_Hit.isFromProton = 1;
                else
                    temp_neutron_Hit.isFromProton = 0;
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

        Hit temp_gamma_Hit;

        for(int n_gammaHit = 0; n_gammaHit < 1000; n_gammaHit++)
        {
            //out of 3dst
            if(abs(t_gammaHitX[n_gammaHit]) > 120 || 
                    abs(t_gammaHitY[n_gammaHit]) > 120 || 
                    abs(t_gammaHitZ[n_gammaHit]) > 100)
                continue;

            //starting point == -1 is default value so remove it
            if(t_gammaStartingPointX[n_gammaHit] == -1 || 
                    t_gammaStartingPointY[n_gammaHit] == -1 || 
                    t_gammaStartingPointZ[n_gammaHit] == -1 )
                continue;

            //energy threshold
            if(t_gammaCubeE[n_gammaHit] < energyHitCut || t_gammaCubeE[n_gammaHit] == 0)
                continue;

            //calculate lever arm
            float leverArm = pow(
                    pow(t_gammaHitX[n_gammaHit] - t_vtx[0],2)+
                    pow(t_gammaHitY[n_gammaHit] - t_vtx[1],2)+
                    pow(t_gammaHitZ[n_gammaHit] - t_vtx[2],2),0.5);

            //calculate signal window; time of flight
            float tof = t_gammaHitT[n_gammaHit] - t_vtxTime - 1;
            float tofSmear = t_gammaHitSmearT[n_gammaHit] - t_vtxTime - 1;

            //Fix a bug from edep-sim
            if(tof == 1)
                tof = 0.5;

            if(tof > 0)
            {
                temp_gamma_Hit.SetTOF(tof);
                temp_gamma_Hit.SetTOFSmear(tofSmear);
                temp_gamma_Hit.SetLeverArm(leverArm);
                temp_gamma_Hit.SetEnergyDeposit(t_gammaHitE[n_gammaHit]);

                temp_gamma_Hit.SetVtxX(t_vtx[0]);
                temp_gamma_Hit.SetVtxY(t_vtx[1]);
                temp_gamma_Hit.SetVtxZ(t_vtx[2]);

                temp_gamma_Hit.piDeath[0] = t_piDeath[0];
                temp_gamma_Hit.piDeath[1] = t_piDeath[1];
                temp_gamma_Hit.piDeath[2] = t_piDeath[2];

                temp_gamma_Hit.protonDeath[0] = t_protonDeath[0];
                temp_gamma_Hit.protonDeath[1] = t_protonDeath[1];
                temp_gamma_Hit.protonDeath[2] = t_protonDeath[2];

                temp_gamma_Hit.SetTrueT(t_gammaHitT[n_gammaHit]);
                temp_gamma_Hit.SetCubeE(t_gammaCubeE[n_gammaHit]);

                temp_gamma_Hit.SetParentId(t_gammaParentId[n_gammaHit]);
                temp_gamma_Hit.parentPdg = t_gammaParentPDG[n_gammaHit];
                temp_gamma_Hit.SetHitPDG(t_gammaHitPDG[n_gammaHit]);

                temp_gamma_Hit.SetVtxT(t_vtxTime);
                if(t_gammaStartingPointX[n_gammaHit] == t_piDeath[0])
                    temp_gamma_Hit.isFromPion = 1;
                else
                    temp_gamma_Hit.isFromPion = 0;
                if(t_gammaStartingPointX[n_gammaHit] == t_protonDeath[0])
                    temp_gamma_Hit.isFromProton = 1;
                else
                    temp_gamma_Hit.isFromProton = 0;
                temp_gamma_Hit.SetT(t_gammaHitT[n_gammaHit]);
                temp_gamma_Hit.SetX(t_gammaHitX[n_gammaHit]);
                temp_gamma_Hit.SetY(t_gammaHitY[n_gammaHit]);
                temp_gamma_Hit.SetZ(t_gammaHitZ[n_gammaHit]);
                temp_gamma_Hit.SetParentId(t_gammaParentId[n_gammaHit]);
                temp_gamma_Hit.SetIsGamma(true);
                temp_gamma_Hit.SetCubeE(t_gammaCubeE[n_gammaHit]);

                vectorHit.push_back(temp_gamma_Hit);
            }
        }

        if(vectorHit.size() == 0)
            continue;

        //this makes beta <<< 1, 1 spill is 10us, skip this event
        if(vectorHit.at(0).GetTrueT() > 10000)
            continue;

        //sort by time
        if(vectorHit.size() != 0)
            std::sort(vectorHit.begin(), vectorHit.end(), tSort);

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
            lev_time_smeared->Fill(earliest_hit.GetLeverArm()+gRandom->Gaus(0,0.3),earliest_hit.GetTOFSmear());
            //(true-smear)/true
            float true_E, smear_E;
            true_E = 0.7245*pow((earliest_hit.GetLeverArm()/earliest_hit.GetTOF()),2);
            smear_E = 0.7245*pow(((earliest_hit.GetLeverArm()+gRandom->Gaus(0,0.3))/earliest_hit.GetTOFSmear()),2);
            for(int i = 0; i < 20; i++)
            {
                if(10*i< earliest_hit.GetLeverArm() && earliest_hit.GetLeverArm() < 10*(i+1))
                {
                    for(int j = 0; j < 25; j++)
                    {
                        if(j < earliest_hit.GetTOF() && earliest_hit.GetTOF() < j+1)
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
    rms->GetZaxis()->SetRangeUser(0,0.3);
    rms->Draw("colz");
    can4->SaveAs("rms.pdf");

    cout<<"making output files is done"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"all done"<<endl;

    return 0;
}
