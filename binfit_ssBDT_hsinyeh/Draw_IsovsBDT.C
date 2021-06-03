#include <TH1.h>
#include <TH2.h>
void Draw_IsovsBDT(char EBEE[10]="EB", int jetbin=0, int ptbin=14, int rebinoption=5, int sb1=14, int sb2=20){
  
  TFile *fqcd = new TFile("mc_QCD.root");
  //TFile *fgjet = new TFile("mc_gjet6000.root");
  // TFile *fgjet = new TFile("mc_hggfilter.root");
  //TFile *fgjet = new TFile("mc_QCD_noHLT.root");
  //TFile *fgjet = new TFile("mc_hggfilter_bdt_m.root");
  //TFile *fgjet = new TFile("mc_gjet_MG.root");
  TFile *fgjet = new TFile("output_mc.root");
  

  // TFile *fdata = new TFile("data.root");
  TFile *fdata = new TFile("output_data.root");
  char hname[100];
  int ebee=0;
  if(strcmp(EBEE,"EE")==0) ebee=1;

  TH2F *hgjet;
  TH2F *hqcd;
  TH2F *hdata;

  int IsoOption=0; //0 chIso, 1 phoIso, 2 combIso, 3 chWorst

  if(jetbin==0){
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, jetbin, ptbin, IsoOption);  
    hqcd = (TH2F*)fqcd->Get(hname);
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, jetbin, ptbin, IsoOption);  
    hgjet = (TH2F*)fgjet->Get(hname);
    hdata = (TH2F*)fdata->Get(hname);
  }else if(jetbin==1){
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, jetbin, ptbin, IsoOption);  
    hqcd = (TH2F*)fqcd->Get(hname);
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, jetbin, ptbin, IsoOption);  
    hgjet = (TH2F*)fgjet->Get(hname);
    hdata = (TH2F*)fdata->Get(hname);
  }else{
    printf("jet bin %d \n", jetbin);
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, 0, ptbin, IsoOption);  
    hqcd = (TH2F*)fqcd->Get(hname);
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, 1, ptbin, IsoOption);  
    hqcd->Add((TH2F*)fqcd->Get(hname));
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, 2, ptbin, IsoOption);  
    hqcd->Add((TH2F*)fqcd->Get(hname));

    sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, 0, ptbin, IsoOption);  
    hgjet = (TH2F*)fgjet->Get(hname);
    hdata = (TH2F*)fdata->Get(hname);
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, 1, ptbin, IsoOption);  
    hgjet->Add((TH2F*)fgjet->Get(hname));
    hdata->Add((TH2F*)fdata->Get(hname));
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, 2, ptbin, IsoOption);  
    hgjet->Add((TH2F*)fgjet->Get(hname));
    hdata->Add((TH2F*)fdata->Get(hname));
  }
  
  //if ploting all pt range
   // for(int ii=ptbin+1; ii<21; ii++){
   //   sprintf(hname,"h_IsovsBDT_%d_0_%d_1_%d",ebee, ptbin, IsoOption);  
   //   hqcd->Add((TH2F*)fqcd->Get(hname));
   //   sprintf(hname,"h_IsovsBDT_%d_1_%d_1_%d",ebee, ptbin, IsoOption);  
   //   hqcd->Add((TH2F*)fqcd->Get(hname));
   //   sprintf(hname,"h_IsovsBDT_%d_2_%d_1_%d",ebee, ptbin, IsoOption);  
   //   hqcd->Add((TH2F*)fqcd->Get(hname));
  
   //   sprintf(hname,"h_IsovsBDT_%d_0_%d_0_%d",ebee, ptbin, IsoOption);  
   //   hgjet->Add((TH2F*)fgjet->Get(hname));
   //   sprintf(hname,"h_IsovsBDT_%d_1_%d_0_%d",ebee, ptbin, IsoOption);  
   //   hgjet->Add((TH2F*)fgjet->Get(hname));
   //   sprintf(hname,"h_IsovsBDT_%d_2_%d_0_%d",ebee, ptbin, IsoOption);  
   //   hgjet->Add((TH2F*)fgjet->Get(hname));
   // }

  TH2F* hgjet_all = (TH2F*)hgjet->Clone();
  TH2F* hqcd_all = (TH2F*)hqcd->Clone();
  TH2F* hdata_all = (TH2F*)hdata->Clone(); 
  
  sprintf(hname,"gjet_all_%d_%d_%d",ebee, jetbin, ptbin);  
  hgjet_all->SetName(hname);
  sprintf(hname,"qcd_all_%d_%d_%d",ebee, jetbin, ptbin);  
  hqcd_all->SetName(hname);
  sprintf(hname,"data_all_%d_%d_%d",ebee, jetbin, ptbin);  
  hdata_all->SetName(hname);


  Printf("data %.0f, signal %.2f, bkg %.2f \n", hdata->Integral(), hgjet->Integral(), hqcd->Integral());

  hqcd->Rebin2D(rebinoption,2);
  hgjet->Rebin2D(rebinoption,2);
  hdata->Rebin2D(rebinoption,2);

  int nbinx = hqcd->GetNbinsX();

  hgjet->SetMinimum(0);
  hqcd->SetMinimum(0);
  TCanvas *c1 = new TCanvas("c1","",1000,500);
  c1->Divide(2,1);
  c1->cd(1);
  hgjet->Draw("colz");
  c1->cd(2);  
  hqcd->Draw("colz");

  //return;
  
  int zone1_low = 1;
  int zone1_high = 4; 
  if(ebee==1) { //EE
    if(IsoOption==0) zone1_high=3;
    else if(IsoOption==1) zone1_high=5;
    else if(IsoOption==2) zone1_high=7;
    else if(IsoOption==3) zone1_high=6;
  }

  int zone2_low = sb1;
  int zone2_high = sb2;
  //for production 
  if(ebee==0) {zone2_low=14; zone2_high=26;} //EB
  else {zone2_low=12; zone2_high=24;}
 
  
  //for chIso SB
  sprintf(hname,"gjet_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
  TH1F *h_gjet_zone1 = (TH1F*)hgjet->ProjectionX(hname,zone1_low, zone1_high);
  sprintf(hname,"gjet_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
  TH1F *h_gjet_zone2 = (TH1F*)hgjet->ProjectionX(hname,zone2_low, zone2_high);
  sprintf(hname,"qcd_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
  TH1F *h_qcd_zone1 = (TH1F*)hqcd->ProjectionX(hname,zone1_low, zone1_high);
  sprintf(hname,"qcd_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
  TH1F *h_qcd_zone2 = (TH1F*)hqcd->ProjectionX(hname,zone2_low, zone2_high);
  sprintf(hname,"data_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
  TH1F *h_data_zone1 = (TH1F*)hdata->ProjectionX(hname,zone1_low, zone1_high);
  sprintf(hname,"data_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
  TH1F *h_data_zone2 = (TH1F*)hdata->ProjectionX(hname,zone2_low, zone2_high);



  //for PhoISO

  // sprintf(hname,"h_IsovsBDT_%d_%d_%d_1_1",ebee, jetbin, ptbin);  
  // hqcd = (TH2F*)fqcd->Get(hname);
  // sprintf(hname,"h_IsovsBDT_%d_%d_%d_1_1",ebee, jetbin, ptbin);  
  // hqcd->Add((TH2F*)fqcd->Get(hname));
  // sprintf(hname,"h_IsovsBDT_%d_%d_%d_1_1",ebee, jetbin, ptbin);  
  // hqcd->Add((TH2F*)fqcd->Get(hname));

  // sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_1",ebee, jetbin, ptbin);  
  // hgjet = (TH2F*)fgjet->Get(hname);
  // hdata = (TH2F*)fdata->Get(hname);
  // sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_1",ebee, jetbin, ptbin);  
  // hgjet->Add((TH2F*)fgjet->Get(hname));
  // hdata->Add((TH2F*)fdata->Get(hname));
  // sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_1",ebee, jetbin, ptbin);  
  // hgjet->Add((TH2F*)fgjet->Get(hname));
  // hdata->Add((TH2F*)fdata->Get(hname)); 

  // //if EB phoIsoRaw
  // zone1_high=5;
  // //for phoIso SB
  // if(ebee==0) {
  //   zone2_low = 8;
  //   zone2_high = 16;
  // }else{
  //   zone2_low = 8;
  //   zone2_high = 20;
  // }    
  // sprintf(hname,"gjet_%d_%d_px1_phoIso",ebee, jetbin, ptbin);
  // TH1F *h_gjet_zone1_phoIso = (TH1F*)hgjet->ProjectionX(hname,zone1_low, zone1_high);
  // sprintf(hname,"gjet_%d_%d_px2_phoIso",ebee, jetbin, ptbin);
  // TH1F *h_gjet_zone2_phoIso = (TH1F*)hgjet->ProjectionX(hname,zone2_low, zone2_high);
  // sprintf(hname,"qcd_%d_%d_px1_phoIso",ebee, jetbin, ptbin);
  // TH1F *h_qcd_zone1_phoIso = (TH1F*)hqcd->ProjectionX(hname,zone1_low, zone1_high);
  // sprintf(hname,"qcd_%d_%d_px2_phoIso",ebee, jetbin, ptbin);
  // TH1F *h_qcd_zone2_phoIso = (TH1F*)hqcd->ProjectionX(hname,zone2_low, zone2_high);
  // sprintf(hname,"data_%d_%d_px1_phoIso",ebee, jetbin, ptbin);
  // TH1F *h_data_zone1_phoIso = (TH1F*)hdata->ProjectionX(hname,zone1_low, zone1_high);
  // sprintf(hname,"data_%d_%d_px2_phoIso",ebee, jetbin, ptbin);
  // TH1F *h_data_zone2_phoIso = (TH1F*)hdata->ProjectionX(hname,zone2_low, zone2_high);



  if(ptbin==13 && rebinoption==1){
    h_qcd_zone1->SetBinContent(89,0.);
    h_qcd_zone1->SetBinError(89,0.);
    h_qcd_zone1->SetBinContent(90,0.);
    h_qcd_zone1->SetBinError(90,0.);
  }

  TCanvas *c2 = new TCanvas("c2","",1500,500);
  c2->Divide(3,1);
  c2->cd(1);
  gPad->SetLogy();
  //h_gjet_zone1->SetMinimum(h_gjet_zone1->GetMinimum()*0.1);
  h_gjet_zone1->Draw();
  h_gjet_zone2->SetLineColor(2);
  h_gjet_zone2->Draw("same");
  printf("sig faction of SB/all  = %f \n", h_gjet_zone2->Integral()/(hgjet->Integral()));
  printf("sig faction of sig/all = %f \n", h_gjet_zone1->Integral()/(hgjet->Integral()));
  printf("sig fit correction       %f \n",h_gjet_zone1->Integral()/(hgjet->Integral())- h_gjet_zone2->Integral()/(hgjet->Integral()));
  c2->cd(2);
  //gPad->SetLogy();
  //h_qcd_zone1->SetMinimum(h_qcd_zone2->GetMinimum()*0.1);
  h_qcd_zone1->Scale(1./h_qcd_zone1->Integral());
  h_qcd_zone2->Scale(1./h_qcd_zone2->Integral());

  float ymax = h_qcd_zone1->GetMaximum();
  if(h_qcd_zone2->GetMaximum()>ymax) ymax = h_qcd_zone2->GetMaximum();
  h_qcd_zone1->SetMaximum(ymax*1.2);				       

  h_qcd_zone1->Draw();
  h_qcd_zone2->SetLineColor(2);
  h_qcd_zone2->Draw("same");
  
  printf("zone1 sig faction of left / right = %f \n", h_qcd_zone1->Integral(1,nbinx/2.)/h_qcd_zone1->Integral(nbinx/2+1,nbinx));
  printf("zone2 SB  faction of left / right = %f \n", h_qcd_zone2->Integral(1,nbinx/2.)/h_qcd_zone2->Integral(nbinx/2+1,nbinx));

 
  c2->cd(3);
  //gPad->SetLogy();
  //h_data_zone1->SetMinimum(h_data_zone2->GetMinimum()*0.1);
  ymax = h_data_zone1->GetMaximum();
  if(h_data_zone2->GetMaximum()>ymax) ymax = h_data_zone2->GetMaximum();
  h_data_zone1->SetMaximum(ymax*1.2);
  h_data_zone1->SetMinimum(0.);
				       
  h_data_zone1->Draw();
  h_data_zone2->SetLineColor(2);
  h_data_zone2->Draw("same");
  printf("Data faction of SB/all = %f \n", h_data_zone2->Integral()/(hdata->Integral()));
  printf("Data faction of sig/all = %f \n", h_data_zone1->Integral()/(hdata->Integral()));


  if(rebinoption==1){
    TFile *fout = new TFile("isovsbdt.root","recreate");
    h_gjet_zone1->Write();
    h_gjet_zone2->Write();
    h_qcd_zone1->Write();
    h_qcd_zone2->Write();
    h_data_zone1->Write();
    h_data_zone2->Write();
    
    // h_gjet_zone1_phoIso->Write();
    // h_gjet_zone2_phoIso->Write();
    // h_qcd_zone1_phoIso->Write();
    // h_qcd_zone2_phoIso->Write();
    // h_data_zone1_phoIso->Write();
    // h_data_zone2_phoIso->Write();
    hgjet_all->Write();
    hdata_all->Write();
    hqcd_all->Write();
    fout->Close();
  }

}

void Draw_Isoeff(){
  
  // float ptcut[30] = {22, 30, 36, 50, 75, 90, 105,  120, 135, 150, 165, 175, 185,
  //                    190, 200, 220, 250, 300, 350, 400, 500, 750, 1000, 1500, 2000, 3000, 10000};

  float ptcut[30] = {25, 34, 40, 55, 70, 85, 100,  115, 135, 155, 175, 190,
    200, 220, 250, 300, 350, 400, 500, 750, 1000, 1500, 2000, 3000, 10000};

  int nbin=22;
  TH1F *h_EB_pass  = new TH1F("h_EB_pass" ,"",nbin,ptcut);
  TH1F *h_EB_total = new TH1F("h_EB_total","",nbin,ptcut);
  TH1F *h_EE_pass  = new TH1F("h_EE_pass" ,"",nbin,ptcut);
  TH1F *h_EE_total = new TH1F("h_EE_total","",nbin,ptcut);



  TFile *f = new TFile("isovsbdt_template_noxsweight.root");
  TH1F *h1;
  TH1F *htotal;
  char hname[100];
  for(int ii=0; ii<22; ii++){
    int ebeebin=0;
    //correct signal efficiency
    sprintf(hname,"gjet_%d_%d_%d_px1_chIso", ebeebin, 2, ii);
    h1=(TH1F*)f->Get(hname);
    sprintf(hname,"gjet_all_%d_%d_%d", ebeebin, 2, ii);
    htotal=(TH1F*)f->Get(hname);

    float sigeff = h1->Integral()/htotal->Integral();
    printf("bin %d, chIso signal eff %f \n", ii, sigeff);
    
    h_EB_pass->SetBinContent(ii+1,h1->Integral());
    h_EB_total->SetBinContent(ii+1,htotal->Integral());
    //--------------
    ebeebin=1;
    //correct signal efficiency
    sprintf(hname,"gjet_%d_%d_%d_px1_chIso", ebeebin, 2, ii);
    h1=(TH1F*)f->Get(hname);
    sprintf(hname,"gjet_all_%d_%d_%d", ebeebin, 2, ii);
    htotal=(TH1F*)f->Get(hname);
    
    h_EE_pass->SetBinContent(ii+1,h1->Integral());
    h_EE_total->SetBinContent(ii+1,htotal->Integral());    
    
  }
  
  TGraphAsymmErrors *tgrs_EB = new TGraphAsymmErrors();
  TGraphAsymmErrors *tgrs_EE = new TGraphAsymmErrors();
  
  // tgrs_EB->Divide(h_EB_pass,h_EB_total,"cl=0.683 b(1,1) mode");
  // tgrs_EE->Divide(h_EE_pass,h_EE_total,"cl=0.683 b(1,1) mode");
  tgrs_EB->Divide(h_EB_pass,h_EB_total);
  tgrs_EE->Divide(h_EE_pass,h_EE_total);

  // printf(" 195, %f / %f =  %f \n", h_EB_pass->GetBinContent(14), 
  // 	 h_EB_total->GetBinContent(14), tgrs_EB->Eval(195));
  
  // h_EB_total->Draw();
  // h_EB_pass->Draw("same");
  // return;


  TCanvas *c1 = new TCanvas("c1","",600,600);
  c1->Draw();
  
  TH2F *h2 = new TH2F("h2","",100, 150, 1000, 100, 0.9, 1.);
  h2->SetNdivisions(505,"XY");
  h2->SetXTitle("photon pt (GeV)");
  h2->SetYTitle("efficiency");
  h2->Draw();

  tgrs_EB->SetMarkerStyle(8);
  tgrs_EE->SetMarkerStyle(26);
  tgrs_EE->SetLineColor(4);
  tgrs_EE->SetMarkerColor(4);

  tgrs_EB->Draw("lpe same");
  tgrs_EE->Draw("lpe same");

  TLegend *tleg = new TLegend(0.3, 0.6, 0.9, 0.9);
  tleg->SetHeader("ch. Iso cut efficiency");
  tleg->SetFillStyle(0);
  tleg->SetShadowColor(0);
  tleg->SetBorderSize(0);  
  tleg->AddEntry(tgrs_EB,"EB charged ISO < 1.5 GeV","pel");
  tleg->AddEntry(tgrs_EE,"EE charged ISO < 2.0 GeV","pel");

  tleg->Draw();

  gPad->RedrawAxis();

}


void Draw_2d(){
  
  TChain *tc_signal = new TChain("t");
  tc_signal->Add("../output_job_fall15_gjet_pt*MGG*miniAOD.root");
  TChain *tc_qcd = new TChain("t");
  //tc_qcd->Add("../output_job_fall15_gjet_pt*MGG*miniAOD.root");
  tc_qcd->Add("../qcd/qcd.root");

  TCanvas *c1 = new TCanvas("c1","",1200,600);
  c1->Divide(2,1);

  c1->cd(1);
  gPad->SetRightMargin(0.12);
  TH2F *h2signal = new TH2F("h2signal","",20, -1., 1., 15, 0., 15.);
  h2signal->Sumw2();
  h2signal->SetXTitle("BDT");
  h2signal->SetYTitle("charged Isolation");
  tc_signal->Draw("chIsoRaw:mva >>h2signal","xsweight*puwei*(isMatched==1&&chWorstRaw<15&&HoverE<0.05)","colz");
  h2signal->Scale(1./h2signal->GetMaximum());
  h2signal->Draw("colz");
    
  
  c1->cd(2);
  gPad->SetRightMargin(0.12);
  TH2F *h2qcd = new TH2F("h2qcd","",20, -1., 1., 15, 0., 15.);
  h2qcd->Sumw2();
  h2qcd->SetXTitle("BDT");
  h2qcd->SetYTitle("charged Isolation");
  tc_qcd->Draw("chIsoRaw:mva >>h2qcd","xsweight*puwei*(isMatched!=1&&chWorstRaw<15&&HoverE<0.05)","colz");
  h2qcd->Scale(1./h2qcd->GetMaximum());
  h2qcd->Draw("colz");

  printf("signal %f %f \n", h2signal->GetCorrelationFactor(), h2signal->GetCovariance());
  printf("qcd %f %f \n", h2qcd->GetCorrelationFactor(), h2qcd->GetCovariance());


  

  TCanvas *c2 = new TCanvas("c2","",1200,600);
  c2->Divide(2,1);
  c2->cd(1);
  gPad->SetRightMargin(0.12);
  TProfile *prof1 = (TProfile*)h2signal->ProfileX("prof1");
  prof1->Draw("pe");
  c2->cd(2);
  gPad->SetRightMargin(0.12);
  TProfile *prof2 = (TProfile*)h2qcd->ProfileX("prof2");
  prof2->Draw("pe");

  TCanvas *c3 = new TCanvas("c3","",1200,600);
  c3->Divide(2,1);
  c3->cd(1);
  gPad->SetRightMargin(0.12);
  TH1F *proj1 = (TH1F*)h2signal->ProjectionX("proj1");
  proj1->Draw("pe");
  c3->cd(2);
  gPad->SetRightMargin(0.12);
  TH1F *proj2 = (TH1F*)h2qcd->ProjectionX("proj2");
  proj2->Draw("pe");

}
