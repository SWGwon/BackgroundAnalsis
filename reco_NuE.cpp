void reco_NuE()
{
    TH1F * reco_NuE = new TH1F("","reco NuE without neutron",100,0,3000);
    TH1F * reco_NuE_w_neutron = new TH1F("","reco NuE with neutron",100,0,4000);
    TFile * file = new TFile("/output/variables.root");
    TTree * tree = (TTree*)file->Get("output_tree");

    float t_muonMomentum; tree->SetBranchAddress("muonMomentum",&t_muonMomentum);
    float t_category; tree->SetBranchAddress("category",&t_category);
    float t_neutonE; tree->SetBranchAddress("neutronE",&t_neutonE);

    float smeard_mu_momentum;
    float reco_muE;

    for(int i = 0; i < tree->GetEntries(); i++)
    {
        tree->GetEntry(i);
        if(t_category != 1)
            continue;
        smeard_mu_momentum = t_muonMomentum*(1+0.04*gRandom->Gaus(0,1));
        reco_NuE_w_neutron->Fill(smeard_mu_momentum+t_neutonE);
    }

    new TCanvas;
    reco_NuE_w_neutron->Draw();
}

