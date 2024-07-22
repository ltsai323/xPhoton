{
    TTree *t = (TTree*)_file0->Get("t");

    Float_t jetPt, recoPt, jetSubVtxPt, jetSubVtx3DVal, jetSubVtx3DErr, jetSubVtxMass, jetDeepCSVTags_b, jetDeepCSVTags_bb, jetDeepCSVTags_c, jetDeepCSVTags_udsg, photonIDmva, jetCSV2BJetTags, chIsoRaw, mva;  
    Int_t jetSubVtxNtrks, flavour, files, isMatched, phoFiredTrgs;
    Float_t mcweight, puwei;
    Float_t LBin[15]={25,34,40,55,70,85,100,115,135,155,175,200,220,250,300};
    Float_t HBin[15]={34,40,55,70,85,100,115,135,155,175,200,220,250,300,1000};

    bool isMC = t->FindBranch("mcPt") ? true : false;

    t->SetBranchAddress("jetPt",&jetPt);
    t->SetBranchAddress("recoPt",&recoPt);
    t->SetBranchAddress("jetSubVtxPt",&jetSubVtxPt);
    t->SetBranchAddress("jetSubVtx3DVal",&jetSubVtx3DVal);
    t->SetBranchAddress("jetSubVtx3DErr",&jetSubVtx3DErr);
    t->SetBranchAddress("jetSubVtxNtrks",&jetSubVtxNtrks);
    t->SetBranchAddress("jetSubVtxMass",&jetSubVtxMass);
    t->SetBranchAddress("jetDeepCSVTags_b",&jetDeepCSVTags_b);
    t->SetBranchAddress("jetDeepCSVTags_bb",&jetDeepCSVTags_bb);
    t->SetBranchAddress("jetDeepCSVTags_c",&jetDeepCSVTags_c);
    t->SetBranchAddress("jetDeepCSVTags_udsg",&jetDeepCSVTags_udsg);
    t->SetBranchAddress("jetCSV2BJetTags",&jetCSV2BJetTags);
    t->SetBranchAddress("photonIDmva",&photonIDmva);
    t->SetBranchAddress("phoFiredTrgs",&phoFiredTrgs);
    t->SetBranchAddress("chIsoRaw",&chIsoRaw);
    t->SetBranchAddress("mva",&mva);
    t->SetBranchAddress("files",&files); // not existed in xAna
    if ( isMC )
    {
        t->SetBranchAddress("flavour",&flavour); // not existed in xAna
        t->SetBranchAddress("isMatched",&isMatched);
        t->SetBranchAddress("mcweight", &mcweight);
        t->SetBranchAddress("puwei", &puwei);
    }


    TH1F *h_jetpt_LM[20];
    TH1F *h_jetpt_LN[20];
    TH1F *h_jetpt_CM[20];
    TH1F *h_jetpt_CN[20];
    TH1F *h_jetpt_BM[20];
    TH1F *h_jetpt_BN[20];
    TH1F *h_jetpt_MC[20];

    TH1F *h_recopt_LM[20];
    TH1F *h_recopt_LN[20];
    TH1F *h_recopt_CM[20];
    TH1F *h_recopt_CN[20];
    TH1F *h_recopt_BM[20];
    TH1F *h_recopt_BN[20];
    TH1F *h_recopt_MC[20];

    TH1F *h_mva_MC[20];



    char name[30];
    char title[40]; 
    if ( isMC )
        for (Int_t i=0;i<15;i++) {

            sprintf(name,"h_jetpt_LM_%d",i+1);
            sprintf(title,"h_jetpt_LM_%d",i+1);
            h_jetpt_LM[i] = new TH1F(name,title, 30, 0., 600.);
            h_jetpt_LM[i]->Sumw2();
            sprintf(name,"h_jetpt_LN_%d",i+1);
            sprintf(title,"h_jetpt_LN_%d",i+1);
            h_jetpt_LN[i] = new TH1F(name,title, 30, 0., 600.);
            h_jetpt_LN[i]->Sumw2();

            sprintf(name,"h_jetpt_CM_%d",i+1);
            sprintf(title,"h_jetpt_CM_%d",i+1);
            h_jetpt_CM[i] = new TH1F(name,title, 30, 0., 600.);
            h_jetpt_CM[i]->Sumw2();
            sprintf(name,"h_jetpt_CN_%d",i+1);
            sprintf(title,"h_jetpt_CN_%d",i+1);
            h_jetpt_CN[i] = new TH1F(name,title, 30, 0., 600.);
            h_jetpt_CN[i]->Sumw2();

            sprintf(name,"h_jetpt_BM_%d",i+1);
            sprintf(title,"h_jetpt_BM_%d",i+1);
            h_jetpt_BM[i] = new TH1F(name,title, 30, 0., 600.);
            h_jetpt_BM[i]->Sumw2();
            sprintf(name,"h_jetpt_BN_%d",i+1);
            sprintf(title,"h_jetpt_BN_%d",i+1);
            h_jetpt_BN[i] = new TH1F(name,title, 30, 0., 600.);
            h_jetpt_BN[i]->Sumw2();

            sprintf(name,"h_jetpt_MC_%d",i+1);
            sprintf(title,"h_jetpt_MC_%d",i+1);
            h_jetpt_MC[i] = new TH1F(name,title, 30, 0., 600.);
            h_jetpt_MC[i]->Sumw2();


            sprintf(name,"h_recopt_LM_%d",i+1);
            sprintf(title,"h_recopt_LM_%d",i+1);
            h_recopt_LM[i] = new TH1F(name,title, 10, LBin[i], HBin[i]);
            h_recopt_LM[i]->Sumw2();
            sprintf(name,"h_recopt_LN_%d",i+1);
            sprintf(title,"h_recopt_LN_%d",i+1);
            h_recopt_LN[i] = new TH1F(name,title, 10, LBin[i], HBin[i]);
            h_recopt_LN[i]->Sumw2();

            sprintf(name,"h_recopt_CM_%d",i+1);
            sprintf(title,"h_recopt_CM_%d",i+1);
            h_recopt_CM[i] = new TH1F(name,title, 10, LBin[i], HBin[i]);
            h_recopt_CM[i]->Sumw2();
            sprintf(name,"h_recopt_CN_%d",i+1);
            sprintf(title,"h_recopt_CN_%d",i+1);
            h_recopt_CN[i] = new TH1F(name,title, 10, LBin[i], HBin[i]);
            h_recopt_CN[i]->Sumw2();

            sprintf(name,"h_recopt_BM_%d",i+1);
            sprintf(title,"h_recopt_BM_%d",i+1);
            h_recopt_BM[i] = new TH1F(name,title, 10, LBin[i], HBin[i]);
            h_recopt_BM[i]->Sumw2();
            sprintf(name,"h_recopt_BN_%d",i+1);
            sprintf(title,"h_recopt_BN_%d",i+1);
            h_recopt_BN[i] = new TH1F(name,title, 10, LBin[i], HBin[i]);
            h_recopt_BN[i]->Sumw2();

            sprintf(name,"h_recopt_MC_%d",i+1);
            sprintf(title,"h_recopt_MC_%d",i+1);
            h_recopt_MC[i] = new TH1F(name,title, 10, LBin[i], HBin[i]);
            h_recopt_MC[i]->Sumw2();

            sprintf(name,"h_mva_MC_%d",i+1);
            sprintf(title,"h_mva_MC_%d",i+1);
            h_mva_MC[i] = new TH1F(name,title, 20, -1., 1.);
            h_mva_MC[i]->Sumw2();

        }

    // data part
    TH1F *h_mva_data[20];
    TH1F *h_recopt_data[20];
    TH1F *h_jetpt_data[20]; 
    if (!isMC )
        for (Int_t i=0;i<15;i++) {

            sprintf(name,"h_mva_data_%d",i+1);
            sprintf(title,"h_mva_data_%d",i+1);
            h_mva_data[i] = new TH1F(name,title, 20, -1., 1.); 
            h_mva_data[i]->Sumw2();

            sprintf(name,"h_recopt_data_%d",i+1);
            sprintf(title,"h_recopt_data_%d",i+1);
            h_recopt_data[i] = new TH1F(name,title, 10, LBin[i], HBin[i]);
            h_recopt_data[i]->Sumw2();

            sprintf(name,"h_jetpt_data_%d",i+1);
            sprintf(title,"h_jetpt_data_%d",i+1);
            h_jetpt_data[i] = new TH1F(name,title, 30, 0., 600.);
            h_jetpt_data[i]->Sumw2();

        }


    Int_t FiredTrgs[15]={0,1,2,3,3,4,5,5,6,6,6,7,7,7,7};


    Float_t n_l[15]={32957.964844, 38267.503906, 83379.875000, 57719.539062, 23084.937500, 54243.886719, 53688.183594, 37353.328125, 37592.421875, 20444.455078, 14032.282227, 474188.062500, 417623.468750, 320266.343750, 250206.593750};
    Float_t n_c[15]={4696.668457, 5878.100586, 12984.797852, 8667.257812, 3508.803467, 7356.348633, 7180.242676, 4185.255859, 4599.318359, 2422.927002, 1534.502563, 66954.476562, 56275.589844, 47858.011719, 52612.386719};
    Float_t n_b[15]={760.436096, 905.366150, 2461.268066, 1954.471313, 906.421021, 2087.768066, 2137.895508, 1583.307495, 1471.579102, 877.642456, 604.276062, 19580.164062, 18106.681641, 13649.618164, 9538.590820};

    Float_t w_l[15], w_c[15], w_b[15];

    for(int i=0;i<15;i++){
        w_l[i] = n_l[i]/(n_l[i]+n_c[i]+n_b[i]);
        w_c[i] = n_c[i]/(n_l[i]+n_c[i]+n_b[i]);
        w_b[i] = n_b[i]/(n_l[i]+n_c[i]+n_b[i]);
    }

    Float_t w_is[15]={0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7};
    Float_t w_not[15]={0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3};

    for(int i = 0 ; i < t->GetEntries() ; i++){

        t->GetEntry(i);
        float eventweight = isMC ? puwei * mcweight : 1.;

        if ( isMC )
            for(int j = 0 ; j < 15; j++){
                if(recoPt>LBin[j] && recoPt<=HBin[j] && chIsoRaw < 2.0 && jetPt != 0){
                    h_mva_MC[j]->Fill(mva,eventweight*w_is[j]*w_l[j]);
                    if (mva > 0){
                        h_jetpt_MC[j]->Fill(jetPt,eventweight*w_is[j]*w_l[j]);
                        h_recopt_MC[j]->Fill(recoPt,eventweight*w_is[j]*w_l[j]);
                        if(isMatched==1){
                            if(flavour == 0) {
                                h_jetpt_LM[j]->Fill(jetPt,eventweight*w_is[j]*w_l[j]);
                                h_recopt_LM[j]->Fill(recoPt,eventweight*w_is[j]*w_l[j]);
                            }else if (flavour == 4) {
                                h_jetpt_CM[j]->Fill(jetPt,eventweight*w_is[j]*w_c[j]);
                                h_recopt_CM[j]->Fill(recoPt,eventweight*w_is[j]*w_c[j]);
                            }else{
                                h_jetpt_BM[j]->Fill(jetPt,eventweight*w_is[j]*w_b[j]);
                                h_recopt_BM[j]->Fill(recoPt,eventweight*w_is[j]*w_b[j]); 
                            }		
                        }else{
                            if(flavour == 0) {
                                h_jetpt_LN[j]->Fill(jetPt,eventweight*w_is[j]*w_l[j]);
                                h_recopt_LN[j]->Fill(recoPt,eventweight*w_is[j]*w_l[j]);
                            }else if (flavour == 4) {
                                h_jetpt_CN[j]->Fill(jetPt,eventweight*w_is[j]*w_c[j]);
                                h_recopt_CN[j]->Fill(recoPt,eventweight*w_is[j]*w_c[j]);
                            }else{
                                h_jetpt_BN[j]->Fill(jetPt,eventweight*w_is[j]*w_b[j]);
                                h_recopt_BN[j]->Fill(recoPt,eventweight*w_is[j]*w_b[j]);
                            }
                        }
                    }	
                }
            }
        if (!isMC )
            for(int j = 0 ; j < 15; j++){
                if(recoPt>LBin[j] && recoPt<=HBin[j] && chIsoRaw < 2.0 && ((phoFiredTrgs>>FiredTrgs[j])&1)==1 && jetPt!=0 ){
                    h_mva_data[j]->Fill(mva);
                    if (mva > 0){
                        h_recopt_data[j]->Fill(recoPt);
                        h_jetpt_data[j]->Fill(jetPt);
                    }
                }
            }
    }

    TFile *f = new TFile("hist.root","recreate");

    for(Int_t h = 0; h < 15; h++){
        if ( isMC ) {
            //h_jetpt_LM[h]->Write();
            //h_jetpt_BM[h]->Write();
            //h_jetpt_CM[h]->Write();
            //h_jetpt_LN[h]->Write();
            //h_jetpt_BN[h]->Write();
            //h_jetpt_CN[h]->Write();
            h_jetpt_MC[h]->Write();
            h_recopt_MC[h]->Write();
            h_mva_MC[h]->Write();
        } else {
            h_recopt_data[h]->Write();
            h_jetpt_data[h]->Write();
            h_mva_data[h]->Write();
        }
    }
    f->Close();
}

