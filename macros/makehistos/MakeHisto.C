#define MakeHisto_cxx
#include "MakeHisto.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TMath.h>
#include <iostream>
#include <TLorentzVector.h>

void MakeHisto::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L MakeHisto.C
  //      Root > MakeHisto t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  TRandom3 *trd = new TRandom3();
  //int netabin=14;
  int netabin=4;

  TFile *fout = new TFile("output.root","recreate");

  TH1F *h_BDT_all[netabin][3][30][2]; //ebee, jetbin, ptbin, true/fake;
  TH1F *h_BDT[netabin][3][30][2];

  //TH1F *h_BDTvar[20][netabin][30][2]; // var, ebee, ptbin, true/fake;

  TH1F *h_Pt_all[netabin][3][30][2];
  TH1F *h_Pt[netabin][2];
  TH1F *h_Ptspec[netabin][2];
  TH1F *h_Wmn_mt[netabin][2];

  TH2F *h_IsovsBDT[netabin][3][30][2][4]; //ebee,jetbin, ptbin, truth/fake, isovar;


  //printf("eta bins %d \n", 8);
  char txt[100];
  char hname[100];
  
  map<int, char*> varname;
  float var_lowx[20];
  float var_highx[20];
  varname[0] = "recoPhi"; var_lowx[0]=-3.2, var_highx[0]=3.2;
  varname[1] = "r9"; var_lowx[1]=0.5, var_highx[1]=1.05;;
  varname[2] = "e1x3Full5x5/e5x5Full5x5"; var_lowx[2]=0.2, var_highx[2]=1.05;
  varname[3] = "e2x2Full5x5/e5x5Full5x5"; var_lowx[3]=0.4, var_highx[3]=1.05;
  varname[4] = "e2x5Full5x5/e5x5Full5x5"; var_lowx[4]=0.4, var_highx[4]=1.05;
  varname[5] = "sieieFull5x5"; var_lowx[5]=0.00, var_highx[5]=0.05;
  varname[6] = "sieipFull5x5"; var_lowx[6]=-0.0002, var_highx[6]=0.0002;
  varname[7] = "recoSCEta"; var_lowx[7]=-2.5, var_highx[7]=2.5;
  varname[8] = "rawE"; var_lowx[8]=0., var_highx[8]=1000.;
  varname[9] = "scEtaWidth"; var_lowx[9]=0., var_highx[9]=0.06;
  varname[10] = "scPhiWidth"; var_lowx[10]=0., var_highx[10]=0.12;
  varname[11] = "phoIsoRaw"; var_lowx[11]=0., var_highx[11]=20.;
  varname[12] = "chIsoRaw"; var_lowx[12]=0., var_highx[12]=20.;
  varname[13] = "chWorstRaw"; var_lowx[13]=0., var_highx[13]=20.;
  varname[14] = "rho"; var_lowx[14]=0., var_highx[14]=40.;
  varname[15] = "photonIDmva"; var_lowx[15]=-1., var_highx[15]=1.;
  varname[16] = "esRR"; var_lowx[16]=0., var_highx[16]=15.;
  varname[17] = "esEn/rawE"; var_lowx[17]=0., var_highx[17]=0.6;
  varname[18] = "nVtx"; var_lowx[18]=0., var_highx[18]=50;
  //varname[] = ""; var_lowx[]=, var_highx[]=;

  // printf(" %s \n", varname.find(0)->second);
  // return;
  printf("define 1st set \n");
  // for(int ii=0; ii<20; ii++){
  //   for(int mm=0; mm<8; mm++){
  //     for(int jj=0; jj<30; jj++){
  //  	for(int kk=0; kk<2; kk++){	  
  //  	  sprintf(txt,"var %s EBEE_%d_ptbin_%d_true_%d",varname.find(ii)->second,mm,jj,kk);
  //  	  sprintf(hname,"h_BDTvar_%d_%d_%d_%d",ii,mm,jj,kk);
  //  	  if(ii!=5) h_BDTvar[ii][mm][jj][kk] = new TH1F(hname,txt,40, var_lowx[ii], var_highx[ii]);
  // 	  else h_BDTvar[ii][mm][jj][kk] = new TH1F(hname,txt,90, var_lowx[ii], var_highx[ii]);
	  
  // 	  printf("%d %d %d %d \n", ii, mm, jj, kk);
  //  	}
  //     }
  //   }
  // }
  
  for(int ii=0; ii<netabin; ii++){
    for(int kk=0; kk<2; kk++){
      sprintf(txt,"Wmass EBEE_%d_true_%d",ii,kk);
      sprintf(hname,"h_Wmn_mt_%d_%d",ii,kk);
      h_Wmn_mt[ii][kk] = new TH1F(hname,txt, 150, 0., 150.); 
    }
  }
  for(int ii=0; ii<netabin; ii++){
    for(int mm=0; mm<3; mm++){
      for(int jj=0; jj<30; jj++){
	for(int kk=0; kk<2; kk++){
	  sprintf(txt,"BDT all  EBEE_%d_Jet_%d_ptbin_%d_true_%d",ii,mm,jj,kk);
	  sprintf(hname,"h_BDT_all_%d_%d_%d_%d",ii,mm,jj,kk);
	  h_BDT_all[ii][mm][jj][kk] = new TH1F(hname,txt,100, -1., 1.);
	  sprintf(txt,"BDT selected EBEE_%d_Jet_%d_ptbin_%d_true_%d",ii,mm,jj,kk);
	  sprintf(hname,"h_BDT_%d_%d_%d_%d",ii,mm,jj,kk);
	  h_BDT[ii][mm][jj][kk] = new TH1F(hname,txt,100, -1., 1.);

	  for(int nn=0; nn<4; nn++){
	    sprintf(txt,"Iso vs BDT EBEE_%d_Jet_%d_ptbin_%d_true_%d_Iso_%d",ii,mm,jj,kk,nn);
	    sprintf(hname,"h_IsovsBDT_%d_%d_%d_%d_%d",ii,mm,jj,kk,nn);
	    h_IsovsBDT[ii][mm][jj][kk][nn] = new TH2F(hname,txt,100, -1., 1., 30, 0., 15);
	    //h_IsovsBDT[ii][mm][jj][kk][nn] = new TH2F(hname,txt,90, -0.8, 1., 30, 0., 15);
	    h_IsovsBDT[ii][mm][jj][kk][nn]->Sumw2();
	  }

	  sprintf(txt,"Pt all  EBEE_%d_Jet_%d_ptbin_%d_true_%d",ii,mm,jj,kk);
	  sprintf(hname,"h_Pt_all_%d_%d_%d_%d",ii,mm,jj,kk);
	  h_Pt_all[ii][mm][jj][kk] = new TH1F(hname,txt, 2000, 0., 2000.);
	  sprintf(txt,"Pt selected EBEE_%d_Jet_%d_ptbin_%d_true_%d",ii,mm,jj,kk);
	
	  h_BDT[ii][mm][jj][kk]->Sumw2(); 
	  h_Pt_all[ii][mm][jj][kk]->Sumw2();
	}
      }
    }
    for(int kk=0; kk<2; kk++){
      sprintf(txt,"Pt EBEE_%d_true_%d",ii,kk);
      sprintf(hname,"h_Pt_spec_%d_%d",ii,kk);
      h_Ptspec[ii][kk] = new TH1F(hname,txt, 200, 0., 2000.);
      h_Ptspec[ii][kk]->Sumw2();

      sprintf(hname,"h_Pt_%d_%d",ii,kk);
      h_Pt[ii][kk] = new TH1F(hname,txt, 200, 0., 2000.);
      h_Pt[ii][kk]->Sumw2();
    }
  }
  TH1F *h_EB_HLTall = new TH1F("h_EB_HLTall","all HLT photon", 1000, 0., 1000.);
  TH1F *h_EE_HLTall = new TH1F("h_EE_HLTall","all HLT photon", 1000, 0., 1000.);

  TH1F *h_chiso_sg = new TH1F("h_chiso_sg","chiso signal region", 150, 0., 30);
  TH1F *h_chworst_sg = new TH1F("h_chworst_sg","chworst signal region", 150, 0., 30);


  TH1F *h_HLT[netabin][13][2];
  for (int jj=0; jj<netabin; jj++){
    for(int ii=0; ii<13; ii++){
      sprintf(txt,"HLT ebee %d bit %d all",jj, ii);
      sprintf(hname,"h_HLT_ebee_%d_bit%d",jj, ii);
      h_HLT[jj][ii][0] = new TH1F(hname,txt, 2000, 0., 2000.);
      sprintf(txt,"HLT ebee %d bit %d pass",jj, ii);
      sprintf(hname,"h_HLT_ebee_%d_bit%d_pass",jj, ii);
      h_HLT[jj][ii][1] = new TH1F(hname,txt, 2000, 0., 2000.);
    }
  }
  //smearing due to gain switching (G6->G1)    
  // float binning[10]={0,100,175,225, 275, 350, 100000}; //from E/P
  // TH1F *h_gainCorr = new TH1F("h_gainCorr","correction due to gain switch", 6, binning);
  // h_gainCorr->SetBinContent(1,1.);      h_gainCorr->SetBinError(1,0.001);
  // h_gainCorr->SetBinContent(2,0.998);	  h_gainCorr->SetBinError(2,0.002);
  // h_gainCorr->SetBinContent(3,0.996);	  h_gainCorr->SetBinError(3,0.002);
  // h_gainCorr->SetBinContent(4,0.991);	  h_gainCorr->SetBinError(4,0.003);
  // h_gainCorr->SetBinContent(5,0.981);	  h_gainCorr->SetBinError(5,0.003);
  // h_gainCorr->SetBinContent(6,0.965);	  h_gainCorr->SetBinError(6,0.010);  
  float binning[10]={0,200,300, 400, 500, 100000};
  TH1F *h_gainCorr = new TH1F("h_gainCorr","correction due to gain switch", 5, binning);
  h_gainCorr->SetBinContent(1,1.);      h_gainCorr->SetBinError(1,0.001);
  h_gainCorr->SetBinContent(2,1./1.0199);	  h_gainCorr->SetBinError(2,0.001);
  h_gainCorr->SetBinContent(3,1./1.052);	  h_gainCorr->SetBinError(3,0.003);
  h_gainCorr->SetBinContent(4,1./1.015);	  h_gainCorr->SetBinError(4,0.006);
  h_gainCorr->SetBinContent(5,1.);      h_gainCorr->SetBinError(5,0.001);  

  Long64_t nentries = fChain->GetEntries();   
  printf("nentries %li \n", nentries);
  printf("HLT option %d \n", HLTOPTION);

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //for (Long64_t jentry=0; jentry<1000;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if(TMath::Abs(recoEta)>1.4442 && TMath::Abs(recoEta)<1.566) continue;
    if(TMath::Abs(recoEta)>2.5) continue;

    if(MET/recoPt > 0.7) continue;

    //test new mva with isolation smearing
    //if(isData!=1) 
    photonIDmva = mva;// norminall
    // photonIDmva = mva + trd->Gaus(0.025,0.05); //extra smearing for signal sys
    // photonIDmva = mva - trd->Gaus(0.025,0.05);
    // float tmp_shift = 0.015; if(TMath::Abs(recoSCEta)>1.5) tmp_shift=0.03;
    // photonIDmva = mva - tmp_shift;// - trd->Gaus(0.025,0.05);

    //if(run>259000) continue;
    if(run == 256729) continue;
    if(run == 256734 ) continue;
    //jetY =jetEta;

    //printf("photon eta %.2f, bin %d,  pt %.2f, bin %d , hltbit %d\n", recoEta, EBEE(recoEta), recoPt, Ptbin(recoPt) , HLTbit(recoPt));
    int ebee = EBEE(recoEta);
    //if(recoEta>-1.8 && recoEta<-1.5) printf("ebee bin %d \n", ebee);
    int ptbin = Ptbin(recoPt);
    //int ptbin = Ptbin(recoPt*0.99); //playing with photon energy scale

    //smearing due to gain switching (G6->G1)    
    TLorentzVector *phop4 = new TLorentzVector();
    phop4->SetPtEtaPhiM(recoPt, recoEta, recoPhi,0.);
    if(isData==1 && TMath::Abs(recoEta)<1.5) {
      phop4->SetPtEtaPhiM(recoPt, recoEta, recoPhi,0.);
      float phoE = phop4->E();
      int bin1 =  h_gainCorr->FindBin(SeedEnergy);
      // float factor = trd->Gaus( h_gainCorr->GetBinContent(bin1), h_gainCorr->GetBinError(bin1));
      float factor = h_gainCorr->GetBinContent(bin1);
      float phoE_new = phoE*1./factor;
      //printf("phoE %.3f , factor 1./%.3f, new %.3f \n", phoE, factor, phoE_new);
      phop4->SetE(phoE_new);
      //printf("phoEt %.3f , new %.3f \n", recoPt, phop4->Et());
      ptbin = Ptbin(phop4->Et());
    }
    //end of smeaing gain switching effect
    //----------------------------------------------------------------
    int hltbit = HLTbit(recoPt);
    int jetbin = JetEtaBin(jetY);

    //define BDT var
    float var[20];
    var[0] = recoPhi;
    var[1] = r9;
    var[2] = e1x3Full5x5/e5x5Full5x5;
    var[3] = e2x2Full5x5/e5x5Full5x5;
    var[4] = e2x5Full5x5/e5x5Full5x5;
    var[5] = sieieFull5x5;
    var[6] = sieipFull5x5;
    var[7] = recoSCEta;
    var[8] = rawE;
    var[9] = scEtaWidth;
    var[10] = scPhiWidth;
    var[11] = phoIsoRaw;
    var[12] = chIsoRaw;
    var[13] = chWorstRaw;
    var[14] = rho;
    var[15] = photonIDmva;
    var[16] = esRR;
    var[17] = esEn/rawE; 
    var[18] = nVtx;

    if(eleVeto==1 && photonIDmva>0.35 && chIsoRaw<2.){
      if(ebee>1 && HoverE > 0.01) continue;
      for(int ibit=0; ibit<13; ibit++){
	int basebit=ibit-1;
	//if(basebit==7) basebit=6;
	if(ibit>=4) basebit=3;
	if(ibit==6) basebit=5;
	if(ibit>=7) basebit=6;
	if(ibit>=9) basebit=8;
	if( (phoFiredTrg >>basebit) & 1 == 1 ) {
	  h_HLT[ebee][ibit][0]->Fill(phop4->Et());
	  if( (phoFiredTrg >>(ibit)) & 1 == 1 ) {
	    h_HLT[ebee][ibit][1]->Fill(phop4->Et());
	  }
	}	  
      }	
      if(phoFiredTrg>0) {
	if(ebee==0) h_EB_HLTall->Fill(recoPt);
	else h_EE_HLTall->Fill(recoPt);
      }
    }
      


    if(ptbin<0) continue;
    //if(photon_jetID==1) continue;
    // if(isData==1 && ((phoFiredTrg>>triggerbit(ptbin))&1)==0) continue;
    // if(isData==1 && !(((phoFiredTrg>>8)&1)==1 || MTm>0) ) continue;
    //if(!(((phoFiredTrg>>8)&1)==1 || MTm>0) ) continue;
    if(HLTOPTION==1 && (((phoFiredTrg>>8)&1)==0) ) continue;
    float dr_wg = TMath::Sqrt(deta_wg*deta_wg+dphi_wg*dphi_wg);
    // if(MTm>0. && ebee==0 &&dr_wg<0.4) continue;
    // if(MTm>0. && ebee==1 &&dr_wg<1.) continue;
    // if(MTm>0. && dr_wg<0.4) continue;
    
    int mctruth = 0;
    if(isData!=1 && isMatched!=1 && isConverted!=1 && isMatchedEle!=1) mctruth=1; //fake

    h_BDT_all[ebee][jetbin][ptbin][mctruth]->Fill(photonIDmva, xsweight*puwei); //<-default 
    h_Pt_all[ebee][jetbin][ptbin][mctruth]->Fill(recoPt, xsweight*puwei);

    //if(isData==1 && ((phoFiredTrg>>8)&1)==0) continue;
    //if(mctruth<0)continue;      
    //dump histogram for BDT fit
    //for all HLT photon
    //if(isData==1&&phoFiredTrg==0) continue;
    //if(isData==1&&(Mmm<50||Mee<50)) continue;
    //if(Mee>50) continue;
    //use 175 trigger
    //if(isData==0 || (isData==1&&((phoFiredTrg>>6) &1 ==1) )){ //175 25ns
    //if((isData==0&&phoFiredTrg>>0 &1 ==1) || (isData==1&&phoFiredTrg>>8 &1 ==1 )){ //175
    
    if(TMath::Abs(recoEta)<1.4442){
      if(sieieFull5x5 > 0.015) continue;
      // for template validattion
      //if(sieieFull5x5<0.01) continue;
      //if(sieieFull5x5>0.01) continue;

      //for testing smearing signal MC
      // if(isData!=1 && (isMatched==1||isConverted==1) ) {
      //  	float rnd_gau = 1- TMath::Abs(trd->Gaus(0,0.02));
      //  	if(rnd_gau<0.) rnd_gau=1.;
      //  	//printf("smear by %f \n", rnd_gau );
      //  	h_BDT[ebee][jetbin][ptbin][mctruth]->Fill(photonIDmva*rnd_gau, xsweight*puwei);
      // }else{
      //  	h_BDT[ebee][jetbin][ptbin][mctruth]->Fill(photonIDmva, xsweight*puwei);
      // }

      h_BDT[ebee][jetbin][ptbin][mctruth]->Fill(photonIDmva, xsweight);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][0]->Fill(photonIDmva, chIsoRaw, xsweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][1]->Fill(photonIDmva, phoIsoRaw, xsweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][2]->Fill(photonIDmva, chIsoRaw+phoIsoRaw, xsweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][3]->Fill(photonIDmva, chWorstRaw, xsweight*puwei);
      // h_IsovsBDT[ebee][jetbin][ptbin][mctruth][0]->Fill(photonIDmva, chIsoRaw, puwei);
      // h_IsovsBDT[ebee][jetbin][ptbin][mctruth][1]->Fill(photonIDmva, phoIsoRaw, puwei);
      // h_IsovsBDT[ebee][jetbin][ptbin][mctruth][2]->Fill(photonIDmva, chIsoRaw+phoIsoRaw, puwei);
      // h_IsovsBDT[ebee][jetbin][ptbin][mctruth][3]->Fill(photonIDmva, chWorstRaw, puwei);
      // for(int ivar=0; ivar<16; ivar++){	
      // 	h_BDTvar[ivar][ebee][ptbin][mctruth]->Fill(var[ivar], xsweight*puwei);
      // 	//printf("var %s, value %f \n", varname.find(ivar)->second, var[ivar]);
      // }
      //h_BDT[ebee][jetbin][ptbin][mctruth]->Fill(mva, xsweight*puwei);
      h_Pt[ebee][mctruth]->Fill(recoPt, xsweight*puwei);
      h_Ptspec[ebee][mctruth]->Fill( phop4->Et(), xsweight*puwei);
      if(recoPt>15.) {
	h_Wmn_mt[ebee][mctruth]->Fill(MTm, xsweight*puwei);            
      }
      if(mctruth==1&&recoPt>100.){
	h_chiso_sg->Fill(chIsoRaw);
	h_chworst_sg->Fill(chWorstRaw+phoIsoRaw);
      }
    }else{
      if(sieieFull5x5>0.045)  continue;
      h_BDT[ebee][jetbin][ptbin][mctruth]->Fill(photonIDmva, xsweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][0]->Fill(photonIDmva, chIsoRaw, xsweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][1]->Fill(photonIDmva, phoIsoRaw, xsweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][2]->Fill(photonIDmva, chIsoRaw+phoIsoRaw, xsweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][3]->Fill(photonIDmva, chWorstRaw, xsweight*puwei);
      // h_IsovsBDT[ebee][jetbin][ptbin][mctruth][0]->Fill(photonIDmva, chIsoRaw, puwei);
      // h_IsovsBDT[ebee][jetbin][ptbin][mctruth][1]->Fill(photonIDmva, phoIsoRaw, puwei);
      // h_IsovsBDT[ebee][jetbin][ptbin][mctruth][2]->Fill(photonIDmva, chIsoRaw+phoIsoRaw, puwei);
      // h_IsovsBDT[ebee][jetbin][ptbin][mctruth][3]->Fill(photonIDmva, chWorstRaw, puwei);

      // for(int ivar=0; ivar<18; ivar++){	
      // 	h_BDTvar[ivar][ebee][ptbin][mctruth]->Fill(var[ivar], xsweight*puwei);
      // }
      //h_BDT[ebee][jetbin][ptbin][mctruth]->Fill(mva, xsweight*puwei);
      h_Pt[ebee][mctruth]->Fill(recoPt, xsweight*puwei);
      h_Ptspec[ebee][mctruth]->Fill( phop4->Et(), xsweight*puwei);
      if(recoPt>15.) {
	h_Wmn_mt[ebee][mctruth]->Fill(MTm, xsweight*puwei);             	
      }   
    }   
  }

  TH1F *h_sf_EB = new TH1F("h_sf_EB","sf EB", 100, -1, 1.);
  TH1F *h_sf_EE = new TH1F("h_sf_EE","sf EE", 100, -1, 1.);
  //---------------------------------------------------------------------------------------   
  // correct signal template
  // if(isData!=1 && (isMatched==1 || isConverted==1)) {
  //   TFile *fEB = new TFile("../rootfiles_18feb/EB_ratio.root");
  //   TFile *fEE = new TFile("../rootfiles_18feb/EB_ratio.root");
  //   TH1F *h_eb_sf = (TH1F*)fEB->Get("mva_EBReal");
  //   TH1F *h_ee_sf = (TH1F*)fEE->Get("mva_EBReal");

    
  //   h_sf_EB->Sumw2();
  //   h_sf_EE->Sumw2();
  //   for(int ibin=0; ibin<20; ibin++){
  //     for(int irep=0; irep<5; irep++){
  // 	if(ibin>=10){
  // 	  h_sf_EB->SetBinContent( ibin*5+irep+1, h_eb_sf->GetBinContent(ibin+1) );
  // 	  h_sf_EB->SetBinError( ibin*5+irep+1, h_eb_sf->GetBinError(ibin+1) );
  // 	  h_sf_EE->SetBinContent( ibin*5+irep+1, h_ee_sf->GetBinContent(ibin+1) );
  // 	  h_sf_EE->SetBinError( ibin*5+irep+1, h_ee_sf->GetBinError(ibin+1) );
  // 	}else{
  // 	  h_sf_EB->SetBinContent( ibin*5+irep+1, 1.);
  // 	  h_sf_EB->SetBinError( ibin*5+irep+1, 0.);
  // 	  h_sf_EE->SetBinContent( ibin*5+irep+1, 1.);
  // 	  h_sf_EE->SetBinError( ibin*5+irep+1, 0.);
  // 	}
  //     }
  //   }

  //   h_eb_sf->Draw();
  //   h_sf_EB->SetLineColor(2);
  //   h_sf_EB->Draw("hsame");
  //   h_ee_sf->Draw();
  //   h_sf_EE->SetLineColor(4);
  //   h_sf_EE->Draw("hsame");
    
  //   for(int mm=0; mm<3; mm++){
  //     for(int jj=0; jj<30; jj++){
  //   	for(int kk=0; kk<2; kk++){
  //   	  int ii=0;      //EB
  //   	  h_BDT[ii][mm][jj][kk]->Multiply(h_sf_EB);
  //   	  h_BDT_all[ii][mm][jj][kk]->Multiply(h_sf_EB);
  //   	  ii=1;      //EE
  //   	  h_BDT[ii][mm][jj][kk]->Multiply(h_sf_EE);
  //   	  h_BDT_all[ii][mm][jj][kk]->Multiply(h_sf_EE);
  //   	}
  //     }
  //   }
  // }
  //---------------------------------------------------------------------------------------
  fout->cd();
   
  for(int ii=0; ii<netabin; ii++){
    for(int mm=0; mm<3; mm++){
      for(int jj=0; jj<30; jj++){
	for(int kk=0; kk<2; kk++){
	  h_BDT[ii][mm][jj][kk]->Write();
	  h_IsovsBDT[ii][mm][jj][kk][0]->Write();
	  h_IsovsBDT[ii][mm][jj][kk][1]->Write();
	  h_IsovsBDT[ii][mm][jj][kk][2]->Write();
	  h_IsovsBDT[ii][mm][jj][kk][3]->Write();
	  h_BDT_all[ii][mm][jj][kk]->Write();
	  h_Pt_all[ii][mm][jj][kk]->Write();
	}
      }
    }
    for(int kk=0; kk<2; kk++){
      h_Pt[ii][kk]->Write();
      h_Ptspec[ii][kk]->Write();
    }
  }
   
  h_EB_HLTall->Write();
  h_EE_HLTall->Write();

  for (int jj=0; jj<netabin; jj++){
    for(int ii=0; ii<13; ii++){
      h_HLT[jj][ii][0]->Write();
      h_HLT[jj][ii][1]->Write();
    }
  }

  h_chiso_sg->Write();
  h_chworst_sg->Write();

  h_sf_EB->Write();
  h_sf_EE->Write();
  for(int ii=0; ii<netabin; ii++){
    for(int kk=0; kk<2; kk++){
      h_Wmn_mt[ii][kk]->Write();
    }
  }

  // for(int ii=0; ii<19; ii++){
  //   for(int mm=0; mm<netabin; mm++){
  //     for(int jj=0; jj<30; jj++){
  //  	for(int kk=0; kk<2; kk++){	  
  //  	  h_BDTvar[ii][mm][jj][kk]->Write();
  //  	}
  //     }
  //   }
  // }

  fout->Close();

}


