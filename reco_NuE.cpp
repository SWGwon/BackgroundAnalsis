void reco_NuE()
{
    TH1F * _0pi0P_true_NuE = new TH1F("","true NuE;MeV",100,0,6000);
    TH1F * reco_NuE = new TH1F("","reco NuE without neutron;MeV",100,0,6000);
    TH1F * reco_NuE_w_neutron_allhits = new TH1F("","reco NuE with neutron (all hits);MeV",100,0,6000);
    TH1F * reco_NuE_w_neutron = new TH1F("","reco NuE with neutron (leverarm,smeared tof);MeV",100,0,6000);

    //////////////////////////////////////////////////////////////////////////////////////
    TH2F * _0pi0P_true_reco_wo_neutron = new TH2F("","0pi0P, true vs reco without neutron;true MeV;reco MeV",100,0,6000,100,0,6000);
    TH2F * _0pi0P_true_reco_w_neutron_allhits = new TH2F("","0pi0P, true vs reco with neutron(all hits);true MeV;reco MeV",100,0,6000,100,0,6000);
    TH2F * _0pi0P_true_reco_w_neutron_levertof = new TH2F("","0pi0P, true vs reco with neutron(leverarm,smeared tof);true MeV;reco MeV",100,0,6000,100,0,6000);

    //////////////////////////////////////////////////////////////////////////////////////
    TH2F * _1pi0P_true_reco_wo_neutron = new TH2F("","1pi0P, true vs reco without neutron;true MeV;reco MeV",100,0,6000,100,0,6000);
    TH2F * _1pi0P_true_reco_w_neutron_allhits = new TH2F("","1pi0P, true vs reco with neutron(all hits);true MeV;reco MeV",100,0,6000,100,0,6000);
    TH2F * _1pi0P_true_reco_w_neutron_levertof = new TH2F("","1pi0P, true vs reco with neutron(leverarm,smeared tof);true MeV;reco MeV",100,0,6000,100,0,6000);

    //////////////////////////////////////////////////////////////////////////////////////
    TH2F * _0pi1P_true_reco_wo_neutron = new TH2F("","0pi1P, true vs reco without neutron;true MeV;reco MeV",100,0,6000,100,0,6000);
    TH2F * _0pi1P_true_reco_w_neutron_allhits = new TH2F("","0pi1P, true vs reco with neutron(all hits);true MeV;reco MeV",100,0,6000,100,0,6000);
    TH2F * _0pi1P_true_reco_w_neutron_levertof = new TH2F("","0pi1P, true vs reco with neutron(leverarm,smeared tof);true MeV;reco MeV",100,0,6000,100,0,6000);

    TFile * file = new TFile("./output/variables.root");
    TTree * tree = (TTree*)file->Get("output_tree");

    float t_muonMomentum; tree->SetBranchAddress("muonMomentum",&t_muonMomentum);
    float t_category; tree->SetBranchAddress("category",&t_category);
    float t_neutronE; tree->SetBranchAddress("neutronE",&t_neutronE);
    float t_neutronE_allhits; tree->SetBranchAddress("neutronE_allhits", &t_neutronE_allhits);
    float t_leverArm; tree->SetBranchAddress("leverArm", &t_leverArm);
    float t_tof; tree->SetBranchAddress("tof", &t_tof);
    float t_channel; tree->SetBranchAddress("channel", &t_channel);
    float t_nuE; tree->SetBranchAddress("neutrinoE", &t_nuE);
    float t_pionMomentum; tree->SetBranchAddress("pionMomentum", &t_pionMomentum);
    float t_protonMomentum; tree->SetBranchAddress("protonMomentum", &t_protonMomentum);

    float smeard_mu_momentum;
    float smeard_pion_momentum;
    float smeard_proton_momentum;
    float reco_muE;
    float reco_protonE;
    float reco_neutronE;    //leverarm, tof
    float neutron_m = 1.674*pow(10,-27);    //kg

    TH1F * _0pi0P_resolution_wo_neutron = new TH1F("","0pi0P, without neutron;(true-reco)/true",1000,-3,3);
    TH1F * _0pi0P_resolution_w_neutron_allhits = new TH1F("","0pi0P, with neutron allhits;(true-reco)/true",1000,-3,3);
    TH1F * _0pi0P_resolution_w_neutron_levertof = new TH1F("","0pi0P, with reco neutron(leverarm,smeared tof);(true-reco)/true",1000,-3,3);

    TH1F * _1pi0P_resolution_wo_neutron = new TH1F("","1pi0P, without neutron;(true-reco)/true",1000,-3,3);
    TH1F * _1pi0P_resolution_w_neutron_allhits = new TH1F("","1pi0P, with neutron allhits;(true-reco)/true",1000,-3,3);
    TH1F * _1pi0P_resolution_w_neutron_levertof = new TH1F("","1pi0P, with reco neutron(leverarm,smeared tof);(true-reco)/true",1000,-3,3);

    TH1F * _0pi1P_resolution_wo_neutron = new TH1F("","0pi1P, without neutron;(true-reco)/true",1000,-3,3);
    TH1F * _0pi1P_resolution_w_neutron_allhits = new TH1F("","0pi1P, with neutron allhits;(true-reco)/true",1000,-3,3);
    TH1F * _0pi1P_resolution_w_neutron_levertof = new TH1F("","0pi1P, with reco neutron(leverarm,smeared tof);(true-reco)/true",1000,-3,3);

    TFile * trueT_file = new TFile("./data/variables.root");
    TTree * trueT_tree = (TTree*)trueT_file->Get("output_tree");

    float trueT_muonMomentum; trueT_tree->SetBranchAddress("muonMomentum",&trueT_muonMomentum);
    float trueT_category; trueT_tree->SetBranchAddress("category",&trueT_category);
    float trueT_neutronE; trueT_tree->SetBranchAddress("neutronE",&trueT_neutronE);
    float trueT_neutronE_allhits; trueT_tree->SetBranchAddress("neutronE_allhits", &trueT_neutronE_allhits);
    float trueT_leverArm; trueT_tree->SetBranchAddress("leverArm", &trueT_leverArm);
    float trueT_tof; trueT_tree->SetBranchAddress("tof", &trueT_tof);
    float trueT_channel; trueT_tree->SetBranchAddress("channel", &trueT_channel);
    float trueT_nuE; trueT_tree->SetBranchAddress("neutrinoE", &trueT_nuE);
    float trueT_pionMomentum; trueT_tree->SetBranchAddress("pionMomentum", &trueT_pionMomentum);
    float trueT_protonMomentum; trueT_tree->SetBranchAddress("protonMomentum", &trueT_protonMomentum);

    float trueT_smeard_mu_momentum;
    float trueT_smeard_pion_momentum;
    float trueT_smeard_proton_momentum;
    float trueT_reco_muE;
    float trueT_reco_protonE;
    float trueT_reco_neutronE;    //leverarm, tof
    float trueT_neutron_m = 1.674*pow(10,-27);    //kg
    TH2F * trueT_0pi0P_true_reco_w_neutron_levertof = new TH2F("","0pi0P, true vs reco with neutron(leverarm,true tof);true MeV;reco MeV",100,0,6000,100,0,6000);
    TH2F * trueT_1pi0P_true_reco_w_neutron_levertof = new TH2F("","1pi0P, true vs reco with neutron(leverarm,true tof);true MeV;reco MeV",100,0,6000,100,0,6000);
    TH2F * trueT_0pi1P_true_reco_w_neutron_levertof = new TH2F("","0pi1P, true vs reco with neutron(leverarm,true tof);true MeV;reco MeV",100,0,6000,100,0,6000);
    TH1F * trueT_0pi0P_resolution_w_neutron_levertof = new TH1F("","0pi0P, with reco neutron(leverarm,true tof);(true-reco)/true",1000,-3,3);
    TH1F * trueT_1pi0P_resolution_w_neutron_levertof = new TH1F("","1pi0P, with reco neutron(leverarm,true tof);(true-reco)/true",1000,-3,3);
    TH1F * trueT_0pi1P_resolution_w_neutron_levertof = new TH1F("","0pi1P, with reco neutron(leverarm,true tof);(true-reco)/true",1000,-3,3);

    for(int i = 0; i < tree->GetEntries(); i++)
    {
        tree->GetEntry(i);
        if(t_category != 1)
            continue;
        reco_neutronE = 1.674/1.602*pow(t_leverArm/t_tof,2);    //MeV
        smeard_mu_momentum = t_muonMomentum*(1+0.04*gRandom->Gaus(0,1));

        if(t_channel == 0)
        {
            float reco_wo_neutron_0pi0P = smeard_mu_momentum;
            float reco_w_neutron_allhits_0pi0P = smeard_mu_momentum+t_neutronE_allhits;
            float reco_w_neutron_levertof_0pi0P = smeard_mu_momentum+reco_neutronE;
            _0pi0P_true_reco_wo_neutron->Fill(t_nuE*1000,smeard_mu_momentum);
            _0pi0P_true_reco_w_neutron_allhits->Fill(t_nuE*1000,smeard_mu_momentum+t_neutronE_allhits);
            _0pi0P_true_reco_w_neutron_levertof->Fill(t_nuE*1000,smeard_mu_momentum+reco_neutronE);
            _0pi0P_resolution_wo_neutron->Fill((t_nuE*1000-reco_wo_neutron_0pi0P)/(t_nuE*1000));
            _0pi0P_resolution_w_neutron_allhits->Fill((t_nuE*1000-reco_w_neutron_allhits_0pi0P)/(t_nuE*1000));
            _0pi0P_resolution_w_neutron_levertof->Fill((t_nuE*1000-reco_w_neutron_levertof_0pi0P)/(t_nuE*1000));
        }

        if(t_channel == 1)
        {
            float reco_wo_neutron_1pi0P = smeard_mu_momentum+smeard_pion_momentum;
            float reco_w_neutron_allhits_1pi0P = smeard_mu_momentum+t_neutronE_allhits+smeard_pion_momentum;
            float reco_w_neutron_levertof_1pi0P = smeard_mu_momentum+reco_neutronE+smeard_pion_momentum;
            smeard_pion_momentum = t_pionMomentum*(1+0.04*gRandom->Gaus(0,1));
            _1pi0P_true_reco_wo_neutron->Fill(t_nuE*1000,smeard_mu_momentum+smeard_pion_momentum);
            _1pi0P_true_reco_w_neutron_allhits->Fill(t_nuE*1000,smeard_mu_momentum+t_neutronE_allhits+smeard_pion_momentum);
            _1pi0P_true_reco_w_neutron_levertof->Fill(t_nuE*1000,smeard_mu_momentum+reco_neutronE+smeard_pion_momentum);
            _1pi0P_resolution_wo_neutron->Fill((t_nuE*1000-reco_wo_neutron_1pi0P)/(t_nuE*1000));
            _1pi0P_resolution_w_neutron_allhits->Fill((t_nuE*1000-reco_w_neutron_allhits_1pi0P)/(t_nuE*1000));
            _1pi0P_resolution_w_neutron_levertof->Fill((t_nuE*1000-reco_w_neutron_levertof_1pi0P)/(t_nuE*1000));
        }

        if(t_channel == 2)
        {
            float reco_wo_neutron_0pi1P = smeard_mu_momentum+smeard_proton_momentum;
            float reco_w_neutron_allhits_0pi1P = smeard_mu_momentum+t_neutronE_allhits+smeard_proton_momentum;
            float reco_w_neutron_levertof_0pi1P = smeard_mu_momentum+reco_neutronE+smeard_proton_momentum;
            smeard_proton_momentum = t_protonMomentum*(1+0.04*gRandom->Gaus(0,1));    //MeV
            _0pi1P_true_reco_wo_neutron->Fill(t_nuE*1000,smeard_mu_momentum+smeard_proton_momentum);
            _0pi1P_true_reco_w_neutron_allhits->Fill(t_nuE*1000,smeard_mu_momentum+t_neutronE_allhits+smeard_proton_momentum);
            _0pi1P_true_reco_w_neutron_levertof->Fill(t_nuE*1000,smeard_mu_momentum+reco_neutronE+smeard_proton_momentum);
            _0pi1P_resolution_wo_neutron->Fill((t_nuE*1000-reco_wo_neutron_0pi1P)/(t_nuE*1000));
            _0pi1P_resolution_w_neutron_allhits->Fill((t_nuE*1000-reco_w_neutron_allhits_0pi1P)/(t_nuE*1000));
            _0pi1P_resolution_w_neutron_levertof->Fill((t_nuE*1000-reco_w_neutron_levertof_0pi1P)/(t_nuE*1000));
        }
    }

    for(int i = 0; i < trueT_tree->GetEntries(); i++)
    {
        trueT_tree->GetEntry(i);
        if(trueT_category != 1)
            continue;
        trueT_reco_neutronE = 1.674/1.602*pow(trueT_leverArm/trueT_tof,2);    //MeV
        trueT_smeard_mu_momentum = trueT_muonMomentum*(1+0.04*gRandom->Gaus(0,1));

        if(trueT_channel == 0)
        {
            float trueT_reco_w_neutron_levertof_0pi0P = trueT_smeard_mu_momentum+trueT_reco_neutronE;
            trueT_0pi0P_true_reco_w_neutron_levertof->Fill(trueT_nuE*1000,trueT_smeard_mu_momentum+trueT_reco_neutronE);
            trueT_0pi0P_resolution_w_neutron_levertof->Fill((trueT_nuE*1000-trueT_reco_w_neutron_levertof_0pi0P)/(trueT_nuE*1000));
        }

        if(trueT_channel == 1)
        {
            float trueT_reco_w_neutron_levertof_1pi0P = trueT_smeard_mu_momentum+trueT_reco_neutronE+trueT_smeard_pion_momentum;
            trueT_smeard_pion_momentum = trueT_pionMomentum*(1+0.04*gRandom->Gaus(0,1));
            trueT_1pi0P_true_reco_w_neutron_levertof->Fill(trueT_nuE*1000,trueT_smeard_mu_momentum+trueT_reco_neutronE+trueT_smeard_pion_momentum);
            trueT_1pi0P_resolution_w_neutron_levertof->Fill((trueT_nuE*1000-trueT_reco_w_neutron_levertof_1pi0P)/(trueT_nuE*1000));
        }

        if(trueT_channel == 2)
        {
            float trueT_reco_w_neutron_levertof_0pi1P = trueT_smeard_mu_momentum+trueT_reco_neutronE+trueT_smeard_proton_momentum;
            trueT_smeard_proton_momentum = trueT_protonMomentum*(1+0.04*gRandom->Gaus(0,1));    //MeV
            trueT_0pi1P_true_reco_w_neutron_levertof->Fill(trueT_nuE*1000,trueT_smeard_mu_momentum+trueT_reco_neutronE+trueT_smeard_proton_momentum);
            trueT_0pi1P_resolution_w_neutron_levertof->Fill((trueT_nuE*1000-trueT_reco_w_neutron_levertof_0pi1P)/(trueT_nuE*1000));
        }
    }

    TLine * l = new TLine(0,0,6000,6000);

    TCanvas * can1 = new TCanvas;
    can1->Divide(2,2);
    can1->cd(1);
    _1pi0P_true_reco_wo_neutron->SetStats(0);
    _1pi0P_true_reco_wo_neutron->Draw("colz");
    l->Draw();
    can1->cd(2);
    _1pi0P_true_reco_w_neutron_allhits->SetStats(0);
    _1pi0P_true_reco_w_neutron_allhits->Draw("colz");
    l->Draw();
    can1->cd(3);
    _1pi0P_true_reco_w_neutron_levertof->SetStats(0);
    _1pi0P_true_reco_w_neutron_levertof->Draw("colz");
    l->Draw();
    can1->cd(4);
    trueT_1pi0P_true_reco_w_neutron_levertof->SetStats(0);
    trueT_1pi0P_true_reco_w_neutron_levertof->Draw("colz");
    l->Draw();

    TCanvas * can4 = new TCanvas;
    can4->Divide(2,2);
    can4->cd(1);
    _0pi0P_resolution_wo_neutron->Draw();
    can4->cd(2);
    _0pi0P_resolution_w_neutron_allhits->Draw();
    can4->cd(3);
    _0pi0P_resolution_w_neutron_levertof->Draw();
    can4->cd(4);
    trueT_0pi0P_resolution_w_neutron_levertof->Draw();

    TCanvas * can2 = new TCanvas;
    can2->Divide(2,2);
    can2->cd(1);
    _0pi0P_true_reco_wo_neutron->SetStats(0);
    _0pi0P_true_reco_wo_neutron->Draw("colz");
    l->Draw();
    can2->cd(2);
    _0pi0P_true_reco_w_neutron_allhits->SetStats(0);
    _0pi0P_true_reco_w_neutron_allhits->Draw("colz");
    l->Draw();
    can2->cd(3);
    _0pi0P_true_reco_w_neutron_levertof->SetStats(0);
    _0pi0P_true_reco_w_neutron_levertof->Draw("colz");
    l->Draw();
    can2->cd(4);
    trueT_0pi0P_true_reco_w_neutron_levertof->SetStats(0);
    trueT_0pi0P_true_reco_w_neutron_levertof->Draw("colz");
    l->Draw();

    TCanvas * can5 = new TCanvas;
    can5->Divide(2,2);
    can5->cd(1);
    _1pi0P_resolution_wo_neutron->Draw();
    can5->cd(2);
    _1pi0P_resolution_w_neutron_allhits->Draw();
    can5->cd(3);
    _1pi0P_resolution_w_neutron_levertof->Draw();
    can5->cd(4);
    trueT_1pi0P_resolution_w_neutron_levertof->Draw();

    TCanvas * can3 = new TCanvas;
    can3->Divide(2,2);
    can3->cd(1);
    _0pi1P_true_reco_wo_neutron->SetStats(0);
    _0pi1P_true_reco_wo_neutron->Draw("colz");
    l->Draw();
    can3->cd(2);
    _0pi1P_true_reco_w_neutron_allhits->SetStats(0);
    _0pi1P_true_reco_w_neutron_allhits->Draw("colz");
    l->Draw();
    can3->cd(3);
    _0pi1P_true_reco_w_neutron_levertof->SetStats(0);
    _0pi1P_true_reco_w_neutron_levertof->Draw("colz");
    l->Draw();
    can3->cd(4);
    trueT_0pi1P_true_reco_w_neutron_levertof->SetStats(0);
    trueT_0pi1P_true_reco_w_neutron_levertof->Draw("colz");
    l->Draw();

    TCanvas * can6 = new TCanvas;
    can6->Divide(2,2);
    can6->cd(1);
    _0pi1P_resolution_wo_neutron->Draw();
    can6->cd(2);
    _0pi1P_resolution_w_neutron_allhits->Draw();
    can6->cd(3);
    _0pi1P_resolution_w_neutron_levertof->Draw();
    can6->cd(4);
    trueT_0pi1P_resolution_w_neutron_levertof->Draw();

    TPad * p1 = (TPad*)can1->cd(1);
    p1->SetLogz();
    TPad * p2 = (TPad*)can1->cd(2);
    p2->SetLogz();
    TPad * p3 = (TPad*)can1->cd(3);
    p3->SetLogz();
    TPad * p10 = (TPad*)can1->cd(4);
    p10->SetLogz();

    TPad * p4 = (TPad*)can2->cd(1);
    p4->SetLogz();
    TPad * p5 = (TPad*)can2->cd(2);
    p5->SetLogz();
    TPad * p6 = (TPad*)can2->cd(3);
    p6->SetLogz();
    TPad * p11 = (TPad*)can2->cd(4);
    p11->SetLogz();

    TPad * p7 = (TPad*)can3->cd(2);
    p7->SetLogz();
    TPad * p8 = (TPad*)can3->cd(3);
    p8->SetLogz();
    TPad * p9 = (TPad*)can3->cd(1);
    p9->SetLogz();
    TPad * p12 = (TPad*)can3->cd(4);
    p12->SetLogz();
}

