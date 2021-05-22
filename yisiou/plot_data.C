{
   ///<Purpose>
   // extract some particular leaves from input.root
   // and collect them into a new root files
   
   ///<Usage>
   // [Bash] root.exe input.root
   // [root] .x reduce.C
   // output: ./reduce1.root

   // t1 : the tree of input.root
   // upper case : the leaf of input.root
   //
   //  t : the tree of output.root
   // lower case : the leaf of output.root
   
   /// set the tree of input.root as t1
   TTree *t = (TTree*)_file0->Get("t");

   /// set the leaf of input.root as upper case
   
   // those exist in the input.root
   Float_t JetPt, RecoPt, JetEta, JetPhi, JetY, JetSubVtxPt, JetSubVtx3DVal, JetSubVtx3DErr, JetSubVtxMass, JetDeepCSVTags_b, JetDeepCSVTags_bb, JetDeepCSVTags_c, JetDeepCSVTags_udsg, PhotonIDmva,  Xsweight, JetCSV2BJetTags;
   Int_t JetSubVtxNtrks, JetHadFlvr, phoFiredTrgs;

   // those don't exist in the input.root 
   Float_t btagger, CvsL, CvsB;
   

   Float_t jetPt, recoPt, jetEta, jetPhi, jetY, jetSubVtxPt, jetSubVtx3DVal, jetSubVtx3DErr, jetSubVtxMass, jetDeepCSVTags_b, jetDeepCSVTags_bb, jetDeepCSVTags_c, jetDeepCSVTags_udsg, photonIDmva, jetCSV2BJetTags, chIsoRaw, mva;  
   //Float_t weight, Lumi;

   Int_t jetSubVtxNtrks, flavour, files;


   TH1F *h_btag_data[20];
   TH1F *h_cvsl_b[20]; 
   TH1F *h_cvsl_c[20];
   TH1F *h_cvsl_l[20];
   TH1F *h_cvsl_mc[20];
   TH1F *h_cvsb_b[20]; 
   TH1F *h_cvsb_c[20];
   TH1F *h_cvsb_l[20];
   TH1F *h_cvsb_mc[20];

   TH1F *h_mva_data[20];
   TH1F *h_recopt_data[20];
   TH1F *h_jetpt_data[20]; 

   TH1F *h_jetpt_total_data = new TH1F("jetpt_data","jetpt_data", 300, 0., 600.);

   Float_t LBin[14]={25,34,40,55,70,85,100,115,135,155,175,200,250,300};
   Float_t HBin[14]={34,40,55,70,85,100,115,135,155,175,200,250,300,1000};
   

   char name[30];
   char title[40]; 
   for (Int_t i=0;i<14;i++) {

     ///using BCtag

   //contains B and C tagging

     ///B-tagging

      sprintf(name,"h_btag_data_%d",i+1);
      sprintf(title,"h_btag_data_%d",i+1);
      h_btag_data[i] = new TH1F(name,title, 25, 0., 1.);
      h_btag_data[i]->Sumw2();

      sprintf(name,"h_mva_data_%d",i+1);
      sprintf(title,"h_mva_data_%d",i+1);
      h_mva_data[i] = new TH1F(name,title, 50, -1., 1.); 
      h_mva_data[i]->Sumw2();

      sprintf(name,"h_recopt_data_%d",i+1);
      sprintf(title,"h_recopt_data_%d",i+1);
      h_recopt_data[i] = new TH1F(name,title, 100, LBin[i], HBin[i]);
      h_recopt_data[i]->Sumw2();

      sprintf(name,"h_jetpt_data_%d",i+1);
      sprintf(title,"h_jetpt_data_%d",i+1);
      h_jetpt_data[i] = new TH1F(name,title, 300, 0., 600.);
      h_jetpt_data[i]->Sumw2();
     
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

   


   
   Int_t buff=300000000;
   Float_t Lumi[10]={1.073e-01, 1.092e-01, 4.305e-01, 4.322e-01, 3.590e+00, 3.680e+00, 4.771e-02, 4.910e-02, 1.065e+01, 1.056e+01};
   Float_t size[10]={3480023, 3592694, 5978516, 5815190, 1274485, 1276271, 4067116, 3741619, 1251989, 1178579};
//   Float_t xsec[10]={};
   Float_t weight[10];
//   Int_t LBin[14]={25,34,40,55,70,85,100,115,135,155,175,200,250,300};
//   Int_t HBin[14]={34,40,55,70,85,100,115,135,155,175,200,250,300,1000};
   Int_t FiredTrgs[14]={0,1,2,3,3,4,5,5,6,6,6,7,7,7};

   for(int i=0;i<10;i++){
	//weight[i] = 1./((size[i]/1000000.)*Lumi[i]);
	//weight[i] = 1./Lumi[i];
	weight[i] = 1;
	printf("%f\n", weight[i]);
   }


//TGraph2D *dt = new TGraph2D();
//TGraph*gr1 = new TGraph(100,&jetPt,&recoPt);
//gr1->Draw();

TCanvas *c1 = new TCanvas("c1"); 
//t->Draw("jetPt:recoPt","jetSubVtxMass !=0 && jetPt>25 && recoPt>25 && photonIDmva > 0 && jetCSV2BJetTags > 0.8484"); 
//TGraph *gr = (TGraph*)gPad->GetPrimitive("Graph");
//gr->GetCorrelationFactor();
//gr->GetCovariance();


//t->Draw("btagger"," jetPt>175 && jetPt<=300 && recoPt>175 && recoPt<=300 && photonIDmva > 0 && jetCSV2BJetTags > 0.8484"); 

//t->Draw("btagger"," jetPt>175 && jetPt<=300 && recoPt>175 && recoPt<=300 && photonIDmva > 0");


// 22 30 36 50 75 90 120 175 300


for(int i = 0 ; i < t->GetEntries() ; i++){

  t->GetEntry(i);
  
	h_jetpt_total_data->Fill(jetPt,weight[files]);

  for(int j = 0 ; j < 14; j++){

  if(recoPt>LBin[j] && recoPt<=HBin[j] && chIsoRaw < 2.0 && ((phoFiredTrgs>>FiredTrgs[j])&1)==1  ){
	h_mva_data[j]->Fill(mva,weight[files]);
	if (mva > 0){
		h_recopt_data[j]->Fill(recoPt,weight[files]);
		h_jetpt_data[j]->Fill(jetPt,weight[files]);
		h_btag_data[j]->Fill(btagger,weight[files]);	
	}
	
  }

  } //for with j




}


//t.Write();
TFile *f = new TFile("hist.root","update");//rereate

for(Int_t h = 0; h < 14; h++){

   h_btag_data[h]->Write();
   h_recopt_data[h]->Write();
   h_jetpt_data[h]->Write();
   h_mva_data[h]->Write();
}
   h_jetpt_total_data->Write();

      f->Close();

}