Int_t MakeHisto::EBEE(Float_t eta)
{
  // if(TMath::Abs(eta)<1.5) return 0;
  // else return 1;
  // -2.5, -2.1, -1.8, -1.5, -0.9, 0., 0.9, 1.5, 1.8, 2.1, 2.5
  // if(eta< -2.1) return 0;
  // else if(eta<-1.8 ) return 1;
  // else if(eta<-1.5 ) return 2;
  // else if(eta<-1.2 ) return 3;
  // else if(eta<-0.9 ) return 4;
  // else if(eta<-0.6 ) return 5;
  // else if(eta<-0.3 ) return 6;
  // else if(eta< 0.0 ) return 7;
  // else if(eta< 0.3 ) return 8;
  // else if(eta< 0.6 ) return 9;
  // else if(eta< 0.9 ) return 10;
  // else if(eta< 1.2 ) return 11;
  // else if(eta< 1.5 ) return 12;
  // else if(eta< 1.8 ) return 13;
  // else if(eta< 2.1 ) return 14;
  // else return 15;

  //netabin 14
  // -2.5, -2.2, -2.0, -1.8 -1.6, -1.5, -0.8, 0., 0.8, 1.5, 1.6, 1.8, 2.0, 2.2, 2.5
  // if(eta< -2.4) return 0;
  // else if(eta<-2.3 ) return 1;
  // else if(eta<-2.2 ) return 2;
  // else if(eta<-2.1 ) return 3;
  // else if(eta<-1.5 ) return 4;
  // else if(eta<-0.8 ) return 5;
  // else if(eta< 0.0 ) return 6;
  // else if(eta< 0.8 ) return 7;
  // else if(eta< 1.5 ) return 8;
  // else if(eta< 2.1 ) return 9;
  // else if(eta< 2.2 ) return 10;
  // else if(eta< 2.3 ) return 11;
  // else if(eta< 2.4 ) return 12;
  // else return 13;

  //if netabin==4
  if(TMath::Abs(eta)<0.8) return 0;
  else if(TMath::Abs(eta)<1.5) return 1;
  else if(TMath::Abs(eta)<2.1) return 2;
  else return 3;


}
Int_t MakeHisto::Ptbin(Float_t pt)
{
  //                  0   1   2   3   4   5   6   7    8    9   10   11   12
  // float ptcut[30] = {20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 
  // 		     150, 160, 170, 180, 200, 225, 250, 300, 350, 400, 500, 750, 1000,}; //25 bins to index 10
  //                  13   14   15   16   17   18   19   20   21   22   23   24    25
  //                  0   1   2   3   4   5    6    7    8    9   10   11   12
  //float ptcut[30] = {22, 30, 36, 50, 75, 90, 105,  120, 135, 150, 165, 175, 185,
  float ptcut[30] = {15, 30, 35, 60, 75, 90, 100,  120, 135, 150, 165, 175, 185,
		     190, 200, 220, 250, 300, 350, 400, 500, 750, 1000, 1500, 2000, 3000, 10000}; //22 bins
  //                  13   14   15   16   17   18   19   20   21    22    23    24    25     26
  for(int ibin=0; ibin<26; ibin++){
    if(pt>=ptcut[ibin] && pt<ptcut[ibin+1] ) return ibin;
  }
  if(pt<22.) return -1;
}

Int_t MakeHisto::HLTbit(Float_t pt){
  //                  0   1   2   3   4   5    6    7    8    9   10   11   12
  float ptcut[30] = {22, 30, 36, 50, 75, 90, 120, 165, 175 };
  //                  13   14   15   16   17   18   19   20   21   22   23   24    25
  for(int ibin=0; ibin<8; ibin++){
    if(pt>=ptcut[ibin] && pt<ptcut[ibin+1] ) return ibin;
  }
  if(pt>175) return 8;
  if(pt<22.) return -1;
}

Int_t MakeHisto::JetEtaBin(Float_t eta){  
  if(jetPt==0) return 2;
  if(TMath::Abs(eta)<1.5) return 0;
  return 1;
}
Int_t MakeHisto::triggerbit(Int_t ptbin){
  if(ptbin==2) return 2;
  if(ptbin==3) return 3;
  if(ptbin==4) return 4;
  if(ptbin==5) return 5;
  if(ptbin==6) return 5;
  if(ptbin==7) return 6;
  if(ptbin==8) return 6;
  if(ptbin==9) return 6;
  if(ptbin==10) return 6;
  if(ptbin==11) return 6;
  if(ptbin==12) return 6;
  if(ptbin>=13) return 8;
  return 0;
}
