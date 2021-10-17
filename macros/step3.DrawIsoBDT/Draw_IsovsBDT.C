#include <iostream>
#include <stdio.h>

#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
// target : 
//    input data / sigMC / bkgMC and return binning histogram with all and sideband BDT distribution.
//    which all distribution is 2D histogram. But sideband is 1D.

std::vector<float> ptbin_ranges()
{
  // for 2016
  //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,100000}; // size = 16. ptbin = [0,15]
  std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
  return vec_ptcut;
}
struct VARList
{
    enum vars
    {
        deepCSVTags_b,
        deepCSVTags_bb,
        deepCSVTags_c,
        deepCSVTags_udsg,
        deepFlavourTags_b,
        deepFlavourTags_c,
        deepFlavourTags_g,
        deepFlavourTags_lepb,
        deepFlavourTags_bb,
        deepFlavourTags_uds,
        deepCSVDiscriminatorTags_BvsAll,
        deepCSVDiscriminatorTags_CvsB,
        deepCSVDiscriminatorTags_CvsL,
        subVtxMass,
        totvars
    };
    std::vector<const char*> histnames;

    VARList() : histnames(totvars)
    {
        histnames[deepCSVTags_b]                      = "deepCSVTags_b";                   
        histnames[deepCSVTags_bb]                     = "deepCSVTags_bb";
        histnames[deepCSVTags_c]                      = "deepCSVTags_c";
        histnames[deepCSVTags_udsg]                   = "deepCSVTags_udsg";
        histnames[deepFlavourTags_b]                  = "deepFlavourTags_b";
        histnames[deepFlavourTags_c]                  = "deepFlavourTags_c";
        histnames[deepFlavourTags_g]                  = "deepFlavourTags_g";
        histnames[deepFlavourTags_lepb]               = "deepFlavourTags_lepb";
        histnames[deepFlavourTags_bb]                 = "deepFlavourTags_bb";
        histnames[deepFlavourTags_uds]                = "deepFlavourTags_uds";
        histnames[deepCSVDiscriminatorTags_BvsAll]    = "deepCSVDiscriminatorTags_BvsAll";
        histnames[deepCSVDiscriminatorTags_CvsB]      = "deepCSVDiscriminatorTags_CvsB";
        histnames[deepCSVDiscriminatorTags_CvsL]      = "deepCSVDiscriminatorTags_CvsL";
        histnames[subVtxMass]                         = "subVtxMass";
    }
};

