{
   TTree *t = (TTree*)_file0->Get("t");

   Int_t phoFiredTrgs;
   Float_t jetPt, recoPt, jetEta, jetPhi, jetY, jetSubVtxPt, jetSubVtx3DVal, jetSubVtx3DErr, jetSubVtxMass, jetDeepCSVTags_b, jetDeepCSVTags_bb, jetDeepCSVTags_c, jetDeepCSVTags_udsg, photonIDmva, jetCSV2BJetTags, chIsoRaw, mva;  
   Int_t jetSubVtxNtrks, flavour, files, isMatched;

   TH1F *h_btag_b[20];
   TH1F *h_btag_c[20];
   TH1F *h_btag_l[20];

   Float_t LBin[15]={25,34,40,55,70,85,100,115,135,155,175,200,220,250,300};
   Float_t HBin[15]={34,40,55,70,85,100,115,135,155,175,200,220,250,300,1000};
   

   char name[30];
   char title[40]; 
   for (Int_t i=0;i<15;i++) {

      sprintf(name,"h_btag_l_%d",i+1);
      sprintf(title,"h_btag_l_%d",i+1);
      h_btag_l[i] = new TH1F(name,title, 10, 0., 1.);
      h_btag_l[i]->Sumw2();
      
      sprintf(name,"h_btag_b_%d",i+1);
      sprintf(title,"h_btag_b_%d",i+1);
      h_btag_b[i] = new TH1F(name,title, 10, 0., 1.);
      h_btag_b[i]->Sumw2();
      
      sprintf(name,"h_btag_c_%d",i+1);
      sprintf(title,"h_btag_c_%d",i+1);
      h_btag_c[i] = new TH1F(name,title, 10, 0., 1.);
      h_btag_c[i]->Sumw2();

      
     
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
   t->SetBranchAddress("phoFiredTrgs",&phoFiredTrgs);
   t->SetBranchAddress("chIsoRaw",&chIsoRaw);
   t->SetBranchAddress("mva",&mva);
   t->SetBranchAddress("files",&files);
   t->SetBranchAddress("isMatched",&isMatched);

   


   
   Int_t buff=300000000;
   Float_t Lumi[10]={1.073e-01, 1.092e-01, 4.305e-01, 4.322e-01, 3.590e+00, 3.680e+00, 4.771e-02, 4.910e-02, 1.065e+01, 1.056e+01};
   Float_t weight[10];
   Int_t FiredTrgs[15]={0,1,2,3,3,4,5,5,6,6,6,7,7,7,7};

   for(int i=0;i<10;i++){
	weight[i] = 1./Lumi[i];
	printf("%f\n", weight[i]);
   }



for(int i = 0 ; i < t->GetEntries() ; i++){

  t->GetEntry(i);


  for(int j = 0 ; j < 15; j++){


	if(recoPt>LBin[j] && recoPt<=HBin[j] && chIsoRaw < 2.0 && jetPt != 0 ){
	
	if (mva > 0){
      		if(flavour == 0) {
			h_btag_l[j]->Fill(jetDeepCSVTags_b+jetDeepCSVTags_bb,weight[files]);
		}else if (flavour == 4) {
			h_btag_c[j]->Fill(jetDeepCSVTags_b+jetDeepCSVTags_bb,weight[files]);
  	        }else{
			h_btag_b[j]->Fill(jetDeepCSVTags_b+jetDeepCSVTags_bb,weight[files]);
	     }		
	}
	
  	}

  }

}

for(int j = 0 ; j < 15; j++){
	h_btag_l[j]->Scale(1./h_btag_l[j]->Integral());
	h_btag_c[j]->Scale(1./h_btag_c[j]->Integral());
	h_btag_b[j]->Scale(1./h_btag_b[j]->Integral());
}


TFile *f = new TFile("./hist_btag.root","recreate");

for(Int_t h = 0; h < 15; h++){

   h_btag_l[h]->Write();
   h_btag_b[h]->Write();
   h_btag_c[h]->Write();

}

      f->Close();


}


