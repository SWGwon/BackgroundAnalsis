#include "hit.h"
#include "functions.h"
#include <unistd.h>

using namespace std;

void help()
{
    cout<<"Usage: ./BackgroundAnalysis [OPTION]"<<endl;
    cout<<"Options:"<<endl;
    cout<<"  --help, -h                  : show this help message and exit"<<endl;
    cout<<"  --output, -o [FILE NAME]    : output file name"<<endl;
    cout<<"  --display, -D               : save event display"<<endl;
    cout<<"  --noGamma                   : not include gamma hits"<<endl;
    cout<<"  --noNeutron                 : not include neutron hits"<<endl;
    cout<<"  --threshold, -t [NUMBER]    : energy threshold for hits"<<endl;
    cout<<"  --inputfile, -i [file]      : directory of input files"<<endl;
    cout<<"  -u [NUMBER]                 : using [NUMBER]\% of entry"<<endl;
    cout<<"  --3DST_centerX ,-x [NUMBER] : X location of 3DST center"<<endl;
    cout<<"  --3DST_centerY ,-y [NUMBER] : Y location of 3DST center"<<endl;
    cout<<"  --3DST_centerZ ,-z [NUMBER] : Z location of 3DST center"<<endl;
}

int main(int argc, char * argv[])
{

    gErrorIgnoreLevel = 6000;
    int _3DST_centerX = 0; 
    int _3DST_centerY = 0; 
    int _3DST_centerZ = -50; 
    int _3DSTx = 240; 
    int _3DSTy = 240; 
    int _3DSTz = 200; 
    int FV_x = 100;
    int FV_y = 100;
    int FV_z = 100;

    float energyHitCut = 0.2; //energy deposit threshold for cube
    int IsExtendCube = false;
    int event_display = false;
    int include_gammaHit = true;
    int include_neutronHit = true;
    int numPionRequire = 0;
    float event_ratio_for_use = 100;
    string name_output_file = "variables.root";
    string name_input_file;
    string input_directory;

    struct option options[] = 
        {
            {"extendCube", 0, &IsExtendCube, true},
            {"display", 0, 0, 'd'},
            {"noGamma", 0, &include_gammaHit, false},
            {"noNeutron", 0, &include_neutronHit, false},
            {"output", 1, 0, 'o'},
            {"threshold", 1, 0,'t'},
            {"help", 0, 0, 'h'},
            {"inputfile", 1, 0, 'i'},
            {"3DST_centerX", 1, 0, 'x'},
            {"3DST_centerY", 1, 0, 'y'},
            {"3DST_centerZ", 1, 0, 'z'},
            {"pion", 1, 0, 'p'}
        };

    int option_index = 0;
    int option = 0;

    while((option = getopt_long(argc, argv, "dho:u:i:p:x:y:z:", options, &option_index))!=EOF)
    {
        switch(option)
        {
            case 'h' :
                {
                    help();
                    return 0;
                }
            case 'o' :
                {
                    name_output_file = optarg;
                    break;
                }
            case 'u' :
                {
                    std::stringstream temp(optarg);
                    temp >> event_ratio_for_use;
                    break;
                }
            case 'd' :
                {
                    event_display = true;
                    break;
                }
            case 't' :
                {
                    stringstream temp(optarg);
                    temp >> energyHitCut;
                    break;
                }
            case 'i' :
                {
                    name_input_file = optarg;
                    break;
                }
            case 'p' :
                {
                    std::stringstream temp(optarg);
                    temp >> numPionRequire;
                    break;
                }
            case 'x' :
                {
                    std::stringstream temp(optarg);
                    temp >> _3DST_centerX;
                    break;
                }
            case 'y' :
                {
                    std::stringstream temp(optarg);
                    temp >> _3DST_centerY;
                    break;
                }
            case 'z' :
                {
                    std::stringstream temp(optarg);
                    temp >> _3DST_centerZ;
                    break;
                }
        }
    }

    //histograms,
    //0: primary neutron
    //1: secondary neutron
    //2: primary gamma
    //{
    TH1F * hist_leverarm[3];
    TH1F * hist_angle[3];
    TH1F * hist_beta[3];
    TH1F * hist_distance[3];
    TH1F * hist_TOF[3];
    TH1F * hist_CubeE[3];
    TH1F * hist_nCubeDis[3];
    TH1F * hist_betaSmear[3];
    TH1F * hist_TOFSmear[3];
    TH1F * hist_clusterEnergy[3];
    //}

    //primary neutron{
    hist_leverarm[0] = new TH1F("leverarm_signal","lever arm of signal",20,0,200);
    hist_angle[0] = new TH1F("angle_signal","angle between C and signal hit",20,0,1);
    hist_beta[0] = new TH1F("beta_signal","beta of signal",30,0,1.5);
    hist_distance[0] = new TH1F("distance_signal","distance b/w C and signal hit",20,0,200);
    hist_TOF[0] = new TH1F("TOF_signal","time of flight of signal", 25,0,25);
    hist_CubeE[0] = new TH1F("CubeE_signal", "CubeE of signal", 30, 0, 15);
    hist_nCubeDis[0] = new TH1F("nCubeDis_signal","number of cubes, signal", 50, 0, 100);
    hist_betaSmear[0] = new TH1F("betaSmear_signal","beta of signal smearT",30,0,1.5);
    hist_TOFSmear[0] = new TH1F("TOFSmear_signal","time of flight of signal smearT", 25,0,25);
    hist_clusterEnergy[0] = new TH1F("clusterEnergy_signal","cluster energy of signal", 25,0,250);
    //}

    //secondary neutron{ 
    hist_leverarm[1] = new TH1F("leverarm_secondary_neutron","lever arm of secondary_neutron",20,0,200);
    hist_angle[1] = new TH1F("angle_secondary_neutron","angle between C and secondary_neutron hit",20,0,1);
    hist_beta[1] = new TH1F("beta_secondary_neutron","beta of secondary_neutron",30,0,1.5);
    hist_distance[1] = new TH1F("distance_secondary_neutron","distance b/w C and secondary_neutron hit",20,0,200);
    hist_TOF[1] = new TH1F("TOF_secondary_neutron","time of flight of secondary_neutron", 25,0,25);
    hist_CubeE[1] = new TH1F("CubeE_secondary_neutron", "CubeE of secondary_neutron", 30, 0, 15);
    hist_nCubeDis[1] = new TH1F("nCubeDis_secondary_neutron","number of cubes, secondary neutron", 50, 0, 100);
    hist_betaSmear[1] = new TH1F("betaSmear_secondary_neutron","beta of secondary_neutron smearT",30,0,1.5);
    hist_TOFSmear[1] = new TH1F("TOFSmear_secondary_neutron","time of flight of secondary_neutron smearT", 25,0,25);
    hist_clusterEnergy[1] = new TH1F("clusterEnergy_secondary_neutron","cluster energy of secondary_neutron", 25,0,250);
    //}

    //gamma{
    hist_leverarm[2] = new TH1F("leverarm_primary_gamma","lever arm of primary_gamma",20,0,200);
    hist_angle[2] = new TH1F("angle_primary_gamma","angle between C and primary_gamma hit",20,0,1);
    hist_beta[2] = new TH1F("beta_primary_gamma","beta of primary_gamma",30,0,1.5);
    hist_distance[2] = new TH1F("distance_primary_gamma","distance b/w C and primary_gamma hit",20,0,200);
    hist_TOF[2] = new TH1F("TOF_primary_gamma","time of flight of primary_gamma", 25,0,25);
    hist_CubeE[2] = new TH1F("CubeE_primary_gamma", "CubeE of primary_gamma", 30, 0, 15);
    hist_nCubeDis[2] = new TH1F("nCubeDis_primary_gamma","number of cubes, primary gamma", 50, 0, 100);
    hist_betaSmear[2] = new TH1F("betaSmear_primary_gamma","beta of primary_gamma smearT",30,0,1.5);
    hist_TOFSmear[2] = new TH1F("TOFSmear_primary_gamma","time of flight of primary_gamma smearT", 25,0,25);
    hist_clusterEnergy[2] = new TH1F("clusterEnergy_primary_gamma","cluster energy of primary_gamma", 25,0,250);
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

    const double c_velocity = 29.9792458;

    cout<<"---------------------------"<<endl;

    TFile * outfile = new TFile(name_output_file.c_str(),"RECREATE");
    TTree * output_tree = new TTree("output_tree", "output_tree");

    //variable for output root file
    float leverArm; output_tree->Branch("leverArm",&leverArm, "lever arm");
    float angle; output_tree->Branch("angle",&angle, "angle between C and hit");
    float beta; output_tree->Branch("beta",&beta, "beta");
    float betaSmear; output_tree->Branch("betaSmear",&betaSmear, "betaSmear");
    float distanceCHit; output_tree->Branch("distanceCHit",&distanceCHit, "distance C and hit");
    float tof; output_tree->Branch("tof",&tof, "time of flight");
    float tofSmear; output_tree->Branch("tofSmear",&tofSmear, "smeared time of flight");
    float cubeE; output_tree->Branch("cubeE",&cubeE, "CubeE");
    float nCube; output_tree->Branch("nCube", &nCube, "nCube");
    float category; output_tree->Branch("category", &category, "category");
    float neutrinoE; output_tree->Branch("neutrinoE", &neutrinoE, "neutrinoE");
    float hitPDG; output_tree->Branch("hitPDG", &hitPDG, "hitPDG");
    float neutronE_allhits; output_tree->Branch("neutronE_allhits", &neutronE_allhits, "neutronE_allhits");
    float neutronE_deposit[1000]; output_tree->Branch("neutronE_deposit", &neutronE_deposit, "neutronE_deposit");
    float energy_deposit_in_cluster; output_tree->Branch("energy_deposit_in_cluster", &energy_deposit_in_cluster, "energy_deposit_in_cluster");
    float parentPDG; output_tree->Branch("parentPDG", &parentPDG, "parentPDG");

    //vectors I defined
    float vec_piDeath_to_hit[3];
    float vec_vtx_to_piDeath[3];

    TChain * tree = new TChain("tree");
    if(name_input_file.size() == 0)
    {
        for(int i = 1; i < 200; i++)
        {
            //TFile * f = new TFile(Form("/pnfs/dune/persistent/users/gyang/3DST/dump/standardGeo13/PROD102/RHC_%d_extendCube.root",i));
            TFile * f = new TFile(Form("/Users/gwon/Geo13/PROD102/RHC_%d.root",i));
            if(!f->IsOpen())
                continue;
            if(!f->GetListOfKeys()->Contains("tree"))
                continue;
            tree->Add(Form("/Users/gwon/Geo13/PROD102/RHC_%d.root",i));
            delete f;
        }
    }
    else
    {
        tree->Add(name_input_file.c_str());
    }

    //SetBranchAddress
    float t_vtx[3]; tree->SetBranchAddress("vtx",&t_vtx);
    float t_piDeath[4]; tree->SetBranchAddress("piDeath",&t_piDeath);
    float t_protonDeath[3]; tree->SetBranchAddress("protonDeath",&t_protonDeath);
    int t_nFS; tree->SetBranchAddress("nFS",&t_nFS);
    int t_fsPdg[1000]; tree->SetBranchAddress("fsPdg",&t_fsPdg);
    float t_fsPx[1000]; tree->SetBranchAddress("fsPx",&t_fsPx);
    float t_fsPy[1000]; tree->SetBranchAddress("fsPy",&t_fsPy);
    float t_fsPz[1000]; tree->SetBranchAddress("fsPz",&t_fsPz);
    float t_fsE[1000]; tree->SetBranchAddress("fsE",&t_fsE);
    float t_neutronHitX[1000]; tree->SetBranchAddress("neutronHitX",&t_neutronHitX);
    float t_neutronHitY[1000]; tree->SetBranchAddress("neutronHitY",&t_neutronHitY);
    float t_neutronHitZ[1000]; tree->SetBranchAddress("neutronHitZ",&t_neutronHitZ);
    float t_neutronHitT[1000]; tree->SetBranchAddress("neutronHitT",&t_neutronHitT);
    float t_neutronHitSmearT[1000]; tree->SetBranchAddress("neutronHitSmearT",&t_neutronHitSmearT);
    float t_neutronHitE[1000]; tree->SetBranchAddress("neutronHitE",&t_neutronHitE);
    float t_neutronCubeE[1000]; tree->SetBranchAddress("neutronCubeE",&t_neutronCubeE);
    float t_neutronRecoE[1000]; tree->SetBranchAddress("neutronRecoE",&t_neutronRecoE);
    float t_neutronHitPDG[1000]; tree->SetBranchAddress("neutronHitPDG",&t_neutronHitPDG);
    float t_neutronTrueE[1000]; tree->SetBranchAddress("neutronTrueE",&t_neutronTrueE);
    float t_neutronParentId[1000]; tree->SetBranchAddress("neutronParentId",&t_neutronParentId);
    float t_neutronParentPDG[1000]; tree->SetBranchAddress("neutronParentPDG",&t_neutronParentPDG);
    float t_neutronStartingPointX[1000]; tree->SetBranchAddress("neutronStartingPointX",&t_neutronStartingPointX);
    float t_neutronStartingPointY[1000]; tree->SetBranchAddress("neutronStartingPointY",&t_neutronStartingPointY);
    float t_neutronStartingPointZ[1000]; tree->SetBranchAddress("neutronStartingPointZ",&t_neutronStartingPointZ);
    float t_neutronStartingPointT[1000]; tree->SetBranchAddress("neutronStartingPointT",&t_neutronStartingPointT);
    float t_gammaHitX[1000]; tree->SetBranchAddress("gammaHitX",&t_gammaHitX);
    float t_gammaHitY[1000]; tree->SetBranchAddress("gammaHitY",&t_gammaHitY);
    float t_gammaHitZ[1000]; tree->SetBranchAddress("gammaHitZ",&t_gammaHitZ);
    float t_gammaHitT[1000]; tree->SetBranchAddress("gammaHitT",&t_gammaHitT);
    float t_gammaHitSmearT[1000]; tree->SetBranchAddress("gammaHitSmearT",&t_gammaHitSmearT);
    float t_gammaHitE[1000]; tree->SetBranchAddress("gammaHitE",&t_gammaHitE);
    float t_gammaCubeE[1000]; tree->SetBranchAddress("gammaCubeE",&t_gammaCubeE);
    float t_gammaRecoE[1000]; tree->SetBranchAddress("gammaRecoE",&t_gammaRecoE);
    float t_gammaHitPDG[1000]; tree->SetBranchAddress("gammaHitPDG",&t_gammaHitPDG);
    float t_gammaTrueE[1000]; tree->SetBranchAddress("gammaTrueE",&t_gammaTrueE);
    float t_gammaParentId[1000]; tree->SetBranchAddress("gammaParentId",&t_gammaParentId);
    float t_gammaParentPDG[1000]; tree->SetBranchAddress("gammaParentPDG",&t_gammaParentPDG);
    float t_gammaStartingPointX[1000]; tree->SetBranchAddress("gammaStartingPointX",&t_gammaStartingPointX);
    float t_gammaStartingPointY[1000]; tree->SetBranchAddress("gammaStartingPointY",&t_gammaStartingPointY);
    float t_gammaStartingPointZ[1000]; tree->SetBranchAddress("gammaStartingPointZ",&t_gammaStartingPointZ);
    float t_gammaStartingPointT[1000]; tree->SetBranchAddress("gammaStartingPointT",&t_gammaStartingPointT);
    float t_vtxTime; tree->SetBranchAddress("vtxTime",&t_vtxTime);
    float t_vtxTimeSmear; tree->SetBranchAddress("vtxTimeSmear",&t_vtxTimeSmear);
    float t_hitLocationX[1000]; tree->SetBranchAddress("hitLocationX",&t_hitLocationX);
    float t_hitLocationY[1000]; tree->SetBranchAddress("hitLocationY",&t_hitLocationY);
    float t_hitLocationZ[1000]; tree->SetBranchAddress("hitLocationZ",&t_hitLocationZ);
    float t_hitE[1000]; tree->SetBranchAddress("hitE",&t_hitE);
    float t_hitT[1000]; tree->SetBranchAddress("hitT",&t_hitT);
    //float t_nuEnergy; tree->SetBranchAddress("nuEnergy",&t_nuEnergy);


    cout<<boolalpha;
    cout<<"---------------------------"<<endl;
    cout<<"Options"<<endl;
    if(name_input_file.size() != 0)
        cout<<"|-input file      : "<<name_input_file<<endl;
    cout<<"|-Output file     : "<<name_output_file<<endl;
    cout<<"|-Threshold       : "<<energyHitCut<<"MeV"<<endl;
    cout<<"|-ExtendCube      : "<<(bool)IsExtendCube<<endl;
    cout<<"|-Event display   : "<<(bool)event_display<<endl;
    cout<<"|-Include gamma   : "<<(bool)include_gammaHit<<endl;
    cout<<"|-Include neutron : "<<(bool)include_neutronHit<<endl;
    cout<<"|-Number of pion  : "<<numPionRequire<<endl;
    cout<<"|-Use "<<event_ratio_for_use<<"\% of entry"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"Geometry"<<endl;
    cout<<"|-center of 3DST  : "<<_3DST_centerX<<", "<<_3DST_centerY<<", "<<_3DST_centerZ<<endl;
    cout<<"|-size of 3DST    : "<<_3DSTx<<", "<<_3DSTy<<", "<<_3DSTz<<endl;
    cout<<"|-Fiducial Volume : "<<FV_x<<", "<<FV_y<<", "<<FV_z<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"run? (Y/N)";
    string run;
    cin>>run;
    if(run != "Y")
        return 0;
    cout<<"---------------------------"<<endl;
    cout<<"file loading..."<<endl;
    cout<<"\033[1000Dtotal entries: "<<tree->GetEntries()*event_ratio_for_use/100<<endl;
    cout<<"event loop starts"<<endl;
    cout<<endl;

    int nevent = tree->GetEntries()*event_ratio_for_use/100;
    for(int event = 0; event < nevent; event++)
    {
        cout<<"\033[1Aevent: "<<((double)event*100/nevent)<<"%          \033[1000D"<<endl;
        tree->GetEntry(event);
        //out of fiducial volume
        if(t_vtx[0] < _3DST_centerX-FV_x/2 || t_vtx[0] > _3DST_centerX+FV_x/2)
            continue;
        if(t_vtx[1] < _3DST_centerY-FV_y/2 || t_vtx[1] > _3DST_centerY+FV_y/2)
            continue;
        if(t_vtx[2] < _3DST_centerZ-FV_z/2 || t_vtx[2] > _3DST_centerZ+FV_z/2)
            continue;

        leverArm = -1000;
        angle = -1000;
        beta = -1000;
        betaSmear = -1000;
        distanceCHit = -1000;
        tof = -1000;
        tofSmear = -1000;
        cubeE = -1000;
        nCube = -1000;
        category = -1000;
        neutrinoE = -1000;
        hitPDG = -1000;
        neutronE_allhits = 0;
        energy_deposit_in_cluster = 0;
        parentPDG = -1000;

        int num_pi = 0;
        int num_pi0 = 0;
        int num_proton = 0;
        int num_neutron = 0;
        int num_muon = 0;

        for(int inFS = 0; inFS < t_nFS; inFS++)
        {
            if(t_fsPdg[inFS] == -13)    //pion0PDG=111
            {
                num_muon++;
            }
            if(abs(t_fsPdg[inFS]) == 111)    //pion0PDG=111
            {
                num_pi0++;
            }
            if(t_fsPdg[inFS] == 2212)
            {
                num_proton++;
            }
            if(t_fsPdg[inFS] == 2112)
            {
                num_neutron++;
            }
            if(abs(t_fsPdg[inFS]) == 211)    //pionPDG=+-211
            {
                num_pi++;
            }
        }

        if(num_muon == 0)
            continue;
        if(numPionRequire < 2)
            if(num_pi != numPionRequire)
                continue;
        if(numPionRequire > 1)
            if(num_pi < 2)
                continue;
        if(num_neutron == 0)
            continue;

        std::vector<Hit> vectorHit;    //vector of all neutron+gamma hits

        //push_back satisying hits to vectorHit
        if(include_neutronHit)
        {
            Hit temp_neutron_Hit;   
            for(int n_neutronHit = 0; n_neutronHit < 1000; n_neutronHit++)
            {
                //out of 3dst
                if(t_neutronHitX[n_neutronHit] > _3DST_centerX+_3DSTx/2 || t_neutronHitX[n_neutronHit] < _3DST_centerX-_3DSTx/2)
                    continue;
                if(t_neutronHitY[n_neutronHit] > _3DST_centerY+_3DSTy/2 || t_neutronHitY[n_neutronHit] < _3DST_centerY-_3DSTy/2)
                    continue;
                if(t_neutronHitZ[n_neutronHit] > _3DST_centerZ+_3DSTz/2 || t_neutronHitZ[n_neutronHit] < _3DST_centerZ-_3DSTz/2)
                    continue;
                if(t_neutronHitX[n_neutronHit] == 0)
                    continue;
                if(t_neutronHitY[n_neutronHit] == 0)
                    continue;
                if(t_neutronHitZ[n_neutronHit] == 0)
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
                float tofSmear = t_neutronHitSmearT[n_neutronHit] - t_vtxTimeSmear - 1;

                //Fix a bug from edep-sim
                if(tof == 1)
                    tof = 0.5;

                if(tof > 0)
                {
                    temp_neutron_Hit.SetHitE(t_neutronHitE[n_neutronHit]);
                    temp_neutron_Hit.SetTOF(tof);
                    temp_neutron_Hit.SetTOFSmear(tofSmear);
                    temp_neutron_Hit.SetLeverArm(leverArm);
                    temp_neutron_Hit.SetEnergyDeposit(t_neutronHitE[n_neutronHit]);

                    temp_neutron_Hit.SetVtxX(t_vtx[0]);
                    temp_neutron_Hit.SetVtxY(t_vtx[1]);
                    temp_neutron_Hit.SetVtxZ(t_vtx[2]);

                    if(num_pi > 0)
                    {
                        temp_neutron_Hit.piDeath[0] = t_piDeath[0];
                        temp_neutron_Hit.piDeath[1] = t_piDeath[1];
                        temp_neutron_Hit.piDeath[2] = t_piDeath[2];
                    }

                    temp_neutron_Hit.SetTrueT(t_neutronHitT[n_neutronHit]);
                    temp_neutron_Hit.SetTrueE(t_neutronTrueE[n_neutronHit]);
                    temp_neutron_Hit.SetRecoE(t_neutronRecoE[n_neutronHit]);
                    temp_neutron_Hit.SetCubeE(t_neutronCubeE[n_neutronHit]);

                    temp_neutron_Hit.SetParentId(t_neutronParentId[n_neutronHit]);
                    temp_neutron_Hit.SetParentPdg(t_neutronParentPDG[n_neutronHit]);
                    temp_neutron_Hit.SetHitPDG(t_neutronHitPDG[n_neutronHit]);

                    temp_neutron_Hit.SetVtxT(t_vtxTime);
                    temp_neutron_Hit.SetT(t_neutronHitT[n_neutronHit]);
                    temp_neutron_Hit.SetTSmear(t_neutronHitSmearT[n_neutronHit]);
                    temp_neutron_Hit.SetX(t_neutronHitX[n_neutronHit]);
                    temp_neutron_Hit.SetY(t_neutronHitY[n_neutronHit]);
                    temp_neutron_Hit.SetZ(t_neutronHitZ[n_neutronHit]);
                    temp_neutron_Hit.SetParentId(t_neutronParentId[n_neutronHit]);
                    temp_neutron_Hit.SetIsNeutron(true);
                    temp_neutron_Hit.SetCubeE(t_neutronCubeE[n_neutronHit]);

                    vectorHit.push_back(temp_neutron_Hit);
                }
            }
        }

        if(include_gammaHit)
        {
            Hit temp_gamma_Hit;
            for(int n_gammaHit = 0; n_gammaHit < 1000; n_gammaHit++)
            {
                //out of 3dst
                if(t_gammaHitX[n_gammaHit] > _3DST_centerX+_3DSTx/2 || t_gammaHitX[n_gammaHit] < _3DST_centerX-_3DSTx/2)
                    continue;
                if(t_gammaHitY[n_gammaHit] > _3DST_centerY+_3DSTy/2 || t_gammaHitY[n_gammaHit] < _3DST_centerY-_3DSTy/2)
                    continue;
                if(t_gammaHitZ[n_gammaHit] > _3DST_centerZ+_3DSTz/2 || t_gammaHitZ[n_gammaHit] < _3DST_centerZ-_3DSTz/2)
                    continue;
                if(t_gammaHitX[n_gammaHit] == 0)
                    continue;
                if(t_gammaHitY[n_gammaHit] == 0)
                    continue;
                if(t_gammaHitZ[n_gammaHit] == 0)
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
                float tofSmear = t_gammaHitSmearT[n_gammaHit] - t_vtxTimeSmear - 1;

                //Fix a bug from edep-sim
                if(tof == 1)
                    tof = 0.5;

                if(tof > 0)
                {
                    temp_gamma_Hit.SetHitE(t_gammaHitE[n_gammaHit]);
                    temp_gamma_Hit.SetTOF(tof);
                    temp_gamma_Hit.SetTOFSmear(tofSmear);
                    temp_gamma_Hit.SetLeverArm(leverArm);
                    temp_gamma_Hit.SetEnergyDeposit(t_gammaHitE[n_gammaHit]);

                    temp_gamma_Hit.SetVtxX(t_vtx[0]);
                    temp_gamma_Hit.SetVtxY(t_vtx[1]);
                    temp_gamma_Hit.SetVtxZ(t_vtx[2]);

                    if(num_pi > 0)
                    {
                        temp_gamma_Hit.piDeath[0] = t_piDeath[0];
                        temp_gamma_Hit.piDeath[1] = t_piDeath[1];
                        temp_gamma_Hit.piDeath[2] = t_piDeath[2];
                    }

                    temp_gamma_Hit.SetTrueT(t_gammaHitT[n_gammaHit]);
                    temp_gamma_Hit.SetCubeE(t_gammaCubeE[n_gammaHit]);

                    temp_gamma_Hit.SetParentId(t_gammaParentId[n_gammaHit]);
                    temp_gamma_Hit.SetParentPdg(t_gammaParentPDG[n_gammaHit]);
                    temp_gamma_Hit.SetHitPDG(t_gammaHitPDG[n_gammaHit]);

                    temp_gamma_Hit.SetVtxT(t_vtxTime);
                    temp_gamma_Hit.SetT(t_gammaHitT[n_gammaHit]);
                    temp_gamma_Hit.SetTSmear(t_gammaHitSmearT[n_gammaHit]);
                    temp_gamma_Hit.SetX(t_gammaHitX[n_gammaHit]);
                    temp_gamma_Hit.SetY(t_gammaHitY[n_gammaHit]);
                    temp_gamma_Hit.SetZ(t_gammaHitZ[n_gammaHit]);
                    temp_gamma_Hit.SetParentId(t_gammaParentId[n_gammaHit]);
                    temp_gamma_Hit.SetIsGamma(true);
                    temp_gamma_Hit.SetCubeE(t_gammaCubeE[n_gammaHit]);

                    vectorHit.push_back(temp_gamma_Hit);
                }
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

        //map<position,pair<true,time>>
        std::map<std::tuple<float,float,float>,std::pair<int,float>> cube_fired;
        //e deposit in cluster
        std::map<std::tuple<float,float,float>,std::pair<int,float>> cube_fired_e_deposit;

        for(auto t:vectorHit)
        {
            //cout<<"x,y,z: "<<t.GetX()<<", "<<t.GetY()<<", "<<t.GetZ()<<endl;
            if(event_display)
            {
                XYPlane_allhits->Fill(t.GetX(),t.GetY());
                YZPlane_allhits->Fill(t.GetY(),t.GetZ());
                XZPlane_allhits->Fill(t.GetX(),t.GetZ());
            }
            std::tuple<float, float, float> temp_position = std::make_tuple(t.GetX(),t.GetY(),t.GetZ());
            cube_fired.insert(make_pair(temp_position,make_pair(1,t.GetT())));  
            cube_fired_e_deposit.insert(make_pair(temp_position,make_pair(1,t.GetCubeE())));  
        }

        //cube cluster vector
        std::vector<Hit> cube_cluster;

        //push back the first hit
        cube_cluster.push_back(vectorHit.at(0));
        energy_deposit_in_cluster += vectorHit.at(0).GetCubeE();

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
                int N = 2;      //adjacent cube range(%d cube)
                int number_of_direction_array = 0;
                std::tuple<float, float, float> direction[(2*N+1)*(2*N+1)*(2*N+1)];
                for(int x = -N; x < N+1; x++)
                {
                    for(int y = -N; y < N+1; y++)
                    {
                        for(int z = -N; z < N+1; z++)
                        {
                            if(IsExtendCube)
                                direction[number_of_direction_array] = std::make_tuple(t.GetX()+1.5*x,t.GetY()+1.5*y,t.GetZ()+1.5*z);       //+- cube size * dimension
                            else
                                direction[number_of_direction_array] = std::make_tuple(t.GetX()+1*x,t.GetY()+1*y,t.GetZ()+1*z);       //+- cube size * dimension
                            number_of_direction_array++;
                        }
                    }
                }

                for(int i = 0; i < (2*N+1)*(2*N+1)*(2*N+1); i++)
                {
                    if(cube_fired.find(direction[i])->second.first == 1 && abs(t.GetT()-cube_fired.find(direction[i])->second.second) < 1)
                    {
                        energy_deposit_in_cluster += cube_fired_e_deposit.find(direction[i])->second.second;
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

        //select earliest hit 
        Hit earliest_hit;
        earliest_hit = vectorHit.at(0);

        if(earliest_hit.IsNeutron())
        {
            if(earliest_hit.GetParentId() == -1)
            {
                earliest_hit.SetCategory(0);
            }
            if(earliest_hit.GetParentId() > 0)
                earliest_hit.SetCategory(1);
        }
        if(earliest_hit.IsGamma())
        {
            earliest_hit.SetCategory(2);
        }


        if(earliest_hit.GetCategory() == -1000)
            continue;
        if(earliest_hit.GetHitPDG() > 10000)
            continue;

        //event display
        if(event_display)
        {
            for(auto t:cube_cluster)
            {
                cube_XYPlane->Fill(t.GetX(),t.GetY());
                cube_XZPlane->Fill(t.GetX(),t.GetZ());
                cube_YZPlane->Fill(t.GetY(),t.GetZ());
            }

            gStyle->SetFrameFillColor(1);
            if(XYPlane_allhits->GetEntries() != 0)
            {
                TCanvas * can1 = new TCanvas();
                can1->Divide(3,2);
                can1->cd(1);
                XYPlane_allhits->SetStats(0);
                XYPlane_allhits->Draw("colz");
                can1->cd(2);
                XZPlane_allhits->SetStats(0);
                XZPlane_allhits->Draw("colz");
                can1->cd(3);
                YZPlane_allhits->SetStats(0);
                YZPlane_allhits->Draw("colz");

                can1->cd(4);
                cube_XYPlane->SetStats(0);
                cube_XYPlane->Draw("colz");
                can1->cd(5);
                cube_XZPlane->SetStats(0);
                cube_XZPlane->Draw("colz");
                can1->cd(6);
                cube_YZPlane->SetStats(0);
                cube_YZPlane->Draw("colz");
                can1->SaveAs(Form("cube_eventview_%f_%d.pdf",earliest_hit.GetCategory(),event));
                can1->Clear();
            }
            XYPlane_allhits->Reset();
            XZPlane_allhits->Reset();
            YZPlane_allhits->Reset();
            cube_XYPlane->Reset();
            cube_XZPlane->Reset();
            cube_YZPlane->Reset();
        }

        parentPDG = earliest_hit.GetParentPdg();
        //cout<<"parentPDG: "<<parentPDG<<endl;

        for(int i = 0; i < 3; i++)      //i: x,y,z
        {
            if(i == 0)
            {
                vec_piDeath_to_hit[i] = earliest_hit.GetX()-earliest_hit.piDeath[i];
                vec_vtx_to_piDeath[i] = earliest_hit.piDeath[i]-earliest_hit.GetVtxX();
            }
            if(i == 1)
            {
                vec_piDeath_to_hit[i] = earliest_hit.GetY()-earliest_hit.piDeath[i];
                vec_vtx_to_piDeath[i] = earliest_hit.piDeath[i]-earliest_hit.GetVtxY();
            }
            if(i == 2)
            {
                vec_piDeath_to_hit[i] = earliest_hit.GetZ()-earliest_hit.piDeath[i];
                vec_vtx_to_piDeath[i] = earliest_hit.piDeath[i]-earliest_hit.GetVtxZ();
            }
        }

        float vec_vtx_to_hit[3];
        vec_vtx_to_hit[0] = earliest_hit.GetX() - earliest_hit.GetVtxX();
        vec_vtx_to_hit[1] = earliest_hit.GetY() - earliest_hit.GetVtxY();
        vec_vtx_to_hit[2] = earliest_hit.GetZ() - earliest_hit.GetVtxZ();

        for(int i = 0; i < 3; i++)
        {
            leverArm = earliest_hit.GetLeverArm();
            beta = (earliest_hit.GetLeverArm()/earliest_hit.GetTOF())/c_velocity;
            tof = earliest_hit.GetTOF();
            betaSmear = (earliest_hit.GetLeverArm()/earliest_hit.GetTOFSmear())/c_velocity;
            tofSmear = earliest_hit.GetTOFSmear();
            cubeE = earliest_hit.GetCubeE();
            nCube = cube_cluster.size();
            hitPDG = earliest_hit.GetHitPDG();

            if(earliest_hit.GetCategory() == i)
            {
                hist_leverarm[i]->Fill(earliest_hit.GetLeverArm());
                hist_beta[i]->Fill((earliest_hit.GetLeverArm()/earliest_hit.GetTOF())/c_velocity);
                hist_TOF[i]->Fill(earliest_hit.GetTOF());
                hist_betaSmear[i]->Fill((earliest_hit.GetLeverArm()/earliest_hit.GetTOFSmear())/c_velocity);
                hist_TOFSmear[i]->Fill(earliest_hit.GetTOFSmear());
                hist_CubeE[i]->Fill(earliest_hit.GetCubeE());
                hist_nCubeDis[i]->Fill(cube_cluster.size());
                hist_clusterEnergy[i]->Fill(energy_deposit_in_cluster);
            }

            if(num_pi > 0)
            {
                if(earliest_hit.GetCategory() == i)
                {
                    hist_angle[i]->Fill(GetAngle(vec_vtx_to_piDeath,vec_piDeath_to_hit));
                    hist_distance[i]->Fill(GetDistance(earliest_hit.piDeath,earliest_hit));
                }
                angle = GetAngle(vec_vtx_to_piDeath,vec_piDeath_to_hit);
                distanceCHit = GetDistance(earliest_hit.piDeath,earliest_hit);
            }
            else
            {
                angle = -1000;
                distanceCHit = -1000;
            }

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
        //neutrinoE = t_nuEnergy;
        //Q2 = 4*neutrinoE*muonE*0.001*pow(TMath::Sin(TMath::Pi()*muonAngle/2),2);
        category = earliest_hit.GetCategory();
        output_tree->Fill();
    }//end of event iterate

    outfile->Write();
    outfile->Close();

    cout<<"making output files... ";

    TFile * fi1 = new TFile("background.root","RECREATE");
    gStyle->SetFrameFillColor(0);

    Font_t ft = 132;
    gStyle->SetLabelSize(50,"XY");
    gStyle->SetTitleSize(50,"XY");
    //gStyle->SetLegendSize(5);

    TCanvas * can = new TCanvas;

    TLegend * legend = new TLegend(0.5,0.6,0.9,0.9);
    legend->SetHeader("DUNE: Simulation","C");
    legend->AddEntry(hist_leverarm[0],"signal","l");
    legend->AddEntry(hist_leverarm[1],"secondary neutron","l");
    legend->AddEntry(hist_leverarm[2],"gamma","l");
    legend->SetTextSize(0.055);

    TLegend * legend1 = new TLegend(0.1,0.6,0.5,0.9);
    legend1->SetHeader("DUNE: Simulation","C");
    legend1->AddEntry(hist_leverarm[0],"signal","l");
    legend1->AddEntry(hist_leverarm[1],"secondary neutron","l");
    legend1->AddEntry(hist_leverarm[2],"gamma","l");
    legend1->SetTextSize(0.055);

    /*
     * 2: red, signal
     * 4: blue, secondary neutron
     * 6: purple, gamma
     */

    //leaverarm{
    hist_leverarm[0]->GetXaxis()->SetTitle("[cm]");
    hist_leverarm[0]->GetYaxis()->SetTitle("Normalized fraction");
    hist_leverarm[0]->GetYaxis()->CenterTitle(1);
    hist_leverarm[0]->GetXaxis()->SetLabelSize(0.045);
    hist_leverarm[0]->GetYaxis()->SetLabelSize(0.045);
    hist_leverarm[0]->GetXaxis()->SetTitleSize(0.060);
    hist_leverarm[0]->GetYaxis()->SetTitleSize(0.055);
    hist_leverarm[0]->GetYaxis()->SetTitleOffset(0.9);
    hist_leverarm[0]->GetXaxis()->SetTitleOffset(0.70);
    hist_leverarm[0]->GetXaxis()->SetTitle("cm");
    hist_leverarm[0]->SetTitle("lever arm");

    for(int i = 0; i < 3; i++)
    {
        hist_leverarm[i]->Write();
        hist_leverarm[i]->SetLineColor(2*i+2);
        hist_leverarm[i]->SetLineWidth(3);
        hist_leverarm[i]->SetStats(0);
        hist_leverarm[i]->Scale(1/hist_leverarm[i]->Integral(),"nosw2");
        hist_leverarm[i]->GetYaxis()->SetRangeUser(0,1);
        if(i == 0)
            hist_leverarm[i]->Draw();
        else
            hist_leverarm[i]->Draw("same");

    }

    legend->Draw();
    can->SaveAs("leverarm.pdf");
    can->SaveAs("leverarm.C");
    can->Clear();
    //}

    //angle{
    hist_angle[0]->GetXaxis()->SetTitle("[π]");
    hist_angle[0]->GetYaxis()->SetTitle("Normalized fraction");
    hist_angle[0]->GetYaxis()->CenterTitle(1);
    hist_angle[0]->GetXaxis()->SetLabelSize(0.045);
    hist_angle[0]->GetYaxis()->SetLabelSize(0.045);
    hist_angle[0]->GetXaxis()->SetTitleSize(0.060);
    hist_angle[0]->GetYaxis()->SetTitleSize(0.055);
    hist_angle[0]->GetYaxis()->SetTitleOffset(0.9);
    hist_angle[0]->GetXaxis()->SetTitleOffset(0.70);
    hist_angle[0]->GetXaxis()->SetTitle("pi");
    hist_angle[0]->SetTitle("angle");

    for(int i = 0; i < 3; i++)
    {
        hist_angle[i]->Write();
        hist_angle[i]->SetLineColor(2*i+2);
        hist_angle[i]->SetLineWidth(3);
        hist_angle[i]->SetStats(0);
        hist_angle[i]->Scale(1/hist_angle[i]->Integral(),"nosw2");
        hist_angle[i]->GetYaxis()->SetRangeUser(0,1);
        if(i == 0)
            hist_angle[i]->Draw();
        else
            hist_angle[i]->Draw("same");
    }

    legend1->Draw();
    can->SaveAs("angle.pdf");
    can->SaveAs("angle.C");
    can->Clear();
    //}

    //beta{
    hist_beta[0]->GetXaxis()->SetTitle("speed of particle/c");
    hist_beta[0]->GetYaxis()->SetTitle("Normalized fraction");
    hist_beta[0]->GetYaxis()->CenterTitle(1);
    hist_beta[0]->GetXaxis()->SetLabelSize(0.045);
    hist_beta[0]->GetYaxis()->SetLabelSize(0.045);
    hist_beta[0]->GetXaxis()->SetTitleSize(0.060);
    hist_beta[0]->GetYaxis()->SetTitleSize(0.055);
    hist_beta[0]->GetYaxis()->SetTitleOffset(0.9);
    hist_beta[0]->GetXaxis()->SetTitleOffset(0.70);
    hist_beta[0]->GetXaxis()->SetTitle("speed of particle/c");
    hist_beta[0]->SetTitle("beta");

    for(int i = 0; i < 0; i++)
    {
        hist_beta[i]->Write();
        hist_beta[i]->SetLineColor(2*i+2);
        hist_beta[i]->SetLineWidth(3);
        hist_beta[i]->SetStats(0);
        hist_beta[i]->Scale(1/hist_beta[i]->Integral(),"nosw2");
        hist_beta[i]->GetYaxis()->SetRangeUser(0,1);
        if(i == 0)
            hist_beta[i]->Draw();
        else
            hist_beta[i]->Draw("same");
    }

    legend1->Draw();
    can->SaveAs("beta.pdf");
    can->SaveAs("beta.C");
    can->Clear();
    //}

    //betaSmear{
    hist_betaSmear[0]->GetXaxis()->SetTitle("speed of particle/c");
    hist_betaSmear[0]->GetYaxis()->SetTitle("Normalized fraction");
    hist_betaSmear[0]->GetYaxis()->CenterTitle(1);
    hist_betaSmear[0]->GetXaxis()->SetLabelSize(0.045);
    hist_betaSmear[0]->GetYaxis()->SetLabelSize(0.045);
    hist_betaSmear[0]->GetXaxis()->SetTitleSize(0.060);
    hist_betaSmear[0]->GetYaxis()->SetTitleSize(0.055);
    hist_betaSmear[0]->GetYaxis()->SetTitleOffset(0.9);
    hist_betaSmear[0]->GetXaxis()->SetTitleOffset(0.70);
    hist_betaSmear[0]->GetXaxis()->SetTitle("speed of particle/c");
    hist_betaSmear[0]->SetTitle("betaSmear");

    for(int i = 0; i < 3; i++)
    {
        hist_betaSmear[i]->Write();
        hist_betaSmear[i]->SetLineColor(2*i+2);
        hist_betaSmear[i]->SetLineWidth(3);
        hist_betaSmear[i]->SetStats(0);
        hist_betaSmear[i]->Scale(1/hist_betaSmear[i]->Integral(),"nosw2");
        hist_betaSmear[i]->GetYaxis()->SetRangeUser(0,1);
        if(i == 0)
            hist_betaSmear[i]->Draw();
        else
            hist_betaSmear[i]->Draw("same");
    }

    legend1->Draw();
    can->SaveAs("betaSmear.pdf");
    can->SaveAs("betaSmear.C");
    can->Clear();
    //}

    //distance{
    hist_distance[0]->GetXaxis()->SetTitle("[cm]");
    hist_distance[0]->GetYaxis()->SetTitle("Normalized fraction");
    hist_distance[0]->GetYaxis()->CenterTitle(1);
    hist_distance[0]->GetXaxis()->SetLabelSize(0.045);
    hist_distance[0]->GetYaxis()->SetLabelSize(0.045);
    hist_distance[0]->GetXaxis()->SetTitleSize(0.060);
    hist_distance[0]->GetYaxis()->SetTitleSize(0.055);
    hist_distance[0]->GetYaxis()->SetTitleOffset(0.9);
    hist_distance[0]->GetXaxis()->SetTitleOffset(0.70);
    hist_distance[0]->GetXaxis()->SetTitle("cm");
    hist_distance[0]->SetTitle("distance b/w C and hit");

    for(int i = 0; i < 3; i++)
    {
        hist_distance[i]->Write();
        hist_distance[i]->SetLineColor(2*i+2);
        hist_distance[i]->SetLineWidth(3);
        hist_distance[i]->SetStats(0);
        hist_distance[i]->Scale(1/hist_distance[i]->Integral(),"nosw2");
        hist_distance[i]->GetYaxis()->SetRangeUser(0,1);
        if(i == 0)
            hist_distance[i]->Draw();
        else
            hist_distance[i]->Draw("same");
    }

    legend->Draw();
    can->SaveAs("distance.pdf");
    can->SaveAs("distance.C");
    can->Clear();
    //}

    //TOF{
    hist_TOF[0]->GetXaxis()->SetTitle("[ns]");
    hist_TOF[0]->GetYaxis()->SetTitle("Normalized fraction");
    hist_TOF[0]->GetYaxis()->CenterTitle(1);
    hist_TOF[0]->GetXaxis()->SetLabelSize(0.045);
    hist_TOF[0]->GetYaxis()->SetLabelSize(0.045);
    hist_TOF[0]->GetXaxis()->SetTitleSize(0.060);
    hist_TOF[0]->GetYaxis()->SetTitleSize(0.055);
    hist_TOF[0]->GetYaxis()->SetTitleOffset(0.9);
    hist_TOF[0]->GetXaxis()->SetTitleOffset(0.70);
    hist_TOF[0]->GetXaxis()->SetTitle("ns");
    hist_TOF[0]->SetTitle("Time of flight");

    for(int i = 0; i < 3; i++)
    {
        hist_TOF[i]->Write();
        hist_TOF[i]->SetLineColor(2*i+2);
        hist_TOF[i]->SetLineWidth(3);
        hist_TOF[i]->SetStats(0);
        hist_TOF[i]->Scale(1/hist_TOF[i]->Integral(),"nosw2");
        hist_TOF[i]->GetYaxis()->SetRangeUser(0,1);
        if(i == 0)
            hist_TOF[i]->Draw();
        else
            hist_TOF[i]->Draw("same");
    }

    legend->Draw();
    can->SaveAs("TOF.pdf");
    can->SaveAs("TOF.C");
    can->Clear();
    //}

    //TOFSmear{
    hist_TOFSmear[0]->GetXaxis()->SetTitle("[ns]");
    hist_TOFSmear[0]->GetYaxis()->SetTitle("Normalized fraction");
    hist_TOFSmear[0]->GetYaxis()->CenterTitle(1);
    hist_TOFSmear[0]->GetXaxis()->SetLabelSize(0.045);
    hist_TOFSmear[0]->GetYaxis()->SetLabelSize(0.045);
    hist_TOFSmear[0]->GetXaxis()->SetTitleSize(0.060);
    hist_TOFSmear[0]->GetYaxis()->SetTitleSize(0.055);
    hist_TOFSmear[0]->GetYaxis()->SetTitleOffset(0.9);
    hist_TOFSmear[0]->GetXaxis()->SetTitleOffset(0.70);
    hist_TOFSmear[0]->GetXaxis()->SetTitle("ns");
    hist_TOFSmear[0]->SetTitle("Time of flight");

    for(int i = 0; i < 3; i++)
    {
        hist_TOFSmear[i]->Write();
        hist_TOFSmear[i]->SetLineColor(2*i+2);
        hist_TOFSmear[i]->SetLineWidth(3);
        hist_TOFSmear[i]->SetStats(0);
        hist_TOFSmear[i]->Scale(1/hist_TOFSmear[i]->Integral(),"nosw2");
        hist_TOFSmear[i]->GetYaxis()->SetRangeUser(0,1);
        if(i == 0)
            hist_TOFSmear[i]->Draw();
        else
            hist_TOFSmear[i]->Draw("same");
    }

    legend->Draw();
    can->SaveAs("TOFSmear.pdf");
    can->SaveAs("TOFSmear.C");
    can->Clear();
    //}

    //CubeE{
    hist_CubeE[0]->GetXaxis()->SetTitle("[MeV]");
    hist_CubeE[0]->GetYaxis()->SetTitle("Normalized fraction");
    hist_CubeE[0]->GetYaxis()->CenterTitle(1);
    hist_CubeE[0]->GetXaxis()->SetLabelSize(0.045);
    hist_CubeE[0]->GetYaxis()->SetLabelSize(0.045);
    hist_CubeE[0]->GetXaxis()->SetTitleSize(0.060);
    hist_CubeE[0]->GetYaxis()->SetTitleSize(0.055);
    hist_CubeE[0]->GetYaxis()->SetTitleOffset(0.9);
    hist_CubeE[0]->GetXaxis()->SetTitleOffset(0.70);
    hist_CubeE[0]->GetXaxis()->SetTitle("MeV");
    hist_CubeE[0]->SetTitle("CubeE");

    for(int i = 0; i < 3; i++)
    {
        hist_CubeE[i]->Write();
        hist_CubeE[i]->SetLineColor(2*i+2);
        hist_CubeE[i]->SetLineWidth(3);
        hist_CubeE[i]->SetStats(0);
        hist_CubeE[i]->Scale(1/hist_CubeE[i]->Integral(),"nosw2");
        hist_CubeE[i]->GetYaxis()->SetRangeUser(0,1);
        if(i == 0)
            hist_CubeE[i]->Draw();
        else
            hist_CubeE[i]->Draw("same");
    }

    legend->Draw();
    can->SaveAs("CubeE.pdf");
    can->SaveAs("CubeE.C");
    can->Clear();
    //}

    //nCube{
    hist_nCubeDis[0]->GetXaxis()->SetTitle("number of fired cube");
    hist_nCubeDis[0]->GetYaxis()->SetTitle("Normalized fraction");
    hist_nCubeDis[0]->GetYaxis()->CenterTitle(1);
    hist_nCubeDis[0]->GetXaxis()->SetLabelSize(0.045);
    hist_nCubeDis[0]->GetYaxis()->SetLabelSize(0.045);
    hist_nCubeDis[0]->GetXaxis()->SetTitleSize(0.060);
    hist_nCubeDis[0]->GetYaxis()->SetTitleSize(0.055);
    hist_nCubeDis[0]->GetYaxis()->SetTitleOffset(0.9);
    hist_nCubeDis[0]->GetXaxis()->SetTitleOffset(0.70);
    hist_nCubeDis[0]->GetXaxis()->SetTitle("number of fired cubes");
    hist_nCubeDis[0]->SetTitle("number of cube");

    for(int i = 0; i < 3; i++)
    {
        hist_nCubeDis[i]->Write();
        hist_nCubeDis[i]->SetLineColor(2*i+2);
        hist_nCubeDis[i]->SetLineWidth(3);
        hist_nCubeDis[i]->SetStats(0);
        hist_nCubeDis[i]->Scale(1/hist_nCubeDis[i]->Integral(),"nosw2");
        hist_nCubeDis[i]->GetYaxis()->SetRangeUser(0,1);
        if(i == 0)
            hist_nCubeDis[i]->Draw();
        else
            hist_nCubeDis[i]->Draw("same");
    }

    legend->Draw();
    can->SaveAs("nCubeDis.pdf");
    can->SaveAs("nCubeDis.C");
    can->Clear();
    //}

    //clusterEnergy{
    hist_clusterEnergy[0]->GetXaxis()->SetTitle("cluster energy");
    hist_clusterEnergy[0]->GetYaxis()->SetTitle("Normalized fraction");
    hist_clusterEnergy[0]->GetYaxis()->CenterTitle(1);
    hist_clusterEnergy[0]->GetXaxis()->SetLabelSize(0.045);
    hist_clusterEnergy[0]->GetYaxis()->SetLabelSize(0.045);
    hist_clusterEnergy[0]->GetXaxis()->SetTitleSize(0.060);
    hist_clusterEnergy[0]->GetYaxis()->SetTitleSize(0.055);
    hist_clusterEnergy[0]->GetYaxis()->SetTitleOffset(0.9);
    hist_clusterEnergy[0]->GetXaxis()->SetTitleOffset(0.70);
    hist_clusterEnergy[0]->GetXaxis()->SetTitle("cluster energy [MeV]");
    hist_clusterEnergy[0]->SetTitle("cluster energy");

    for(int i = 0; i < 3; i++)
    {
        hist_clusterEnergy[i]->Write();
        hist_clusterEnergy[i]->SetLineColor(2*i+2);
        hist_clusterEnergy[i]->SetLineWidth(3);
        hist_clusterEnergy[i]->SetStats(0);
        hist_clusterEnergy[i]->Scale(1/hist_clusterEnergy[i]->Integral(),"nosw2");
        hist_clusterEnergy[i]->GetYaxis()->SetRangeUser(0,1);
        if(i == 0)
            hist_clusterEnergy[i]->Draw();
        else
            hist_clusterEnergy[i]->Draw("same");
    }

    legend->Draw();
    can->SaveAs("clusterEnergy.pdf");
    can->SaveAs("test/clusterEnergy.C");
    can->Clear();
    //}

    fi1->Close();

    cout<<"done"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"exit"<<endl;

    return 0;
}