// jetbin = 0 : barrel jet
// jetbin = 1 : endcap jet
// jetbin = 2 : inclusive photon. So it sums up all jetbins.
/*
TH2F* GetSigHistFromFile_General(TFile* infile, const char* varname,
        int ebee, int jetbin, int ptbin, int IsoOption )
{
    TH2F* hist;
    char hname[200];
    //sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, jetbin, ptbin, IsoOption);  
    sprintf(hname,"%s_%d_%d_%d_0_%d", varname, ebee, jetbin, ptbin, IsoOption);  
    hist = (TH2F*)infile->Get(hname);
    if ( jetbin == 0 || jetbin == 1 ) return hist;
    
    while ( jetbin-- )
    {
        //sprintf(hname,"h_IsovsBDT_%d_%d_%d_0_%d",ebee, jetbin, ptbin, IsoOption);  
        sprintf(hname,"%s_%d_%d_%d_0_%d", varname, ebee, jetbin, ptbin, IsoOption);  
        hist->Add( (TH2F*)infile->Get(hname) );
    }
    return hist;

}
TH2F* GetBkgHistFromFile_General(TFile* infile, const char* varname,
        int ebee, int jetbin, int ptbin, int IsoOption )
{
    TH2F* hist;
    char hname[200];
    //sprintf(hname,"h_IsovsBDT_%d_%d_%d_1_%d",ebee, jetbin, ptbin, IsoOption);  
    sprintf(hname,"%s_%d_%d_%d_1_%d", varname, ebee, jetbin, ptbin, IsoOption);  
    hist = (TH2F*)infile->Get(hname);
    if ( jetbin == 0 || jetbin == 1 ) return hist;
    
    while ( jetbin-- )
    {
        //sprintf(hname,"h_IsovsBDT_%d_%d_%d_1_%d",ebee, jetbin, ptbin, IsoOption);  
        sprintf(hname,"%s_%d_%d_%d_1_%d", varname, ebee, jetbin, ptbin, IsoOption);  
        hist->Add( (TH2F*)infile->Get(hname) );
    }
    return hist;

}
*/
TH2F* GetHistFromFile_General(TFile* infile, const char* varname, int isBkg,
        int ebee, int jetbin, int ptbin )
{
    TH2F* hist;
    char hname[200];
    sprintf(hname,"%s_%d_%d_%d_%d", varname, ebee, jetbin, ptbin, isBkg);  
    hist = (TH2F*)infile->Get(hname);
    if ( jetbin == 0 || jetbin == 1 ) return hist;
    
    while ( jetbin-- )
    {
        sprintf(hname,"%s_%d_%d_%d_%d", varname, ebee, jetbin, ptbin, isBkg);
        hist->Add( (TH2F*)infile->Get(hname) );
    }
    return hist;

}
TH2F* GetHistFromFile_IsovsBDT(TFile* infile, int isBkg,
        int ebee, int jetbin, int ptbin, int IsoOption )
{
    TH2F* hist;
    char hname[200];
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_%d_%d", ebee, jetbin, ptbin, isBkg, IsoOption);  
    hist = (TH2F*)infile->Get(hname);
    if ( jetbin == 0 || jetbin == 1 ) return hist;
    
    while ( jetbin-- )
    {
        sprintf(hname,"h_IsovsBDT_%d_%d_%d_%d_%d", ebee, jetbin, ptbin, isBkg, IsoOption);  
        hist->Add( (TH2F*)infile->Get(hname) );
    }
    return hist;

}
TH2F* GetSigHistFromFile(TFile* infile,
        int ebee, int jetbin, int ptbin, int IsoOption )
{ return GetHistFromFile_IsovsBDT(infile,     0, ebee, jetbin, ptbin, IsoOption); }
TH2F* GetBkgHistFromFile(TFile* infile,
        int ebee, int jetbin, int ptbin, int IsoOption )
{ return GetHistFromFile_IsovsBDT(infile,     1, ebee, jetbin, ptbin, IsoOption); }
TH2F* GetSigVarHistFromFile(TFile* infile, const char* var,
        int ebee, int jetbin, int ptbin )
{ return GetHistFromFile_General(infile, var, 0, ebee, jetbin, ptbin); }
TH2F* GetBkgVarHistFromFile(TFile* infile, const char* var,
        int ebee, int jetbin, int ptbin )
{ return GetHistFromFile_General(infile, var, 1, ebee, jetbin, ptbin); }

const char* GetQCD_madgraph()
{ return "../step2.makehistos/storeroot/makehisto_QCD_madgraph.root"; }
const char* GetData()
{ return "../step2.makehistos/storeroot/makehisto_data.root"; }
const char* GetSig_madgraph()
{ return "../step2.makehistos/storeroot/makehisto_sig_madgraph.root"; }
const char* FakeDataSample(int opt)
{
    switch ( opt )
    {
        case -100: return "../step2.makehistos/storeroot/makehisto_fakedata0.root";
        case -101: return "../step2.makehistos/storeroot/makehisto_fakedata1.root";
        case -102: return "../step2.makehistos/storeroot/makehisto_fakedata2.root";
        case -103: return "../step2.makehistos/storeroot/makehisto_fakedata3.root";
        case -104: return "../step2.makehistos/storeroot/makehisto_fakedata4.root";
        case -105: return "../step2.makehistos/storeroot/makehisto_fakedata5.root";
        case -106: return "../step2.makehistos/storeroot/makehisto_fakedata6.root";
        case -107: return "../step2.makehistos/storeroot/makehisto_fakedata7.root";
        case -108: return "../step2.makehistos/storeroot/makehisto_fakedata8.root";
        case -109: return "../step2.makehistos/storeroot/makehisto_fakedata9.root";
    }
    char mesg[200];
    sprintf( mesg, "FakeDataSample() : Input argument %d is invalid\n", opt );
    throw std::range_error(mesg);
    return "";
    }


