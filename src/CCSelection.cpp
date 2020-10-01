#include "CCSelection.h"

using namespace std;

int main()
{
    TChain tree("tree");
    for(int i = 1; i != 1000; i++)
    { //cout<<"\033[1APROD"<<101<<": "<<(double)(i*100/filenum)<<"%\033[1000D"<<endl;
        string file = Form("/Users/gwon/Geo12/PROD101/RHC_%d_wGamma_2ndVersion_wNuE.root",i);
        //string file = Form("/Users/gwon/Geo12/PROD101/RHC_%d_wGamma_2ndVersion.root",i);
        //string file = Form("/pnfs/dune/persistent/users/gyang/3DST/dump/standardGeo12/PROD101/RHC_%d_wGamma_2ndVersion.root",i);
        tree.Add(TString(file));
    }

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

    TFile * outfile = new TFile("CC_selected.root","RECREATE");
    TTree * output_tree = tree.CloneTree(0);

    for(int i = 0; i < tree.GetEntries(); i++)
    {
        tree.GetEntry(i);
        cout<<"\033[1Aevent: "<<((double)i*100/tree.GetEntries())<<"%          \033[1000D"<<endl;
        //check whether it's CC event or not
        bool is_CC = false;
        for(int inFS = 0; inFS < t_nFS; inFS++)
        {
            if(t_fsPdg[inFS] == -13)    //muonPDG=13
            {
                is_CC = true;
                break;
            }
        }

        //if it's not CC skip this event
        if(!is_CC)
            continue;
        output_tree->Fill();
    }
    output_tree->Print();
    outfile->Write();
    return 0;
}
