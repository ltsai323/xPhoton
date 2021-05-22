                    {
   TTree *t = (TTree*)_file0->Get("t");

   Float_t JetPt, RecoPt, JetEta, JetPhi, JetY, JetSubVtxPt, JetSubVtx3DVal, JetSubVtx3DErr, JetSubVtxMass, JetDeepCSVTags_b, JetDeepCSVTags_bb, JetDeepCSVTags_c, JetDeepCSVTags_udsg, PhotonIDmva,  Xsweight, JetCSV2BJetTags;
   Int_t JetSubVtxNtrks, JetHadFlvr, phoFiredTrgs;

   Float_t btagger, CvsL, CvsB;
   

   Float_t jetPt, recoPt, jetEta, jetPhi, jetY, jetSubVtxPt, jetSubVtx3DVal, jetSubVtx3DErr, jetSubVtxMass, jetDeepCSVTags_b, jetDeepCSVTags_bb, jetDeepCSVTags_c, jetDeepCSVTags_udsg, photonIDmva, jetCSV2BJetTags, chIsoRaw, mva;  
   //Float_t weight, Lumi;

   Int_t jetSubVtxNtrks, flavour, files, isMatched;

   
   TH1F *h_jetpt_LM[20];
   TH1F *h_jetpt_LN[20];
   TH1F *h_jetpt_CM[20];
   TH1F *h_jetpt_CN[20];
   TH1F *h_jetpt_BM[20];
   TH1F *h_jetpt_BN[20];
   

   TH1F *h_jetpt_L[20];
   TH1F *h_jetpt_C[20];
   TH1F *h_jetpt_B[20];
   TH1F *h_jetpt_mc[20];


   TH1F *h_btag_b[20];
   TH1F *h_btag_c[20];
   TH1F *h_btag_l[20];
   TH1F *h_btag_mc[20];
   TH1F *h_cvsl_b[20]; 
   TH1F *h_cvsl_c[20];
   TH1F *h_cvsl_l[20];
   TH1F *h_cvsl_mc[20];
   TH1F *h_cvsb_b[20]; 
   TH1F *h_cvsb_c[20];
   TH1F *h_cvsb_l[20];
   TH1F *h_cvsb_mc[20];

   TH1F *h_mva[20];
   TH1F *h_recopt[20];
   TH1F *h_jetpt[20]; 

	TH1F *h_jetpt_total = new TH1F("jetpt","jetpt", 300, 0., 600.);

   Float_t LBin[14]={25,34,40,55,70,85,100,115,135,155,175,200,250,300};
   Float_t HBin[14]={34,40,55,70,85,100,115,135,155,175,200,250,300,1000};
   

   char name[30];
   char title[40]; 
   for (Int_t i=0;i<14;i++) {

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

     ///using BCtag

   //contains B and C tagging

     ///B-tagging
      sprintf(name,"h_btag_b_%d",i+1);
      sprintf(title,"h_btag_b_%d",i+1);
      h_btag_b[i] = new TH1F(name,title, 25, 0., 1.);
      h_btag_b[i]->Sumw2();

      sprintf(name,"h_btag_c_%d",i+1);
      sprintf(title,"h_btag_c_%d",i+1);
      h_btag_c[i] = new TH1F(name,title, 25, 0., 1.);
      h_btag_c[i]->Sumw2();

      sprintf(name,"h_btag_l_%d",i+1);
      sprintf(title,"h_btag_l_%d",i+1);
      h_btag_l[i] = new TH1F(name,title, 25, 0., 1.);
      h_btag_l[i]->Sumw2();

      sprintf(name,"h_btag_mc_%d",i+1);
      sprintf(title,"h_btag_mc_%d",i+1);
      h_btag_mc[i] = new TH1F(name,title, 25, 0., 1.);
      h_btag_mc[i]->Sumw2();

      sprintf(name,"h_mva_%d",i+1);
      sprintf(title,"h_mva_%d",i+1);
      h_mva[i] = new TH1F(name,title, 50, -1., 1.); 
      h_mva[i]->Sumw2();

      sprintf(name,"h_recopt_%d",i+1);
      sprintf(title,"h_recopt_%d",i+1);
      h_recopt[i] = new TH1F(name,title, 100, LBin[i], HBin[i]);
      h_recopt[i]->Sumw2();

      sprintf(name,"h_jetpt_%d",i+1);
      sprintf(title,"h_jetpt_%d",i+1);
      h_jetpt[i] = new TH1F(name,title, 30, 0., 600.);
      h_jetpt[i]->Sumw2();

      sprintf(name,"h_jetpt_L_%d",i+1);
      sprintf(title,"h_jetpt_L_%d",i+1);
      h_jetpt_L[i] = new TH1F(name,title, 30, 0., 600.);
      h_jetpt_L[i]->Sumw2();
      
      sprintf(name,"h_jetpt_C_%d",i+1);
      sprintf(title,"h_jetpt_C_%d",i+1);
      h_jetpt_C[i] = new TH1F(name,title, 30, 0., 600.);
      h_jetpt_C[i]->Sumw2();
      
      sprintf(name,"h_jetpt_B_%d",i+1);
      sprintf(title,"h_jetpt_B_%d",i+1);
      h_jetpt_B[i] = new TH1F(name,title, 30, 0., 600.);
      h_jetpt_B[i]->Sumw2();

      
     
   }

   /// set the address
   t->SetBranchAddress("jetPt",&jetPt);
   t->SetBranchAddress("recoPt",&recoPt);
   t->SetBranchAddress("jetEta",&jetEta);
   t->SetBranchAddress("jetPhi",&jetPhi);
   t->SetBranchAddress("jetY",&jetY);
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
   t->SetBranchAddress("flavour",&flavour); //
   //t->SetBranchAddress("weight",&weight);  
   t->SetBranchAddress("btagger",&btagger);
   t->SetBranchAddress("phoFiredTrgs",&phoFiredTrgs);
   t->SetBranchAddress("CvsL",&CvsL);
   t->SetBranchAddress("CvsB",&CvsB);
   t->SetBranchAddress("chIsoRaw",&chIsoRaw);
   t->SetBranchAddress("mva",&mva);
   t->SetBranchAddress("files",&files);
   t->SetBranchAddress("isMatched",&isMatched);

   


   
   Int_t buff=300000000;
   Float_t Lumi[10]={1.073e-01, 1.092e-01, 4.305e-01, 4.322e-01, 3.590e+00, 3.680e+00, 4.771e-02, 4.910e-02, 1.065e+01, 1.056e+01};
   Float_t size[10]={3480023, 3592694, 5978516, 5815190, 1274485, 1276271, 4067116, 3741619, 1251989, 1178579};
//   Float_t xsec[10]={};
   Float_t weight[10];
//   Int_t LBin[14]={25,34,40,55,70,85,100,115,135,155,175,200,250,300};
//   Int_t HBin[14]={34,40,55,70,85,100,115,135,155,175,200,250,300,1000};
   Int_t FiredTrgs[14]={0,1,2,3,3,4,5,5,6,6,6,7,7,7};

   Float_t w_l[15]={32957.964844, 38267.503906, 83379.875000, 57719.539062, 23084.937500, 54243.886719, 53688.183594, 37353.328125, 37592.421875, 20444.455078, 14032.282227, 879232.625000, 308355.500000, 220188.359375, 220188.359375};
   Float_t w_c[15]={4696.668457, 5878.100586, 12984.797852, 8667.257812, 3508.803467, 7356.348633, 7180.242676, 4185.255859, 4599.318359, 2422.927002, 1534.502563, 137091.484375, 61136.398438, 84001.429688, 84001.429688};
   Float_t w_b[15]={760.436096, 905.366150, 2461.268066, 1954.471313, 906.421021, 2087.768066, 2137.895508, 1583.307495, 1471.579102, 877.642456, 604.276062, 36406.402344, 12282.214844, 8167.831543, 8167.831543};

   Float_t w_is[15]={0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7};
   Float_t w_not[15]={0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3};

   for(int i=0;i<10;i++){
	weight[i] = 1./((size[i]/1000000.)*Lumi[i]);
	//weight[i] = 1./Lumi[i];
	//weight[i] = 1.;
	printf("%f\n", weight[i]);
   }

TCanvas *c1 = new TCanvas("c1"); 



for(int i = 0 ; i < t->GetEntries() ; i++){

  t->GetEntry(i);
  
  //h_jetpt_total->Fill(jetPt,weight[files]);

  for(int j = 8 ; j < 14; j++){


//if(recoPt>LBin[j] && recoPt<=HBin[j] && chIsoRaw < 2.0 && ((phoFiredTrgs>>FiredTrgs[j])&1)==1  ){

if(recoPt>LBin[j] && recoPt<=HBin[j] && chIsoRaw < 2.0 && isMatched == 1 ){

	h_mva[j]->Fill(mva,weight[files]*w_is[files]);
	if (mva > 0){
	  //h_recopt[j]->Fill(recoPt,weight[files]*w_is[files]);
	  //h_jetpt[j]->Fill(jetPt,weight[files]*w_is[files]);
	  //h_btag_mc[j]->Fill(btagger,weight[files]*w_is[files]);
      		if(flavour == 0) {
		  //h_btag_l[j]->Fill(btagger,weight[files]*w_is[files]*w_l[files]);
			h_jetpt_L[j]->Fill(jetPt,weight[files]*w_is[files]*w_l[files]);
		}else if (flavour == 4) {
		  //h_btag_c[j]->Fill(btagger,weight[files]*w_is[files]*w_c[files]);
			h_jetpt_C[j]->Fill(jetPt,weight[files]*w_is[files]*w_c[files]);
  	        }else{
		  //h_btag_b[j]->Fill(btagger,weight[files]*w_is[files]*w_b[files]);
			h_jetpt_B[j]->Fill(jetPt,weight[files]*w_is[files]*w_b[files]);
	     }		
	}
	
  }

  } //for with j



/////////
/////////


}


//t.Write();
TFile *f = new TFile("hist.root","recreate");

for(Int_t h = 8; h < 14; h++){

   //h_btag_l[h]->Write();
   //h_btag_b[h]->Write();
   //h_btag_c[h]->Write();
   //h_btag_mc[h]->Write();
   //h_recopt[h]->Write();
   //h_jetpt[h]->Write();
   h_jetpt_L[h]->Write();
   h_jetpt_B[h]->Write();
   h_jetpt_C[h]->Write();
   //h_mva[h]->Write();
}
//h_jetpt_total->Write();

      f->Close();

}
