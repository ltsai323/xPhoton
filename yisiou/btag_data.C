{
   TTree *t = (TTree*)_file0->Get("t");

   Int_t phoFiredTrgs;
   Float_t jetPt, recoPt, jetEta, jetPhi, jetY, jetSubVtxPt, jetSubVtx3DVal, jetSubVtx3DErr, jetSubVtxMass, jetDeepCSVTags_b, jetDeepCSVTags_bb, jetDeepCSVTags_c, jetDeepCSVTags_udsg, photonIDmva, jetCSV2BJetTags, chIsoRaw, mva;  
   Int_t jetSubVtxNtrks, flavour, files, isMatched;

   TH1F *h_btag_data[20];

   Float_t LBin[15]={25,34,40,55,70,85,100,115,135,155,175,200,220,250,300};
   Float_t HBin[15]={34,40,55,70,85,100,115,135,155,175,200,220,250,300,1000};
   

   char name[30];
   char title[40]; 
   for (Int_t i=0;i<15;i++) {

      sprintf(name,"h_btag_data_%d",i+1);
      sprintf(title,"h_btag_data_%d",i+1);
      h_btag_data[i] = new TH1F(name,title, 10, 0., 1.);
      h_btag_data[i]->Sumw2(); 
   }

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
   t->SetBranchAddress("flavour",&flavour); //
   t->SetBranchAddress("phoFiredTrgs",&phoFiredTrgs);
   t->SetBranchAddress("chIsoRaw",&chIsoRaw);
   t->SetBranchAddress("mva",&mva);
   t->SetBranchAddress("files",&files);
   t->SetBranchAddress("isMatched",&isMatched);

   Int_t FiredTrgs[15]={0,1,2,3,3,4,5,5,6,6,6,7,7,7,7};


for(int i = 0 ; i < t->GetEntries() ; i++){

  t->GetEntry(i);

  for(int j = 0 ; j < 15; j++){


if(recoPt>LBin[j] && recoPt<=HBin[j] && chIsoRaw < 2.0 && jetPt!=0 && ((phoFiredTrgs>>FiredTrgs[j])&1)==1  ){

	if (mva > 0){
		h_btag_data[j]->Fill(jetDeepCSVTags_b+jetDeepCSVTags_bb);
	}
	
  }

  }


}




TFile *f = new TFile("./hist_btag.root","update");

for(Int_t h = 0; h < 15; h++){
   h_btag_data[h]->Write();
}
      f->Close();
}
