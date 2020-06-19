#include "hit.h"
#include "functions.h"


using namespace std;

int main()
{
    gErrorIgnoreLevel = 6000;
    float Z[3] = {0,0,1};
    //
    //signal{
    TH1F * leverarm_signal = new TH1F("leverarm_signal","lever arm of signal",20,0,200);
    TH1F * angle_signal = new TH1F("angle_signal","angle between C and signal hit",20,0,1);
    TH1F * beta_signal = new TH1F("beta_signal","beta of signal",30,0,1.5);
    TH1F * distance_signal = new TH1F("distance_signal","distance b/w C and signal hit",20,0,200);
    TH1F * TOF_signal = new TH1F("TOF_signal","time of flight of signal", 25,0,25);
    TH1F * CubeE_signal = new TH1F("CubeE_signal", "CubeE of signal", 30, 0, 15);
    TH1F * nCubeDis_signal = new TH1F("nCubeDis_signal","number of cubes, signal", 50, 0, 100);
    //}
    //secondary neutron{ 
    TH1F * leverarm_secondary_neutron = new TH1F("leverarm_secondary_neutron","lever arm of secondary_neutron",20,0,200);
    TH1F * angle_secondary_neutron = new TH1F("angle_secondary_neutron","angle between C and secondary_neutron hit",20,0,1);
    TH1F * beta_secondary_neutron = new TH1F("beta_secondary_neutron","beta of secondary_neutron",30,0,1.5);
    TH1F * distance_secondary_neutron = new TH1F("distance_secondary_neutron","distance b/w C and secondary_neutron hit",20,0,200);
    TH1F * TOF_secondary_neutron = new TH1F("TOF_secondary_neutron","time of flight of secondary_neutron", 25,0,25);
    TH1F * CubeE_secondary_neutron = new TH1F("CubeE_secondary_neutron", "CubeE of secondary_neutron", 30, 0, 15);
    TH1F * nCubeDis_secondary_neutron = new TH1F("nCubeDis_secondary_neutron","number of cubes, secondary neutron", 50, 0, 100);
    //}

    //primary gamma{
    TH1F * leverarm_primary_gamma = new TH1F("leverarm_primary_gamma","lever arm of primary_gamma",20,0,200);
    TH1F * angle_primary_gamma = new TH1F("angle_primary_gamma","angle between C and primary_gamma hit",20,0,1);
    TH1F * beta_primary_gamma = new TH1F("beta_primary_gamma","beta of primary_gamma",30,0,1.5);
    TH1F * distance_primary_gamma = new TH1F("distance_primary_gamma","distance b/w C and primary_gamma hit",20,0,200);
    TH1F * TOF_primary_gamma = new TH1F("TOF_primary_gamma","time of flight of primary_gamma", 25,0,25);
    TH1F * CubeE_primary_gamma = new TH1F("CubeE_primary_gamma", "CubeE of primary_gamma", 30, 0, 15);
    TH1F * nCubeDis_primary_gamma = new TH1F("nCubeDis_primary_gamma","number of cubes, primary gamma", 50, 0, 100);
    //}

    //secondary gamma{
    TH1F * leverarm_secondary_gamma = new TH1F("leverarm_secondary_gamma","lever arm of secondary_gamma",20,0,200);
    TH1F * angle_secondary_gamma = new TH1F("angle_secondary_gamma","angle between C and secondary_gamma hit",20,0,1);
    TH1F * beta_secondary_gamma = new TH1F("beta_secondary_gamma","beta of secondary_gamma",30,0,1.5);
    TH1F * distance_secondary_gamma = new TH1F("distance_secondary_gamma","distance b/w C and secondary_gamma hit",20,0,200);
    TH1F * TOF_secondary_gamma = new TH1F("TOF_secondary_gamma","time of flight of secondary_gamma", 25,0,25);
    TH1F * CubeE_secondary_gamma = new TH1F("CubeE_secondary_gamma", "CubeE of secondary_gamma", 30, 0, 15);
    TH1F * nCubeDis_secondary_gamma = new TH1F("nCubeDis_secondary_gamma","number of cubes, secondary gamma", 50, 0, 100);
    //}

    TH1F * timeWindow = new TH1F("timeWindow", "",250,0,25);
    TH2F * XYPlane = new TH2F("XY","XY;X;Y",240,-120,120,240,-120,120);
    TH2F * XZPlane = new TH2F("XZ","XZ;X;Z",240,-120,120,200,-100,100);
    TH2F * YZPlane = new TH2F("YZ","YZ;Y;Z",240,-120,120,200,-100,100);
    TH2F * cube_XYPlane = new TH2F("cube_XY","XY;X;Y",240,-120,120,240,-120,120);
    TH2F * cube_XZPlane = new TH2F("cube_XZ","XZ;X;Z",240,-120,120,200,-100,100);
    TH2F * cube_YZPlane = new TH2F("cube_YZ","YZ;Y;Z",240,-120,120,200,-100,100);
    TH2F * XYPlane_allhits = new TH2F("XY_allhits","XY;X;Y",240,-120,120,240,-120,120);
    TH2F * XZPlane_allhits = new TH2F("XZ_allhits","XZ;X;Z",240,-120,120,200,-100,100);
    TH2F * YZPlane_allhits = new TH2F("YZ_allhits","YZ;Y;Z",240,-120,120,200,-100,100);

    TH1F * secondary_gamma_parentID = new TH1F("","",200,-100,100);
    float energyHitCut = 0.2; //energy deposit threshold for cube
    const double c_velocity = 29.9792458;
    //histograms{

    //}

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

    TFile * outfile = new TFile("variables.root","RECREATE");
    TTree * output_tree = new TTree("output_tree", "output_tree");

    //variable for output root file
    float channel; output_tree->Branch("channel",&channel,"channel 0pi0P_0 0pi_1 1P_2");
    float leverArm; output_tree->Branch("leverArm",&leverArm, "lever arm");
    float angle; output_tree->Branch("angle",&angle, "angle between C and hit");
    float beta; output_tree->Branch("beta",&beta, "beta");
    float distanceCHit; output_tree->Branch("distanceCHit",&distanceCHit, "distance C and hit");
    float tof; output_tree->Branch("tof",&tof, "time of flight");
    float cubeE; output_tree->Branch("cubeE",&cubeE, "CubeE");
    float nCube; output_tree->Branch("nCube", &nCube, "nCube");
    float category; output_tree->Branch("category", &category, "category");
    float neutrinoE; output_tree->Branch("neutrinoE", &neutrinoE, "neutrinoE");
    float hitPDG; output_tree->Branch("hitPDG", &hitPDG, "hitPDG");
    float neutronE; output_tree->Branch("neutronE", &neutronE, "neutronE");
    float neutronAngle; output_tree->Branch("neutronAngle", &neutronAngle, "neutronAngle");
    float singleTransverseVariable_1pi; output_tree->Branch("singleTransverseVariable_1pi", &singleTransverseVariable_1pi, "singleTransverseVariable_1pi");
    float singleTransverseVariable_1P; output_tree->Branch("singleTransverseVariable_1P", &singleTransverseVariable_1P, "singleTransverseVariable_1P");
    float singleTransverseVariable_0pi0P; output_tree->Branch("singleTransverseVariable_0pi0P", &singleTransverseVariable_0pi0P, "singleTransverseVariable_0pi0P");
    float muonAngle; output_tree->Branch("muonAngle", &muonAngle, "muonAngle");
    float muonMomentum; output_tree->Branch("muonMomentum", &muonMomentum, "muonMomentum");
    float Q2; output_tree->Branch("Q2",&Q2,"Q2");

    cout<<"file loading is done"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"total entries: "<<tree.GetEntries()<<endl;
    cout<<"event loop starts"<<endl;
    cout<<endl;

    for(int event = 0; event < tree.GetEntries(); event++)
    {
        tree.GetEntry(event);

        cout<<"\033[1Aevent: "<<((double)event*100/tree.GetEntries())<<"%          \033[1000D"<<endl;
        channel = -1000;
        leverArm = -1000;
        angle = -1000;
        beta = -1000;
        distanceCHit = -1000;
        tof = -1000;
        cubeE = -1000;
        nCube = -1000;
        category = -1000;
        neutrinoE = -1000;
        hitPDG = -1000;
        neutronE = -1000;
        neutronAngle = -1000;
        singleTransverseVariable_1P = -1000;
        singleTransverseVariable_1pi = -1000;
        singleTransverseVariable_0pi0P = -1000;
        muonAngle = -1000;
        muonMomentum = -1000;
        Q2 = -1000;

        //out of fiducial volume
        if(abs(t_vtx[0]) > 50 || abs(t_vtx[1]) > 50 || abs(t_vtx[2]) > 50)
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

        //count # of charged pion,proton in FS
        int num_pi = 0;
        int num_proton = 0;
        int num_pi0 = 0;
        for(int inFS = 0; inFS < t_nFS; inFS++)
        {
            if(abs(t_fsPdg[inFS]) == 111)    //pion0PDG=111
            {
                num_pi0++;
            }
            if(abs(t_fsPdg[inFS]) == 211)    //pionPDG=+-211
            {
                num_pi++;
            }
            if(t_fsPdg[inFS] == 2212)    //protonPDG=+-211
            {
                num_proton++;
            }
        }

        //flags for channels
        bool _1pi0p = false;
        bool _0pi1p = false;
        bool _0pi0p = false;

        if(num_pi == 1 && num_proton == 0)
        {
            _1pi0p = true;
            channel = 1;
        }
        if(num_pi == 0 && num_proton == 1)
        {
            _0pi1p = true;
            channel = 2;
        }
        if(num_pi == 0 && num_proton == 0)
        {
            _0pi0p = true;
            channel = 0;
        }

        if(!_1pi0p && !_0pi1p && !_0pi0p)
            continue;

        if(num_pi0 != 0)
            continue;

        float muon_mometum[3];
        int num_muon = 0;
        float muonE;
        for(int inFS = 0; inFS < t_nFS; inFS++)
        {
            if(t_fsPdg[inFS] == -13)
            {
                muon_mometum[0] = t_fsPx[inFS];
                muon_mometum[1] = t_fsPy[inFS];
                muon_mometum[2] = t_fsPz[inFS];
                muonE = t_fsE[inFS];
                num_muon++;
            }
        }
        //if(num_muon > 1)
        //{
        //    for(int inFS = 0; inFS < t_nFS; inFS++)
        //    {
        //        std::cout<<"pdg: "<<t_fsPdg[inFS]<<endl;
        //    }
        //    cout<<"----------------------"<<endl;
        //}
        if(num_muon != 1)
            continue;

        muonAngle = GetAngle(Z,muon_mometum);
        muonMomentum = sqrt(muon_mometum[0]*muon_mometum[0]+muon_mometum[1]*muon_mometum[1]+muon_mometum[2]*muon_mometum[2]);

        //        if(_0pi1p || _0pi0p)    //only looking for 1pi0p channel
        //            continue;

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
            //float tofSmear = tof + gRandom->Uniform(-0.5,0.5);

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
            //float tofSmear = tof + gRandom->Uniform(-0.5,0.5);

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

        //map<position,pair<true,time>>
        std::map<std::tuple<float,float,float>,std::pair<int,float>> cube_fired;

        for(auto t:vectorHit)
        {
            //cout<<"x,y,z: "<<t.GetX()<<", "<<t.GetY()<<", "<<t.GetZ()<<endl;
            XYPlane_allhits->Fill(t.GetX(),t.GetY());
            YZPlane_allhits->Fill(t.GetY(),t.GetZ());
            XZPlane_allhits->Fill(t.GetX(),t.GetZ());
            std::tuple<float, float, float> temp_position = std::make_tuple(t.GetX(),t.GetY(),t.GetZ());
            cube_fired.insert(make_pair(temp_position,make_pair(1,t.GetT())));  //모든 힛들이 제대로 들어가는것 확인완료
        }

        //cube cluster vector
        std::vector<Hit> cube_cluster;

        //push back the first hit
        cube_cluster.push_back(vectorHit.at(0));
        //erase that hit from cube_fired vector
        cube_fired.erase(std::make_tuple(cube_cluster.at(0).GetX(),cube_cluster.at(0).GetY(),cube_cluster.at(0).GetZ()));
        //cout<<"first hit: "<<cube_cluster.at(0).GetX()<<" ,"<<cube_cluster.at(0).GetY()<<" ,"<<cube_cluster.at(0).GetZ()<<", "<<cube_cluster.at(0).GetT()<<endl;

        bool size_check = true;
        while(size_check)
        {
            int size_before = cube_cluster.size();
            for(auto t:cube_cluster)
            {
                //making adjacent cube 
                int N = 1;      //adjacent cube range
                int number_of_direction_array = 0;
                std::tuple<float, float, float> direction[(2*N+1)*(2*N+1)*(2*N+1)];
                for(int x = -N; x < N+1; x++)
                {
                    for(int y = -N; y < N+1; y++)
                    {
                        for(int z = -N; z < N+1; z++)
                        {
                            direction[number_of_direction_array] = std::make_tuple(t.GetX()+x,t.GetY()+y,t.GetZ()+z);
                            number_of_direction_array++;
                        }
                    }
                }

                for(int i = 0; i < (2*N+1)*(2*N+1)*(2*N+1); i++)
                {
                    if(cube_fired.find(direction[i])->second.first == 1 && abs(t.GetT()-cube_fired.find(direction[i])->second.second) < 1)
                    {
                        Hit temp_hit;
                        temp_hit.SetX(std::get<0>(direction[i]));
                        temp_hit.SetY(std::get<1>(direction[i]));
                        temp_hit.SetZ(std::get<2>(direction[i]));
                        temp_hit.SetT(cube_fired.find(direction[i])->second.second);
                        //cout<<std::get<0>(direction[i])<<", "<<std::get<1>(direction[i])<<", "<<std::get<2>(direction[i])<<endl;
                        cube_fired.erase(direction[i]);
                        cube_cluster.push_back(temp_hit);
                    }
                }
            }

            int size_after = cube_cluster.size();
            if(size_after == size_before)
                size_check = false;
        }

        for(auto t:cube_cluster)
        {
            cube_XYPlane->Fill(t.GetX(),t.GetY());
            cube_XZPlane->Fill(t.GetX(),t.GetZ());
            cube_YZPlane->Fill(t.GetY(),t.GetZ());
        }

        //event display
        //{
        //gStyle->SetFrameFillColor(1);
        //if(XYPlane_allhits->GetEntries() != 0)
        //{
        //    TCanvas * can1 = new TCanvas();
        //    can1->Divide(3,2);
        //    can1->cd(1);
        //    XYPlane_allhits->SetStats(0);
        //    XYPlane_allhits->Draw("colz");
        //    can1->cd(2);
        //    XZPlane_allhits->SetStats(0);
        //    XZPlane_allhits->Draw("colz");
        //    can1->cd(3);
        //    YZPlane_allhits->SetStats(0);
        //    YZPlane_allhits->Draw("colz");

        //    can1->cd(4);
        //    cube_XYPlane->SetStats(0);
        //    cube_XYPlane->Draw("colz");
        //    can1->cd(5);
        //    cube_XZPlane->SetStats(0);
        //    cube_XZPlane->Draw("colz");
        //    can1->cd(6);
        //    cube_YZPlane->SetStats(0);
        //    cube_YZPlane->Draw("colz");
        //    can1->SaveAs(Form("cube_eventview_%d.pdf",event));
        //    can1->Clear();
        //}
        //XYPlane_allhits->Reset();
        //XZPlane_allhits->Reset();
        //YZPlane_allhits->Reset();
        //cube_XYPlane->Reset();
        //cube_XZPlane->Reset();
        //cube_YZPlane->Reset();
        //}

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

        for(int i = 0; i < 3; i++)
        {
            if(i == 0)
            {
                vec_piDeath_to_hit[i] = earliest_hit.GetX()-earliest_hit.piDeath[i];
                vec_vtx_to_piDeath[i] = earliest_hit.piDeath[i]-earliest_hit.GetVtxX();
                vec_protonDeath_to_hit[i] = earliest_hit.GetX()-earliest_hit.protonDeath[i];
                vec_vtx_to_protonDeath[i] = earliest_hit.protonDeath[i]-earliest_hit.GetVtxX();
            }
            if(i == 1)
            {
                vec_piDeath_to_hit[i] = earliest_hit.GetY()-earliest_hit.piDeath[i];
                vec_vtx_to_piDeath[i] = earliest_hit.piDeath[i]-earliest_hit.GetVtxY();
                vec_protonDeath_to_hit[i] = earliest_hit.GetY()-earliest_hit.protonDeath[i];
                vec_vtx_to_protonDeath[i] = earliest_hit.protonDeath[i]-earliest_hit.GetVtxY();
            }
            if(i == 2)
            {
                vec_piDeath_to_hit[i] = earliest_hit.GetZ()-earliest_hit.piDeath[i];
                vec_vtx_to_piDeath[i] = earliest_hit.piDeath[i]-earliest_hit.GetVtxZ();
                vec_protonDeath_to_hit[i] = earliest_hit.GetZ()-earliest_hit.protonDeath[i];
                vec_vtx_to_protonDeath[i] = earliest_hit.protonDeath[i]-earliest_hit.GetVtxZ();
            }
        }

        float vec_vtx_to_hit[3];
        vec_vtx_to_hit[0] = earliest_hit.GetX() - earliest_hit.GetVtxX();
        vec_vtx_to_hit[1] = earliest_hit.GetY() - earliest_hit.GetVtxY();
        vec_vtx_to_hit[2] = earliest_hit.GetZ() - earliest_hit.GetVtxZ();

        //signal
        if(earliest_hit.GetCategory() == 1)
        {
            leverarm_signal->Fill(earliest_hit.GetLeverArm());
            leverArm = earliest_hit.GetLeverArm();
            if(_1pi0p)
            {
                angle_signal->Fill(GetAngle(vec_vtx_to_piDeath,vec_piDeath_to_hit));
                angle = GetAngle(vec_vtx_to_piDeath,vec_piDeath_to_hit);
                distance_signal->Fill(GetDistance(earliest_hit.piDeath,earliest_hit));
                distanceCHit = GetDistance(earliest_hit.piDeath,earliest_hit);
            }
            if(_0pi1p)
            {
                angle_signal->Fill(GetAngle(vec_vtx_to_protonDeath,vec_protonDeath_to_hit));
                angle = GetAngle(vec_vtx_to_protonDeath,vec_protonDeath_to_hit);
                distance_signal->Fill(GetDistance(earliest_hit.protonDeath,earliest_hit));
                distanceCHit = GetDistance(earliest_hit.protonDeath,earliest_hit);
            }
            if(_0pi0p)
            {
                angle = -1000;
                distanceCHit = -1000;
            }

            beta_signal->Fill((earliest_hit.GetLeverArm()/earliest_hit.GetTOFSmear())/c_velocity);
            beta = (earliest_hit.GetLeverArm()/earliest_hit.GetTOFSmear())/c_velocity;
            TOF_signal->Fill(earliest_hit.GetTOFSmear());
            tof = earliest_hit.GetTOFSmear();
            CubeE_signal->Fill(earliest_hit.GetCubeE());
            cubeE = earliest_hit.GetCubeE();
            nCubeDis_signal->Fill(cube_cluster.size());
            nCube = cube_cluster.size();
            hitPDG = earliest_hit.GetHitPDG();

            neutronE = earliest_hit.GetTrueE();
            neutronAngle = GetAngle(Z,vec_vtx_to_hit);
        }

        //secondary neutron
        if(earliest_hit.GetCategory() == 2)
        {
            leverarm_secondary_neutron->Fill(earliest_hit.GetLeverArm());
            leverArm = earliest_hit.GetLeverArm();
            if(_1pi0p)
            {
                angle_secondary_neutron->Fill(GetAngle(vec_vtx_to_piDeath,vec_piDeath_to_hit));
                angle = GetAngle(vec_vtx_to_piDeath,vec_piDeath_to_hit);
                distance_secondary_neutron->Fill(GetDistance(earliest_hit.piDeath,earliest_hit));
                distanceCHit = GetDistance(earliest_hit.piDeath,earliest_hit);
            }
            if(_0pi1p)
            {
                angle_secondary_neutron->Fill(GetAngle(vec_vtx_to_protonDeath,vec_protonDeath_to_hit));
                angle = GetAngle(vec_vtx_to_protonDeath,vec_protonDeath_to_hit);
                distance_secondary_neutron->Fill(GetDistance(earliest_hit.protonDeath,earliest_hit));
                distanceCHit = GetDistance(earliest_hit.protonDeath,earliest_hit);
            }
            if(_0pi0p)
            {
                angle = -1000;
                distanceCHit = -1000;
            }
            beta_secondary_neutron->Fill((earliest_hit.GetLeverArm()/earliest_hit.GetTOFSmear())/c_velocity);
            beta = (earliest_hit.GetLeverArm()/earliest_hit.GetTOFSmear())/c_velocity;
            TOF_secondary_neutron->Fill(earliest_hit.GetTOFSmear());
            tof = earliest_hit.GetTOFSmear();
            CubeE_secondary_neutron->Fill(earliest_hit.GetCubeE());
            cubeE = earliest_hit.GetCubeE();
            nCubeDis_secondary_neutron->Fill(cube_cluster.size());
            nCube = cube_cluster.size();
            hitPDG = earliest_hit.GetHitPDG();

            neutronE = earliest_hit.GetTrueE();
            neutronAngle = GetAngle(Z,vec_vtx_to_hit);
        }

        //primary gamma 
        if(earliest_hit.GetCategory() == 3)
        {
            leverarm_primary_gamma->Fill(earliest_hit.GetLeverArm());
            leverArm = earliest_hit.GetLeverArm();
            if(_1pi0p)
            {
                angle_primary_gamma->Fill(GetAngle(vec_vtx_to_piDeath,vec_piDeath_to_hit));
                angle = GetAngle(vec_vtx_to_piDeath,vec_piDeath_to_hit);
                distance_primary_gamma->Fill(GetDistance(earliest_hit.piDeath,earliest_hit));
                distanceCHit = GetDistance(earliest_hit.piDeath,earliest_hit);
            }
            if(_0pi1p)
            {
                angle_primary_gamma->Fill(GetAngle(vec_vtx_to_protonDeath,vec_protonDeath_to_hit));
                angle = GetAngle(vec_vtx_to_protonDeath,vec_protonDeath_to_hit);
                distance_primary_gamma->Fill(GetDistance(earliest_hit.protonDeath,earliest_hit));
                distanceCHit = GetDistance(earliest_hit.protonDeath,earliest_hit);
            }
            if(_0pi0p)
            {
                angle = -1000;
                distanceCHit = -1000;
            }
            beta_primary_gamma->Fill((earliest_hit.GetLeverArm()/(earliest_hit.GetTOFSmear()))/c_velocity);
            beta = (earliest_hit.GetLeverArm()/(earliest_hit.GetTOFSmear()))/c_velocity;
            TOF_primary_gamma->Fill(earliest_hit.GetTOFSmear());
            tof = earliest_hit.GetTOFSmear();
            CubeE_primary_gamma->Fill(earliest_hit.GetCubeE());
            cubeE = earliest_hit.GetCubeE();
            nCubeDis_primary_gamma->Fill(cube_cluster.size());
            nCube = cube_cluster.size();
            hitPDG = earliest_hit.GetHitPDG();
        }

        //secondary gamma
        if(earliest_hit.GetCategory() == 4)
        {
            leverarm_secondary_gamma->Fill(earliest_hit.GetLeverArm());
            leverArm = earliest_hit.GetLeverArm();
            if(_1pi0p)
            {
                angle_secondary_gamma->Fill(GetAngle(vec_vtx_to_piDeath,vec_piDeath_to_hit));
                angle = GetAngle(vec_vtx_to_piDeath,vec_piDeath_to_hit);
                distance_secondary_gamma->Fill(GetDistance(earliest_hit.piDeath,earliest_hit));
                distanceCHit = GetDistance(earliest_hit.piDeath,earliest_hit);
            }
            if(_0pi1p)
            {
                angle_secondary_gamma->Fill(GetAngle(vec_vtx_to_protonDeath,vec_protonDeath_to_hit));
                angle = GetAngle(vec_vtx_to_protonDeath,vec_protonDeath_to_hit);
                distance_secondary_gamma->Fill(GetDistance(earliest_hit.protonDeath,earliest_hit));
                distanceCHit = GetDistance(earliest_hit.protonDeath,earliest_hit);
            }
            if(_0pi0p)
            {
                angle = -1000;
                distanceCHit = -1000;
            }
            beta_secondary_gamma->Fill((earliest_hit.GetLeverArm()/earliest_hit.GetTOFSmear())/c_velocity);
            beta = (earliest_hit.GetLeverArm()/earliest_hit.GetTOFSmear())/c_velocity;
            TOF_secondary_gamma->Fill(earliest_hit.GetTOFSmear());
            tof = earliest_hit.GetTOFSmear();
            CubeE_secondary_gamma->Fill(earliest_hit.GetCubeE());
            cubeE = earliest_hit.GetCubeE();
            nCubeDis_secondary_gamma->Fill(cube_cluster.size());
            nCube = cube_cluster.size();
            hitPDG = earliest_hit.GetHitPDG();
            secondary_gamma_parentID->Fill(earliest_hit.GetPDG());
        }
        //transverse momentum
        float Px = 0;
        float Py = 0;
        for(int inFS = 0; inFS < t_nFS; inFS++)
        {
            Px += t_fsPx[inFS];
            Py += t_fsPy[inFS];
        }
        if(isinf(beta))
        {
            //cout<<"inf beta"<<endl;
            beta = -1000;
        }
        if(_1pi0p)
            singleTransverseVariable_1pi = sqrt(Px*Px+Py*Py);
        if(_0pi1p)
            singleTransverseVariable_1P = sqrt(Px*Px+Py*Py);
        if(_0pi0p)
            singleTransverseVariable_0pi0P = sqrt(Px*Px+Py*Py);
        neutrinoE = t_nuEnergy;
        Q2 = 4*neutrinoE*muonE*0.001*pow(TMath::Sin(TMath::Pi()*muonAngle/2),2);
        category = earliest_hit.GetCategory();
        output_tree->Fill();

    }//end of event iterate

    outfile->Write();
    outfile->Close();

    cout<<"event loop is aone"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"making output files"<<endl;

    TFile * fi1 = new TFile("background.root","RECREATE");
    gStyle->SetFrameFillColor(0);

    Font_t ft = 132;
    gStyle->SetLabelSize(50,"XY");
    gStyle->SetTitleSize(50,"XY");
    //gStyle->SetLegendSize(5);

    TCanvas * can = new TCanvas;

    TLegend * legend = new TLegend(0.5,0.6,0.9,0.9);
    legend->SetHeader("DUNE: Simulation","C");
    legend->AddEntry(leverarm_signal,"signal","l");
    legend->AddEntry(leverarm_secondary_neutron,"secondary neutron","l");
    legend->AddEntry(leverarm_primary_gamma,"primary gamma","l");
    legend->AddEntry(leverarm_secondary_gamma,"secondary gamma","l");
    legend->SetTextSize(0.055);

    TLegend * legend1 = new TLegend(0.1,0.6,0.5,0.9);
    legend1->SetHeader("DUNE: Simulation","C");
    legend1->AddEntry(leverarm_signal,"signal","l");
    legend1->AddEntry(leverarm_secondary_neutron,"secondary neutron","l");
    legend1->AddEntry(leverarm_primary_gamma,"primary gamma","l");
    legend1->AddEntry(leverarm_secondary_gamma,"secondary gamma","l");
    legend1->SetTextSize(0.055);

    /*
     * 2: red, signal
     * 4: blue, secondary neutron
     * 6: purple, primary gamma
     * 1: black, secondary gamma
     */

    //leaverarm{
    leverarm_signal->Write();
    leverarm_signal->GetXaxis()->SetTitle("[cm]");
    leverarm_signal->GetYaxis()->SetTitle("Normalized fraction");
    leverarm_signal->GetYaxis()->CenterTitle(1);
    leverarm_signal->GetXaxis()->SetLabelSize(0.045);
    leverarm_signal->GetYaxis()->SetLabelSize(0.045);
    leverarm_signal->GetXaxis()->SetTitleSize(0.060);
    leverarm_signal->GetYaxis()->SetTitleSize(0.055);
    leverarm_signal->GetYaxis()->SetTitleOffset(0.9);
    leverarm_signal->GetXaxis()->SetTitleOffset(0.70);
    leverarm_signal->SetLineColor(2);
    leverarm_signal->SetLineWidth(3);
    leverarm_signal->SetStats(0);
    leverarm_signal->Scale(1/leverarm_signal->Integral(),"nosw2");
    leverarm_signal->GetXaxis()->SetTitle("cm");
    leverarm_signal->GetYaxis()->SetRangeUser(0,0.4);
    leverarm_signal->SetTitle("lever arm");
    leverarm_signal->Draw();

    leverarm_secondary_neutron->Write();
    leverarm_secondary_neutron->SetLineColor(4);
    leverarm_secondary_neutron->SetLineWidth(3);
    leverarm_secondary_neutron->SetStats(0);
    leverarm_secondary_neutron->Scale(1/leverarm_secondary_neutron->Integral(),"nosw2");
    leverarm_secondary_neutron->Draw("same");

    leverarm_primary_gamma->Write();
    leverarm_primary_gamma->SetLineColor(6);
    leverarm_primary_gamma->SetLineWidth(3);
    leverarm_primary_gamma->SetStats(0);
    leverarm_primary_gamma->Scale(1/leverarm_primary_gamma->Integral(),"nosw2");
    leverarm_primary_gamma->Draw("same");

    leverarm_secondary_gamma->Write();
    leverarm_secondary_gamma->SetLineColor(1);
    leverarm_secondary_gamma->SetLineWidth(3);
    leverarm_secondary_gamma->SetStats(0);
    leverarm_secondary_gamma->Scale(1/leverarm_secondary_gamma->Integral(),"nosw2");
    leverarm_secondary_gamma->Draw("same");

    legend->Draw();
    can->SaveAs("leverarm.pdf");
    can->Clear();
    //}

    //angle{
    angle_signal->Write();
    angle_signal->GetXaxis()->SetTitle("[π]");
    angle_signal->GetYaxis()->SetTitle("Normalized fraction");
    angle_signal->GetYaxis()->CenterTitle(1);
    angle_signal->GetXaxis()->SetLabelSize(0.045);
    angle_signal->GetYaxis()->SetLabelSize(0.045);
    angle_signal->GetXaxis()->SetTitleSize(0.060);
    angle_signal->GetYaxis()->SetTitleSize(0.055);
    angle_signal->GetYaxis()->SetTitleOffset(0.9);
    angle_signal->GetXaxis()->SetTitleOffset(0.70);
    angle_signal->SetLineColor(2);
    angle_signal->SetLineWidth(3);
    angle_signal->SetStats(0);
    angle_signal->Scale(1/angle_signal->Integral(),"nosw2");
    angle_signal->GetXaxis()->SetTitle("pi");
    angle_signal->GetYaxis()->SetRangeUser(0,0.4);
    angle_signal->SetTitle("angle");
    angle_signal->Draw();

    angle_secondary_neutron->Write();
    angle_secondary_neutron->SetLineColor(4);
    angle_secondary_neutron->SetLineWidth(3);
    angle_secondary_neutron->SetStats(0);
    angle_secondary_neutron->Scale(1/angle_secondary_neutron->Integral(),"nosw2");
    angle_secondary_neutron->Draw("same");

    angle_primary_gamma->Write();
    angle_primary_gamma->SetLineColor(6);
    angle_primary_gamma->SetLineWidth(3);
    angle_primary_gamma->SetStats(0);
    angle_primary_gamma->Scale(1/angle_primary_gamma->Integral(),"nosw2");
    angle_primary_gamma->Draw("same");

    angle_secondary_gamma->Write();
    angle_secondary_gamma->SetLineColor(1);
    angle_secondary_gamma->SetLineWidth(3);
    angle_secondary_gamma->SetStats(0);
    angle_secondary_gamma->Scale(1/angle_secondary_gamma->Integral(),"nosw2");
    angle_secondary_gamma->Draw("same");

    legend1->Draw();
    can->SaveAs("angle.pdf");
    can->Clear();
    //}

    //beta{
    beta_signal->Write();
    beta_signal->GetXaxis()->SetTitle("speed of particle/c");
    beta_signal->GetYaxis()->SetTitle("Normalized fraction");
    beta_signal->GetYaxis()->CenterTitle(1);
    beta_signal->GetXaxis()->SetLabelSize(0.045);
    beta_signal->GetYaxis()->SetLabelSize(0.045);
    beta_signal->GetXaxis()->SetTitleSize(0.060);
    beta_signal->GetYaxis()->SetTitleSize(0.055);
    beta_signal->GetYaxis()->SetTitleOffset(0.9);
    beta_signal->GetXaxis()->SetTitleOffset(0.70);
    beta_signal->SetLineColor(2);
    beta_signal->SetLineWidth(3);
    beta_signal->SetStats(0);
    beta_signal->Scale(1/beta_signal->Integral(),"nosw2");
    beta_signal->GetXaxis()->SetTitle("speed of particle/c");
    beta_signal->GetYaxis()->SetRangeUser(0,0.3);
    beta_signal->SetTitle("beta");
    beta_signal->Draw();

    beta_secondary_neutron->Write();
    beta_secondary_neutron->SetLineColor(4);
    beta_secondary_neutron->SetLineWidth(3);
    beta_secondary_neutron->SetStats(0);
    beta_secondary_neutron->Scale(1/beta_secondary_neutron->Integral(),"nosw2");
    beta_secondary_neutron->Draw("same");

    beta_primary_gamma->Write();
    beta_primary_gamma->SetLineColor(6);
    beta_primary_gamma->SetLineWidth(3);
    beta_primary_gamma->SetStats(0);
    beta_primary_gamma->Scale(1/beta_primary_gamma->Integral(),"nosw2");
    beta_primary_gamma->Draw("same");

    beta_secondary_gamma->Write();
    beta_secondary_gamma->SetLineColor(1);
    beta_secondary_gamma->SetLineWidth(3);
    beta_secondary_gamma->SetStats(0);
    beta_secondary_gamma->Scale(1/beta_secondary_gamma->Integral(),"nosw2");
    beta_secondary_gamma->Draw("same");

    legend1->Draw();
    can->SaveAs("beta.pdf");
    can->Clear();
    //}

    //distance{
    distance_signal->Write();
    distance_signal->GetXaxis()->SetTitle("[cm]");
    distance_signal->GetYaxis()->SetTitle("Normalized fraction");
    distance_signal->GetYaxis()->CenterTitle(1);
    distance_signal->GetXaxis()->SetLabelSize(0.045);
    distance_signal->GetYaxis()->SetLabelSize(0.045);
    distance_signal->GetXaxis()->SetTitleSize(0.060);
    distance_signal->GetYaxis()->SetTitleSize(0.055);
    distance_signal->GetYaxis()->SetTitleOffset(0.9);
    distance_signal->GetXaxis()->SetTitleOffset(0.70);
    distance_signal->SetLineColor(2);
    distance_signal->SetLineWidth(3);
    distance_signal->SetStats(0);
    distance_signal->Scale(1/distance_signal->Integral(),"nosw2");
    distance_signal->GetXaxis()->SetTitle("cm");
    distance_signal->GetYaxis()->SetRangeUser(0,0.6);
    distance_signal->SetTitle("distance b/w C and hit");
    distance_signal->Draw();

    distance_secondary_neutron->Write();
    distance_secondary_neutron->SetLineColor(4);
    distance_secondary_neutron->SetLineWidth(3);
    distance_secondary_neutron->SetStats(0);
    distance_secondary_neutron->Scale(1/distance_secondary_neutron->Integral(),"nosw2");
    distance_secondary_neutron->Draw("same");

    distance_primary_gamma->Write();
    distance_primary_gamma->SetLineColor(6);
    distance_primary_gamma->SetLineWidth(3);
    distance_primary_gamma->SetStats(0);
    distance_primary_gamma->Scale(1/distance_primary_gamma->Integral(),"nosw2");
    distance_primary_gamma->Draw("same");

    distance_secondary_gamma->Write();
    distance_secondary_gamma->SetLineColor(1);
    distance_secondary_gamma->SetLineWidth(3);
    distance_secondary_gamma->SetStats(0);
    distance_secondary_gamma->Scale(1/distance_secondary_gamma->Integral(),"nosw2");
    distance_secondary_gamma->Draw("same");

    legend->Draw();
    can->SaveAs("distance.pdf");
    can->Clear();
    //}

    //TOF{
    TOF_signal->Write();
    TOF_signal->GetXaxis()->SetTitle("[ns]");
    TOF_signal->GetYaxis()->SetTitle("Normalized fraction");
    TOF_signal->GetYaxis()->CenterTitle(1);
    TOF_signal->GetXaxis()->SetLabelSize(0.045);
    TOF_signal->GetYaxis()->SetLabelSize(0.045);
    TOF_signal->GetXaxis()->SetTitleSize(0.060);
    TOF_signal->GetYaxis()->SetTitleSize(0.055);
    TOF_signal->GetYaxis()->SetTitleOffset(0.9);
    TOF_signal->GetXaxis()->SetTitleOffset(0.70);
    TOF_signal->SetLineColor(2);
    TOF_signal->SetLineWidth(3);
    TOF_signal->SetStats(0);
    TOF_signal->Scale(1/TOF_signal->Integral(),"nosw2");
    TOF_signal->GetXaxis()->SetTitle("ns");
    TOF_signal->GetYaxis()->SetRangeUser(0,0.7);
    TOF_signal->SetTitle("Time of flight");
    TOF_signal->Draw();

    TOF_secondary_neutron->Write();
    TOF_secondary_neutron->SetLineColor(4);
    TOF_secondary_neutron->SetLineWidth(3);
    TOF_secondary_neutron->SetStats(0);
    TOF_secondary_neutron->Scale(1/TOF_secondary_neutron->Integral(),"nosw2");
    TOF_secondary_neutron->Draw("same");

    TOF_primary_gamma->Write();
    TOF_primary_gamma->SetLineColor(6);
    TOF_primary_gamma->SetLineWidth(3);
    TOF_primary_gamma->SetStats(0);
    TOF_primary_gamma->Scale(1/TOF_primary_gamma->Integral(),"nosw2");
    TOF_primary_gamma->Draw("same");

    TOF_secondary_gamma->Write();
    TOF_secondary_gamma->SetLineColor(1);
    TOF_secondary_gamma->SetLineWidth(3);
    TOF_secondary_gamma->SetStats(0);
    TOF_secondary_gamma->Scale(1/TOF_secondary_gamma->Integral(),"nosw2");
    TOF_secondary_gamma->Draw("same");

    legend->Draw();
    can->SaveAs("TOF.pdf");
    can->Clear();
    //}

    //CubeE{
    CubeE_signal->Write();
    CubeE_signal->GetXaxis()->SetTitle("[MeV]");
    CubeE_signal->GetYaxis()->SetTitle("Normalized fraction");
    CubeE_signal->GetYaxis()->CenterTitle(1);
    CubeE_signal->GetXaxis()->SetLabelSize(0.045);
    CubeE_signal->GetYaxis()->SetLabelSize(0.045);
    CubeE_signal->GetXaxis()->SetTitleSize(0.060);
    CubeE_signal->GetYaxis()->SetTitleSize(0.055);
    CubeE_signal->GetYaxis()->SetTitleOffset(0.9);
    CubeE_signal->GetXaxis()->SetTitleOffset(0.70);
    CubeE_signal->SetLineColor(2);
    CubeE_signal->SetLineWidth(3);
    CubeE_signal->SetStats(0);
    CubeE_signal->Scale(1/CubeE_signal->Integral(),"nosw2");
    CubeE_signal->GetXaxis()->SetTitle("MeV");
    CubeE_signal->GetYaxis()->SetRangeUser(0,0.7);
    CubeE_signal->SetTitle("CubeE");
    CubeE_signal->Draw();

    CubeE_secondary_neutron->Write();
    CubeE_secondary_neutron->SetLineColor(4);
    CubeE_secondary_neutron->SetLineWidth(3);
    CubeE_secondary_neutron->SetStats(0);
    CubeE_secondary_neutron->Scale(1/CubeE_secondary_neutron->Integral(),"nosw2");
    CubeE_secondary_neutron->Draw("same");

    CubeE_primary_gamma->Write();
    CubeE_primary_gamma->SetLineColor(6);
    CubeE_primary_gamma->SetLineWidth(3);
    CubeE_primary_gamma->SetStats(0);
    CubeE_primary_gamma->Scale(1/CubeE_primary_gamma->Integral(),"nosw2");
    CubeE_primary_gamma->Draw("same");

    CubeE_secondary_gamma->Write();
    CubeE_secondary_gamma->SetLineColor(1);
    CubeE_secondary_gamma->SetLineWidth(3);
    CubeE_secondary_gamma->SetStats(0);
    CubeE_secondary_gamma->Scale(1/CubeE_secondary_gamma->Integral(),"nosw2");
    CubeE_secondary_gamma->Draw("same");

    legend->Draw();
    can->SaveAs("CubeE.pdf");
    can->Clear();
    //}

    //nCube{
    nCubeDis_signal->Write();
    nCubeDis_signal->GetXaxis()->SetTitle("number of fired cube");
    nCubeDis_signal->GetYaxis()->SetTitle("Normalized fraction");
    nCubeDis_signal->GetYaxis()->CenterTitle(1);
    nCubeDis_signal->GetXaxis()->SetLabelSize(0.045);
    nCubeDis_signal->GetYaxis()->SetLabelSize(0.045);
    nCubeDis_signal->GetXaxis()->SetTitleSize(0.060);
    nCubeDis_signal->GetYaxis()->SetTitleSize(0.055);
    nCubeDis_signal->GetYaxis()->SetTitleOffset(0.9);
    nCubeDis_signal->GetXaxis()->SetTitleOffset(0.70);
    nCubeDis_signal->GetYaxis()->SetRangeUser(0,0.5);
    nCubeDis_signal->SetLineColor(2);
    nCubeDis_signal->SetLineColor(2);
    nCubeDis_signal->SetLineWidth(3);
    nCubeDis_signal->SetStats(0);
    nCubeDis_signal->Scale(1/nCubeDis_signal->Integral(),"nosw2");
    nCubeDis_signal->GetXaxis()->SetTitle("number of fired cubes");
    nCubeDis_signal->GetYaxis()->SetRangeUser(0,0.5);
    nCubeDis_signal->SetTitle("number of cube");
    nCubeDis_signal->Draw();

    nCubeDis_secondary_neutron->Write();
    nCubeDis_secondary_neutron->SetLineColor(4);
    nCubeDis_secondary_neutron->SetLineColor(4);
    nCubeDis_secondary_neutron->SetLineWidth(3);
    nCubeDis_secondary_neutron->SetStats(0);
    nCubeDis_secondary_neutron->Scale(1/nCubeDis_secondary_neutron->Integral(),"nosw2");
    nCubeDis_secondary_neutron->Draw("same");

    nCubeDis_primary_gamma->Write();
    nCubeDis_primary_gamma->SetLineColor(6);
    nCubeDis_primary_gamma->SetLineColor(6);
    nCubeDis_primary_gamma->SetLineWidth(3);
    nCubeDis_primary_gamma->SetStats(0);
    nCubeDis_primary_gamma->Scale(1/nCubeDis_primary_gamma->Integral(),"nosw2");
    nCubeDis_primary_gamma->Draw("same");

    nCubeDis_secondary_gamma->Write();
    nCubeDis_secondary_gamma->SetLineColor(1);
    nCubeDis_secondary_gamma->SetLineColor(1);
    nCubeDis_secondary_gamma->SetLineWidth(3);
    nCubeDis_secondary_gamma->SetStats(0);
    nCubeDis_secondary_gamma->Scale(1/nCubeDis_secondary_gamma->Integral(),"nosw2");
    nCubeDis_secondary_gamma->Draw("same");

    legend->Draw();
    can->SaveAs("nCubeDis.pdf");
    can->Clear();
    //}

    secondary_gamma_parentID->Draw();
    can->SaveAs("secondary_gamma_parentID.pdf");
    can->Clear();
    fi1->Close();

    cout<<"making output files is done"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"all done"<<endl;

    return 0;
}