enum fileid
{ data, sigmadgraph, qcdmadgraph };

const char* GetFile( int fileopt )
{
    switch ( fileopt )
    {
        case fileid::data        : return GetData();
        case fileid::sigmadgraph : return GetSig_madgraph();
        case fileid::qcdmadgraph : return GetQCD_madgraph();

        default: return FakeDataSample(fileopt);
    }
    char mesg[200];
    sprintf( mesg, "GetFile() : Input argument %d is invalid\n", fileopt );
    throw std::range_error(mesg);
    return "";
}




int mainfunc(int ebee=0, int jetbin=0, int ptbin=14, int rebinoption=5, int sb1=14, int sb2=20, const char* datafilename=""){
  TFile *fdata = TFile::Open( datafilename                 );
  
  TFile *fqcd  = TFile::Open( GetFile(fileid::qcdmadgraph) );
  TFile *fgjet = TFile::Open( GetFile(fileid::sigmadgraph) );
  fqcd->Print();
  char hname[100];
  // int ebee=0;
  // if(strcmp(EBEE,"EE")==0) ebee=1;

  int IsoOption=0; //0 chIso, 1 phoIso, 2 combIso, 3 chWorst
  TH2F *hgjet = (TH2F*) GetSigHistFromFile( fgjet, ebee, jetbin, ptbin, IsoOption );
  TH2F *hdata = (TH2F*) GetSigHistFromFile( fdata, ebee, jetbin, ptbin, IsoOption );
  TH2F *hqcd  = (TH2F*) GetBkgHistFromFile( fqcd , ebee, jetbin, ptbin, IsoOption );

  VARList fitvars;
  std::vector<TH2F*> gjet_fithists(VARList::totvars, nullptr);
  std::vector<TH2F*> data_fithists(VARList::totvars, nullptr);
  std::vector<TH2F*>  qcd_fithists(VARList::totvars, nullptr);
  for ( int varidx = 0; varidx < VARList::totvars; ++varidx )
  {
      char vartemplate[100];
      sprintf(vartemplate,"fitVars/h_%s",fitvars.histnames[varidx]);
      gjet_fithists[varidx] = (TH2F*) GetSigVarHistFromFile( fgjet, vartemplate, ebee, jetbin, ptbin )->Clone();
      data_fithists[varidx] = (TH2F*) GetSigVarHistFromFile( fdata, vartemplate, ebee, jetbin, ptbin )->Clone();
       qcd_fithists[varidx] = (TH2F*) GetBkgVarHistFromFile( fqcd , vartemplate, ebee, jetbin, ptbin )->Clone();
  }

  

  TH2F* hgjet_all = (TH2F*) hgjet->Clone();
  TH2F* hqcd_all =  (TH2F*) hqcd->Clone();
  TH2F* hdata_all = (TH2F*) hdata->Clone(); 
  
  sprintf(hname,"gjet_all_%d_%d_%d",ebee, jetbin, ptbin, IsoOption);  
  hgjet_all->SetName(hname);
  sprintf(hname,"qcd_all_%d_%d_%d",ebee, jetbin, ptbin, IsoOption);  
  hqcd_all->SetName(hname);
  sprintf(hname,"data_all_%d_%d_%d",ebee, jetbin, ptbin, IsoOption);  
  hdata_all->SetName(hname);

  std::vector<TH2F*> gjet_all_fithists(VARList::totvars, nullptr);
  std::vector<TH2F*> data_all_fithists(VARList::totvars, nullptr);
  std::vector<TH2F*>  qcd_all_fithists(VARList::totvars, nullptr);
  for ( int varidx = 0; varidx < VARList::totvars; ++varidx )
  {
      char vartemplate[100];
      sprintf(vartemplate,"%s_%s_%d_%d_%d","gjet_all",fitvars.histnames[varidx], ebee, jetbin, ptbin);
      gjet_all_fithists[varidx] = (TH2F*) gjet_fithists[varidx]->Clone();  gjet_all_fithists[varidx]->SetName(vartemplate);
      sprintf(vartemplate,"%s_%s_%d_%d_%d","data_all",fitvars.histnames[varidx], ebee, jetbin, ptbin);
      data_all_fithists[varidx] = (TH2F*) data_fithists[varidx]->Clone();  data_all_fithists[varidx]->SetName(vartemplate);
      sprintf(vartemplate,"%s_%s_%d_%d_%d","qcd_all" ,fitvars.histnames[varidx], ebee, jetbin, ptbin);
       qcd_all_fithists[varidx] = (TH2F*)  qcd_fithists[varidx]->Clone();   qcd_all_fithists[varidx]->SetName(vartemplate);
  }


  Printf("data %.0f, signal %.2f, bkg %.2f \n", hdata->Integral(), hgjet->Integral(), hqcd->Integral());

  hqcd->Rebin2D(rebinoption,2);
  hgjet->Rebin2D(rebinoption,2);
  hdata->Rebin2D(rebinoption,2);
  for ( int varidx = 0; varidx < VARList::totvars; ++varidx )
  {
      gjet_fithists[varidx]->Rebin2D(rebinoption,2);
      data_fithists[varidx]->Rebin2D(rebinoption,2);
       qcd_fithists[varidx]->Rebin2D(rebinoption,2);
  }

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
  //if(ebee>=2) { //EE
  if(ebee) { //EE
    if(IsoOption==0) zone1_high=3;
    else if(IsoOption==1) zone1_high=5;
    else if(IsoOption==2) zone1_high=7;
    else if(IsoOption==3) zone1_high=6;
  }

  int zone2_low = sb1;
  int zone2_high = sb2;
  //for production 
  //if(ebee<=1) {zone2_low=14; zone2_high=26;} //EB
  //else {zone2_low=12; zone2_high=24;}
  if(ebee<=1) {zone2_low=7; zone2_high=20;} //EB
  //else if(ebee==2) {zone2_low=7; zone2_high=20;}
  else {zone2_low=6; zone2_high=20;}
 
  
  //for chIso SB
  sprintf(hname,"gjet_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
  TH1D *h_gjet_zone1 = (TH1D*)hgjet->ProjectionX(hname,zone1_low, zone1_high);
  sprintf(hname,"gjet_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
  TH1D *h_gjet_zone2 = (TH1D*)hgjet->ProjectionX(hname,zone2_low, zone2_high);
  sprintf(hname,"qcd_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
  TH1D *h_qcd_zone1 = (TH1D*)hqcd->ProjectionX(hname,zone1_low, zone1_high);
  sprintf(hname,"qcd_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
  TH1D *h_qcd_zone2 = (TH1D*)hqcd->ProjectionX(hname,zone2_low, zone2_high);
  sprintf(hname,"data_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
  TH1D *h_data_zone1 = (TH1D*)hdata->ProjectionX(hname,zone1_low, zone1_high);
  sprintf(hname,"data_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
  TH1D *h_data_zone2 = (TH1D*)hdata->ProjectionX(hname,zone2_low, zone2_high);

  std::vector<TH1D*> gjet_zone1_fithists(VARList::totvars, nullptr);
  std::vector<TH1D*> data_zone1_fithists(VARList::totvars, nullptr);
  std::vector<TH1D*>  qcd_zone1_fithists(VARList::totvars, nullptr);
  std::vector<TH1D*> gjet_zone2_fithists(VARList::totvars, nullptr);
  std::vector<TH1D*> data_zone2_fithists(VARList::totvars, nullptr);
  std::vector<TH1D*>  qcd_zone2_fithists(VARList::totvars, nullptr);
  for ( int varidx = 0; varidx < VARList::totvars; ++varidx )
  {
      char vartemplate[100];
      sprintf(vartemplate,"%s_%s_%d_%d_%d_px1","gjet",fitvars.histnames[varidx], ebee, jetbin, ptbin);
      gjet_zone1_fithists[varidx] = (TH1D*)gjet_fithists[varidx]->ProjectionX(vartemplate, zone1_low, zone1_high);
      sprintf(vartemplate,"%s_%s_%d_%d_%d_px1","data",fitvars.histnames[varidx], ebee, jetbin, ptbin);
      data_zone1_fithists[varidx] = (TH1D*)data_fithists[varidx]->ProjectionX(vartemplate, zone1_low, zone1_high);
      sprintf(vartemplate,"%s_%s_%d_%d_%d_px1","qcd" ,fitvars.histnames[varidx], ebee, jetbin, ptbin);
       qcd_zone1_fithists[varidx] = (TH1D*) qcd_fithists[varidx]->ProjectionX(vartemplate, zone1_low, zone1_high);
  }
  for ( int varidx = 0; varidx < VARList::totvars; ++varidx )
  {
      char vartemplate[100];
      sprintf(vartemplate,"%s_%s_%d_%d_%d_px2","gjet",fitvars.histnames[varidx], ebee, jetbin, ptbin);
      gjet_zone2_fithists[varidx] = (TH1D*)gjet_fithists[varidx]->ProjectionX(vartemplate, zone2_low, zone2_high);
      sprintf(vartemplate,"%s_%s_%d_%d_%d_px2","data",fitvars.histnames[varidx], ebee, jetbin, ptbin);
      data_zone2_fithists[varidx] = (TH1D*)data_fithists[varidx]->ProjectionX(vartemplate, zone2_low, zone2_high);
      sprintf(vartemplate,"%s_%s_%d_%d_%d_px2","qcd" ,fitvars.histnames[varidx], ebee, jetbin, ptbin);
       qcd_zone2_fithists[varidx] = (TH1D*) qcd_fithists[varidx]->ProjectionX(vartemplate, zone2_low, zone2_high);
  }


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
  // TH1D *h_gjet_zone1_phoIso = (TH1D*)hgjet->ProjectionX(hname,zone1_low, zone1_high);
  // sprintf(hname,"gjet_%d_%d_px2_phoIso",ebee, jetbin, ptbin);
  // TH1D *h_gjet_zone2_phoIso = (TH1D*)hgjet->ProjectionX(hname,zone2_low, zone2_high);
  // sprintf(hname,"qcd_%d_%d_px1_phoIso",ebee, jetbin, ptbin);
  // TH1D *h_qcd_zone1_phoIso = (TH1D*)hqcd->ProjectionX(hname,zone1_low, zone1_high);
  // sprintf(hname,"qcd_%d_%d_px2_phoIso",ebee, jetbin, ptbin);
  // TH1D *h_qcd_zone2_phoIso = (TH1D*)hqcd->ProjectionX(hname,zone2_low, zone2_high);
  // sprintf(hname,"data_%d_%d_px1_phoIso",ebee, jetbin, ptbin);
  // TH1D *h_data_zone1_phoIso = (TH1D*)hdata->ProjectionX(hname,zone1_low, zone1_high);
  // sprintf(hname,"data_%d_%d_px2_phoIso",ebee, jetbin, ptbin);
  // TH1D *h_data_zone2_phoIso = (TH1D*)hdata->ProjectionX(hname,zone2_low, zone2_high);



  // ??? asdf need to be remove!
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
  printf("sig fraction of %d %d SB/all  = %f \n", ptbin, ebee, h_gjet_zone2->Integral()/(hgjet->Integral()));
  printf("sig fraction of %d %d sig/all = %f \n", ptbin, ebee, h_gjet_zone1->Integral()/(hgjet->Integral()));
  printf("sig fit correction       %f \n",h_gjet_zone1->Integral()/(hgjet->Integral())- h_gjet_zone2->Integral()/(hgjet->Integral()));
  {
  c2->cd(2);
  //gPad->SetLogy();
  //h_qcd_zone1->SetMinimum(h_qcd_zone2->GetMinimum()*0.1);
  // h_qcd_zone1->Scale(1./h_qcd_zone1->Integral());
  // h_qcd_zone2->Scale(1./h_qcd_zone2->Integral());

  float ymax = h_qcd_zone1->GetMaximum();
  if(h_qcd_zone2->GetMaximum()>ymax) ymax = h_qcd_zone2->GetMaximum();
  h_qcd_zone1->SetMaximum(ymax*1.2);				       

  h_qcd_zone1->Draw();
  h_qcd_zone2->SetLineColor(2);
  h_qcd_zone2->Draw("same");
  
  printf("zone1 sig faction of left / right = %f \n", h_qcd_zone1->Integral(1,nbinx/2.)/h_qcd_zone1->Integral(nbinx/2+1,nbinx));
  printf("zone2 SB  faction of left / right = %f \n", h_qcd_zone2->Integral(1,nbinx/2.)/h_qcd_zone2->Integral(nbinx/2+1,nbinx));

  }
 
  {
  c2->cd(3);
  //gPad->SetLogy();
  //h_data_zone1->SetMinimum(h_data_zone2->GetMinimum()*0.1);
  float ymax = h_data_zone1->GetMaximum();
  if(h_data_zone2->GetMaximum()>ymax) ymax = h_data_zone2->GetMaximum();
  h_data_zone1->SetMaximum(ymax*1.2);
  h_data_zone1->SetMinimum(0.);
				       
  h_data_zone1->Draw();
  h_data_zone2->SetLineColor(2);
  h_data_zone2->Draw("same");
  printf("Data faction of SB/all = %f \n", h_data_zone2->Integral()/(hdata->Integral()));
  printf("Data faction of sig/all = %f \n", h_data_zone1->Integral()/(hdata->Integral()));
  }


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

    TDirectory* outdir = (TDirectory*) fout->mkdir("fitVars");
    outdir->cd();
    for ( auto iter : gjet_all_fithists ) iter->Write();
    for ( auto iter : data_all_fithists ) iter->Write();
    for ( auto iter :  qcd_all_fithists ) iter->Write();
    for ( auto iter : gjet_zone1_fithists ) iter->Write();
    for ( auto iter : data_zone1_fithists ) iter->Write();
    for ( auto iter :  qcd_zone1_fithists ) iter->Write();
    for ( auto iter : gjet_zone2_fithists ) iter->Write();
    for ( auto iter : data_zone2_fithists ) iter->Write();
    for ( auto iter :  qcd_zone2_fithists ) iter->Write();

    fout->Close();
  }

  return 0;
}

void Draw_Isoeff(){
  std::vector<float> vec_ptcut = ptbin_ranges();
  float* ptcut = &vec_ptcut.front();
  
  int nbin=vec_ptcut.size();
  TH1F *h_EB_pass  = new TH1F("h_EB_pass" ,"",nbin,ptcut);
  TH1F *h_EB_total = new TH1F("h_EB_total","",nbin,ptcut);
  TH1F *h_EE_pass  = new TH1F("h_EE_pass" ,"",nbin,ptcut);
  TH1F *h_EE_total = new TH1F("h_EE_total","",nbin,ptcut);



  TFile *f = new TFile("isovsbdt_template_noxsweight.root");
  TH1F *h1;
  TH1F *htotal;
  char hname[100];
  for(int ii=13; ii<nbin; ii++){
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
void Draw_IsovsBDT(int ebee=0, int jetbin=0, int ptbin=14, int rebinoption=5, int sb1=14, int sb2=20, int fakefileidx=0){
    int fileID = fileid::data;
    if ( fakefileidx != 0 ) fileID = fakefileidx; // Use data or fake sample.
    const char* filename = GetFile(fileID);

    mainfunc(ebee,jetbin,ptbin,rebinoption,sb1,sb2, filename);
}
void Draw_IsovsBDT(const char* ifilename, int ebee=0, int jetbin=0, int ptbin=14, int rebinoption=5, int sb1=14, int sb2=20){
    mainfunc(ebee,jetbin,ptbin,rebinoption,sb1,sb2, ifilename);
}
