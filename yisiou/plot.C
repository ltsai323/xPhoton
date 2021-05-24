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
   
   TH1F *h_mva_data[20];
   TH1F *h_recopt_data[20];
   TH1F *h_jetpt_data[20]; 
   TH1F *h_btag_data[20];
   

   TH1F *h_jetpt_total = new TH1F("jetpt","jetpt", 300, 0., 600.);
   TH1F *h_jetpt_total_data = new TH1F("jetpt_data","jetpt_data", 300, 0., 600.);

   Float_t LBin[15]={25,34,40,55,70,85,100,115,135,155,175,200,220,250,300};
   Float_t HBin[15]={34,40,55,70,85,100,115,135,155,175,200,220,250,300,1000};
   


   char filename[100];
   char name[30];
   char title[40]; 
   for (Int_t i=0;i<15;i++) {


      sprintf(name,"h_mva_%d",i+1);
      sprintf(title,"h_mva_%d",i+1);
      h_mva[i] = new TH1F(name,title, 20, -1., 1.); 

      sprintf(name,"h_recopt_%d",i+1);
      sprintf(title,"h_recopt_%d",i+1);
      h_recopt[i] = new TH1F(name,title, 10, LBin[i], HBin[i]);

      sprintf(name,"h_jetpt_%d",i+1);
      sprintf(title,"h_jetpt_%d",i+1);
      h_jetpt[i] = new TH1F(name,title, 30, 0., 600.);



      sprintf(name,"h_mva_data_%d",i+1);
      sprintf(title,"h_mva_data_%d",i+1);
      h_mva_data[i] = new TH1F(name,title, 20, -1., 1.); 

      sprintf(name,"h_recopt_data_%d",i+1);
      sprintf(title,"h_recopt_data_%d",i+1);
      h_recopt_data[i] = new TH1F(name,title, 10, LBin[i], HBin[i]);

      sprintf(name,"h_jetpt_data_%d",i+1);
      sprintf(title,"h_jetpt_data_%d",i+1);
      h_jetpt_data[i] = new TH1F(name,title, 30, 0., 600.);

     
   }

   TFile *f = new TFile("hist.root");
   f->ls();
   //TTree *t = (TTree*)_f->Get("t");
   //
   TCanvas g("canvas", "canvas", 1024, 600);

for(int i=0;i<15;i++){
/*
      sprintf(name,"h_mva_MC_%d",i+1);
      sprintf(title,"h_mva_%d",i+1);
      sprintf(filename,"./plots/h_mva_%d.png",i+1);
      g.cd();
      h_mva[i] = (TH1F*)f->Get(name);
      h_mva[i]->Scale(1./h_mva[i]->Integral());
      h_mva[i]->Draw("h");
      sprintf(name,"h_mva_data_%d",i+1);
      sprintf(title,"h_mva_data_%d",i+1);
      h_mva_data[i] = (TH1F*)f->Get(name);
      h_mva_data[i]->Scale(1./h_mva_data[i]->Integral());
      h_mva_data[i]->SetLineColor(kBlack);
      h_mva_data[i]->SetMarkerStyle(8);
      h_mva_data[i]->Draw("p e same");
      
      g.SaveAs(filename);
      
      sprintf(name,"h_recopt_MC_%d",i+1);
      sprintf(title,"h_recopt_%d",i+1);
      sprintf(filename,"./plots/h_recopt_%d.png",i+1);
      g.cd();
      h_recopt[i] = (TH1F*)f->Get(name);
      h_recopt[i]->Scale(1./h_recopt[i]->Integral());
      h_recopt[i]->Draw("h");
      sprintf(name,"h_recopt_data_%d",i+1);
      sprintf(title,"h_recopt_data_%d",i+1);
      h_recopt_data[i] = (TH1F*)f->Get(name);
      h_recopt_data[i]->Scale(1./h_recopt_data[i]->Integral());
      h_recopt_data[i]->SetLineColor(kBlack);
      h_recopt_data[i]->SetMarkerStyle(8);
      h_recopt_data[i]->Draw("p e same");
      
      g.SaveAs(filename);
*/
      sprintf(name,"h_jetpt_MC_%d",i+1);
      sprintf(title,"h_jetpt_%d",i+1);
      sprintf(filename,"./plots/h_jetpt_%d.png",i+1);
      g.cd();
      h_jetpt[i] = (TH1F*)f->Get(name);
      h_jetpt[i]->Scale(1./h_jetpt[i]->Integral());
      h_jetpt[i]->SetLineColor(kRed);
      h_jetpt[i]->Draw("h");
      sprintf(name,"h_jetpt_data_%d",i+1);
      sprintf(title,"h_jetpt_data_%d",i+1);
      h_jetpt_data[i] = (TH1F*)f->Get(name);
      h_jetpt_data[i]->Scale(1./h_jetpt_data[i]->Integral());
      h_jetpt_data[i]->SetLineColor(kBlack);
      h_jetpt_data[i]->SetMarkerStyle(8);
      h_jetpt_data[i]->Draw("p e same");
      g.SaveAs(filename);
      

}
//   g.cd();
//
//   TH1F * h = new TH1F("h","h" , 300, 0, 600);
   
//   h = (TH1F*)f->Get("jetpt");
//   h->Draw();
//   g.SaveAs("./plots/jetpt.png");

}
