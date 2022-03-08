#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TTree.h>
#include <TChain.h>
#include <TMath.h>
#include <TProfile.h>
#include <TRandom.h>


//struct ReweightHists
//{
class ReweightHists
{
public:
    ReweightHists()
    {
        // pu & mc weighted
        h_pho_pt_eta = new TH2F("h_pho_pt_eta","pt eta distribution",500, 0., 2500., 50, -2.5, 2.5);
        h_pho_pt_eta_rw = new TH2F("h_pho_pt_eta_rw","pt eta distribution",500, 0., 2500., 50, -2.5, 2.5);

        // pu & mc weighted
        h_fake_pt_eta = new TH2F("h_fake_pt_eta","pt eta distribution",500, 0., 2500., 50, -2.5, 2.5);
        h_fake_pt_eta_rw = new TH2F("h_fake_pt_eta_rw","pt eta distribution",500, 0., 2500., 50, -2.5, 2.5);

        // derived value from h_pho_pt_eta
        h_weight_pt_eta = new TH2F("h_weight_pt_eta","pt eta weight distribution",500, 0., 2500., 50, -2.5, 2.5);
        h_weight_fake_pt_eta = new TH2F("h_weight_fake_pt_eta","pt eta fake weight distribution",500, 0., 2500., 50, -2.5, 2.5);

        h_pt = new TH1F("h_pt","pt", 100, 0., 100.);

        h_pho_pt_eta->Sumw2();
        h_pho_pt_eta_rw->Sumw2();
        h_fake_pt_eta->Sumw2();
        h_fake_pt_eta_rw->Sumw2();	       	 
        h_weight_pt_eta->Sumw2();
        h_weight_fake_pt_eta->Sumw2();
        h_pt->Sumw2();
        return;
    }

    TH2F *h_pho_pt_eta;
    TH2F *h_pho_pt_eta_rw;
    TH2F *h_fake_pt_eta;
    TH2F *h_fake_pt_eta_rw;
    TH2F *h_weight_pt_eta;
    TH2F *h_weight_fake_pt_eta;
    TH1F *h_pt;
    void WeightCounting( const std::vector< const char* >& inames )
    {
        TChain *t = new TChain("t");
        for ( const char* iname : inames ) t->Add(iname);

        // declare tree variables {{{
        // Declaration of leaf types
        Float_t pthat;
        Float_t         mcPt;
        Float_t         mcEta;
        Float_t         mcPhi;
        Float_t         recoPt;
        Float_t         recoEta;
        Float_t         recoPhi;
        Float_t         recoSCEta;
        Float_t         r9;
        Float_t         r9Full5x5;
        Int_t           isMatched;
        Int_t           isMatchedEle;
        Int_t           isConverted;
        //Int_t           idLoose;
        //Int_t           idMedium;
        //Int_t           idTight;
        Int_t           nVtx;
        Int_t           nPU;
        Int_t           eleVeto;
        Float_t         HoverE;
        //Float_t         sieie;
        //Float_t         sieip;
        //Float_t         sipip;
        //Float_t         chIso;
        //Float_t         phoIso;
        //Float_t         nhIso;
        Float_t         chIsoRaw;
        Float_t         chWorstRaw;
        Float_t         phoIsoRaw;
        Float_t         nhIsoRaw;
        Float_t         rho;
        //Float_t         e1x3;
        //Float_t         e2x2;
        //Float_t         e2x5;
        //Float_t         e5x5;
        Float_t         rawE;
        Float_t         scEtaWidth;
        Float_t         scPhiWidth;
        Float_t         esRR;
        Float_t         esEn;
        Float_t         mva;
        Float_t         sieieFull5x5;
        Float_t         sieipFull5x5;
        Float_t         sipipFull5x5;
        //Float_t         e1x3Full5x5;
        Float_t         e2x2Full5x5;
        //Float_t         e2x5Full5x5;
        Float_t         e5x5Full5x5;
        Float_t         mcCalIso04;
        Float_t         mcTrkIso04;
        Float_t         mcweight, puwei = 1.;
        Float_t         photonIDmva;
        //Float_t         trackIsoDR03;
        //Float_t         phoIsoDR03;

        t->SetBranchAddress("pthat", &pthat);
        t->SetBranchAddress("mcPt", &mcPt);
        t->SetBranchAddress("mcEta", &mcEta);
        t->SetBranchAddress("mcPhi", &mcPhi);
        t->SetBranchAddress("recoPt", &recoPt);
        t->SetBranchAddress("recoEta", &recoEta);
        t->SetBranchAddress("recoPhi", &recoPhi);
        t->SetBranchAddress("recoSCEta", &recoSCEta);
        t->SetBranchAddress("r9", &r9);
        t->SetBranchAddress("r9Full5x5", &r9Full5x5);
        t->SetBranchAddress("isMatched", &isMatched);
        t->SetBranchAddress("isMatchedEle", &isMatchedEle);
        t->SetBranchAddress("isConverted", &isConverted);
        //t->SetBranchAddress("idLoose", &idLoose);
        //t->SetBranchAddress("idMedium", &idMedium);
        //t->SetBranchAddress("idTight", &idTight);
        t->SetBranchAddress("nVtx", &nVtx);
        t->SetBranchAddress("nPU", &nPU);
        t->SetBranchAddress("eleVeto", &eleVeto);
        t->SetBranchAddress("HoverE", &HoverE);
        //t->SetBranchAddress("sieie", &sieie);
        //t->SetBranchAddress("sieip", &sieip);
        //t->SetBranchAddress("sipip", &sipip);
        //t->SetBranchAddress("chIso", &chIso);
        //t->SetBranchAddress("phoIso", &phoIso);
        //t->SetBranchAddress("nhIso", &nhIso);
        t->SetBranchAddress("chIsoRaw", &chIsoRaw);
        t->SetBranchAddress("chWorstRaw", &chWorstRaw);
        t->SetBranchAddress("phoIsoRaw", &phoIsoRaw);
        t->SetBranchAddress("nhIsoRaw", &nhIsoRaw);
        t->SetBranchAddress("rho", &rho);
        //t->SetBranchAddress("e1x3", &e1x3);
        //t->SetBranchAddress("e2x2", &e2x2);
        //t->SetBranchAddress("e2x5", &e2x5);
        //t->SetBranchAddress("e5x5", &e5x5);
        t->SetBranchAddress("rawE", &rawE);
        t->SetBranchAddress("scEtaWidth", &scEtaWidth);
        t->SetBranchAddress("scPhiWidth", &scPhiWidth);
        t->SetBranchAddress("esRR", &esRR);
        t->SetBranchAddress("esEn", &esEn);
        t->SetBranchAddress("mva", &mva);
        t->SetBranchAddress("sieieFull5x5", &sieieFull5x5);
        t->SetBranchAddress("sieipFull5x5", &sieipFull5x5);
        t->SetBranchAddress("sipipFull5x5", &sipipFull5x5);
        //t->SetBranchAddress("e1x3Full5x5", &e1x3Full5x5);
        t->SetBranchAddress("e2x2Full5x5", &e2x2Full5x5);
        //t->SetBranchAddress("e2x5Full5x5", &e2x5Full5x5);
        t->SetBranchAddress("e5x5Full5x5", &e5x5Full5x5);
        t->SetBranchAddress("mcCalIso04", &mcCalIso04);
        t->SetBranchAddress("mcTrkIso04", &mcTrkIso04);
        t->SetBranchAddress("photonIDmva", &photonIDmva);
        // t->SetBranchAddress("photrkSumPtHollowConeDR03", &trackIsoDR03);
        // t->SetBranchAddress("phoEcalRecHitSumEtConeDR03", &phoIsoDR03);

        t->SetBranchAddress("mcweight", &mcweight);
        t->SetBranchAddress("puwei", &puwei);
        // declare tree variables end }}}

        float totalEventWeight = 1.;

        Long64_t nentries = t->GetEntries();
        printf("nentries %lli \n", nentries);

        printf(" loop through entries to get 2d weight \n");
        for (Long64_t jentry=0; jentry<nentries;jentry++) {
            //if(jentry%5!=0) continue;
            Long64_t nb = t->GetEntry(jentry);  
            totalEventWeight = mcweight * puwei;
            if (jentry % 1000000 == 0){
                fprintf(stderr, "Processing event %lli of %lli (%.3f %%)\n", jentry + 1, nentries, (jentry+1)*100./float(nentries));
            }
            //printf("photon Et %.2f, Eta %.2f \n", recoPt, recoEta);
            if(isMatchedEle == 1) continue;
            if(sieipFull5x5>1.) continue;
            if(TMath::Abs(recoSCEta)>1.4442 && TMath::Abs(recoSCEta)<1.566) continue;
            if(TMath::Abs(recoSCEta)>=2.5) continue;
            //if(eleVeto==0) continue;
            if(recoPt<15.) continue;
            //preselection
            // if(chIsoRaw>20.) continue;
            // if(phoIsoRaw>50.) continue;
            // if(chWorstRaw>20.) continue;
            // if(TMath::Abs(recoSCEta)<1.5 && sieieFull5x5 > 0.02) continue;
            // if(TMath::Abs(recoSCEta)>1.5 && sieieFull5x5 > 0.05) continue;    
            // if(HoverE>0.1) continue;


            if(isMatched==1||isConverted==1){ //photon
                h_pho_pt_eta->Fill(recoPt, recoEta, totalEventWeight);
                h_pt->Fill(recoPt,totalEventWeight);
            }else if(isMatched != 1 && isConverted!=1){
                h_fake_pt_eta->Fill(recoPt, recoEta, totalEventWeight);
            }
        }
        // //if weighted to fake spectrum
        h_fake_pt_eta_rw = (TH2F*)h_fake_pt_eta->Clone();
        h_fake_pt_eta_rw->SetName("h_fake_pt_eta_rw");
        for(int ibin=0; ibin<h_fake_pt_eta->GetNbinsX(); ibin++){
            for(int jbin=0; jbin<h_fake_pt_eta->GetNbinsY(); jbin++){
                h_weight_fake_pt_eta->SetBinContent(ibin+1, jbin+1, 1.);
            }
        }

        // //reweight pt/eta  to fake
        for(int ibin=0; ibin<h_pho_pt_eta->GetNbinsX(); ibin++){
            for(int jbin=0; jbin<h_pho_pt_eta->GetNbinsY(); jbin++){
                float den = h_pho_pt_eta->GetBinContent(ibin+1,jbin+1);
                float num = h_fake_pt_eta_rw->GetBinContent(ibin+1,jbin+1);
                //float num = 4;
                float err = h_pho_pt_eta->GetBinError(ibin+1,jbin+1);
                float ratio =1.;
                if(den >0.) {
                    ratio=num/den;
                    err = err/den*ratio;
                }
                if(ratio>100.) ratio=1.;
                //if(ratio > 4.) ratio=1.;
                h_weight_pt_eta->SetBinContent(ibin+1, jbin+1, ratio);
                h_weight_pt_eta->SetBinError(ibin+1, jbin+1, err);

                h_pho_pt_eta_rw->SetBinContent(ibin+1, jbin+1, den*ratio);
                h_pho_pt_eta_rw->SetBinError(ibin+1, jbin+1, h_pho_pt_eta->GetBinError(ibin+1,jbin+1)*ratio);
            }
        }
    } // end of WeightCounting
    void WritingHists( const char* fout_)
    {
        TFile *fout = new TFile(fout_,"recreate");
        fout->cd();
        h_pho_pt_eta->Write();
        h_pho_pt_eta_rw->Write();
        h_fake_pt_eta->Write();
        h_fake_pt_eta_rw->Write();
        h_weight_pt_eta->Write();

        h_pt->Write();
        fout->Close();
    }
}; // end of class

void AppendWeightsToFile( const char* ifilename, const ReweightHists& rwHists, const char* oname )
{
    TFile* f = TFile::Open(ifilename);
    TTree* t = (TTree*) f->Get("t");
    Long64_t nentries = t->GetEntries();
        // declare tree variables {{{
        // Declaration of leaf types
        Float_t pthat;
        Float_t         mcPt;
        Float_t         mcEta;
        Float_t         mcPhi;
        Float_t         recoPt;
        Float_t         recoEta;
        Float_t         recoPhi;
        Float_t         recoSCEta;
        Float_t         r9;
        Float_t         r9Full5x5;
        Int_t           isMatched;
        Int_t           isMatchedEle;
        Int_t           isConverted;
        //Int_t           idLoose;
        //Int_t           idMedium;
        //Int_t           idTight;
        Int_t           nVtx;
        Int_t           nPU;
        Int_t           eleVeto;
        Float_t         HoverE;
        //Float_t         sieie;
        //Float_t         sieip;
        //Float_t         sipip;
        //Float_t         chIso;
        //Float_t         phoIso;
        //Float_t         nhIso;
        Float_t         chIsoRaw;
        Float_t         chWorstRaw;
        Float_t         phoIsoRaw;
        Float_t         nhIsoRaw;
        Float_t         rho;
        //Float_t         e1x3;
        //Float_t         e2x2;
        //Float_t         e2x5;
        //Float_t         e5x5;
        Float_t         rawE;
        Float_t         scEtaWidth;
        Float_t         scPhiWidth;
        Float_t         esRR;
        Float_t         esEn;
        Float_t         mva;
        Float_t         sieieFull5x5;
        Float_t         sieipFull5x5;
        Float_t         sipipFull5x5;
        //Float_t         e1x3Full5x5;
        Float_t         e2x2Full5x5;
        //Float_t         e2x5Full5x5;
        Float_t         e5x5Full5x5;
        Float_t         mcCalIso04;
        Float_t         mcTrkIso04;
        Float_t         xsweight;
        Float_t         mcweight, puwei = 1.;
        Float_t         photonIDmva;
        //Float_t         trackIsoDR03;
        //Float_t         phoIsoDR03;

        t->SetBranchAddress("pthat", &pthat);
        t->SetBranchAddress("mcPt", &mcPt);
        t->SetBranchAddress("mcEta", &mcEta);
        t->SetBranchAddress("mcPhi", &mcPhi);
        t->SetBranchAddress("recoPt", &recoPt);
        t->SetBranchAddress("recoEta", &recoEta);
        t->SetBranchAddress("recoPhi", &recoPhi);
        t->SetBranchAddress("recoSCEta", &recoSCEta);
        t->SetBranchAddress("r9", &r9);
        t->SetBranchAddress("r9Full5x5", &r9Full5x5);
        t->SetBranchAddress("isMatched", &isMatched);
        t->SetBranchAddress("isMatchedEle", &isMatchedEle);
        t->SetBranchAddress("isConverted", &isConverted);
        //t->SetBranchAddress("idLoose", &idLoose);
        //t->SetBranchAddress("idMedium", &idMedium);
        //t->SetBranchAddress("idTight", &idTight);
        t->SetBranchAddress("nVtx", &nVtx);
        t->SetBranchAddress("nPU", &nPU);
        t->SetBranchAddress("eleVeto", &eleVeto);
        t->SetBranchAddress("HoverE", &HoverE);
        //t->SetBranchAddress("sieie", &sieie);
        //t->SetBranchAddress("sieip", &sieip);
        //t->SetBranchAddress("sipip", &sipip);
        //t->SetBranchAddress("chIso", &chIso);
        //t->SetBranchAddress("phoIso", &phoIso);
        //t->SetBranchAddress("nhIso", &nhIso);
        t->SetBranchAddress("chIsoRaw", &chIsoRaw);
        t->SetBranchAddress("chWorstRaw", &chWorstRaw);
        t->SetBranchAddress("phoIsoRaw", &phoIsoRaw);
        t->SetBranchAddress("nhIsoRaw", &nhIsoRaw);
        t->SetBranchAddress("rho", &rho);
        //t->SetBranchAddress("e1x3", &e1x3);
        //t->SetBranchAddress("e2x2", &e2x2);
        //t->SetBranchAddress("e2x5", &e2x5);
        //t->SetBranchAddress("e5x5", &e5x5);
        t->SetBranchAddress("rawE", &rawE);
        t->SetBranchAddress("scEtaWidth", &scEtaWidth);
        t->SetBranchAddress("scPhiWidth", &scPhiWidth);
        t->SetBranchAddress("esRR", &esRR);
        t->SetBranchAddress("esEn", &esEn);
        t->SetBranchAddress("mva", &mva);
        t->SetBranchAddress("sieieFull5x5", &sieieFull5x5);
        t->SetBranchAddress("sieipFull5x5", &sieipFull5x5);
        t->SetBranchAddress("sipipFull5x5", &sipipFull5x5);
        //t->SetBranchAddress("e1x3Full5x5", &e1x3Full5x5);
        t->SetBranchAddress("e2x2Full5x5", &e2x2Full5x5);
        //t->SetBranchAddress("e2x5Full5x5", &e2x5Full5x5);
        t->SetBranchAddress("e5x5Full5x5", &e5x5Full5x5);
        t->SetBranchAddress("mcCalIso04", &mcCalIso04);
        t->SetBranchAddress("mcTrkIso04", &mcTrkIso04);
        t->SetBranchAddress("photonIDmva", &photonIDmva);
        // t->SetBranchAddress("photrkSumPtHollowConeDR03", &trackIsoDR03);
        // t->SetBranchAddress("phoEcalRecHitSumEtConeDR03", &phoIsoDR03);

        //t->SetBranchAddress("xsweight", &xsweight);
        t->SetBranchAddress("mcweight", &xsweight);
        t->SetBranchAddress("mcweight", &mcweight);
        t->SetBranchAddress("puwei", &puwei);
        // declare tree variables end }}}

    //TFile *fout = new TFile(Form("rw_outFrag.Tree.%s",ifilename),"recreate");
    TFile *fout = new TFile(oname,"recreate");
    fout->cd();
    TTree* tt = t->CloneTree(0);
    tt->SetName("tt");
    tt->SetDirectory(fout);


    Float_t         weight2d_;
    Float_t         weightpt_;
    Int_t  tID;
    Int_t  mID;
    Int_t  lID;


    //asdf need to add mcweight and puwei
    tt->Branch("weight2d", &weight2d_, "weight2d/F");
    tt->Branch("weightpt", &weightpt_, "weightpt/F");
    tt->Branch("tID", &tID, "tID/I");
    tt->Branch("mID", &mID, "mID/I");
    tt->Branch("lID", &lID, "lID/I");


    TH1F* h1x_t = (TH1F*) rwHists.h_weight_pt_eta->ProjectionX();
    TH1F* h1y_t = (TH1F*) rwHists.h_weight_pt_eta->ProjectionY();

    int etabin=0;
    float etacut[10]={0.5, 1.0, 1.5, 2., 2.1, 2.2, 2.3, 2.4, 2.5}; 

    TRandom *tnd = new TRandom();
    printf(" 2nd loop of entries to assign weight for each photon \n");

    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        //if(jentry%5!=0) continue;
        Long64_t nb = t->GetEntry(jentry);  

        // initialize stored value.
        weight2d_ = 1.;
        weightpt_ = 1.;
        tID=0;  
        mID=0;
        lID=0;

        if (jentry % 1000000 == 0){
            fprintf(stderr, "Processing event %lli of %lli (%.3f %%)\n", jentry + 1, nentries, (jentry+1)*100./float(nentries));
        }

        //printf("photon Et %.2f, Eta %.2f \n", recoPt, recoEta);
        if(isMatchedEle == 1) continue;
        if(sieipFull5x5>1.) continue;
        if(TMath::Abs(recoSCEta)>1.4442 && TMath::Abs(recoSCEta)<1.566) continue;
        if(TMath::Abs(recoSCEta)>=2.5) continue;
        //if(eleVeto==0) continue;
        if(recoPt<15.) continue;
        //preselection
        // if(chIsoRaw>20.) continue;
        // if(phoIsoRaw>50.) continue;
        // if(chWorstRaw>20.) continue;
        // if(TMath::Abs(recoSCEta)<1.5 && sieieFull5x5 > 0.02) continue;
        // if(TMath::Abs(recoSCEta)>1.5 && sieieFull5x5 > 0.05) continue;    
        // if(HoverE>0.1) continue;

        int ibin = h1x_t->FindBin(recoPt);
        int jbin = h1y_t->FindBin(recoEta);
        if(isMatched==1 || isConverted==1){ //photon
            weight2d_ =  rwHists.h_weight_pt_eta->GetBinContent(ibin,jbin);
        }else{
            weight2d_ =  rwHists.h_weight_fake_pt_eta->GetBinContent(ibin,jbin);      
        }
        if(recoPt<100.&&recoPt>0.) weightpt_ = 10./recoPt;
        else weightpt_ = 10./100.;

        //pre-select fakes
        if(isMatched!=1){
            float presel = tnd->Uniform(1.);
            float ww = rwHists.h_weight_fake_pt_eta->GetBinContent(ibin,jbin);    
            if(presel>ww) continue;
        }  

        // fill in new tree {{{
        for(int ii=0; ii<9; ii++){
            if(TMath::Abs(recoEta) > etacut[ii]) etabin = ii+1;
        }
        float p1_rho = 0.831 ; 
        float p1_chiso[10]; float p1_chisow[10]; float p1_phiso[10]; float p1_nhiso[10]; 
        // asdf seems to be modified from wiki
        p1_chiso[0] = 0.006;  p1_chisow[0] = 0.164;  p1_phiso[0] = 0.093;  p1_nhiso[0] = 0.000; 
        p1_chiso[1] = 0.006;  p1_chisow[1] = 0.086;  p1_phiso[1] = 0.095;  p1_nhiso[1] = 0.011; 
        p1_chiso[2] = 0.006;  p1_chisow[2] = 0.053;  p1_phiso[2] = 0.086;  p1_nhiso[2] = 0.020; 
        p1_chiso[3] = 0.006;  p1_chisow[3] = 0.072;  p1_phiso[3] = 0.038;  p1_nhiso[3] = -0.017; 
        p1_chiso[4] = 0.010;  p1_chisow[4] = 0.056;  p1_phiso[4] = 0.033;  p1_nhiso[4] = 0.010; 
        p1_chiso[5] = 0.003;  p1_chisow[5] = 0.077;  p1_phiso[5] = 0.041;  p1_nhiso[5] = -0.033; 
        p1_chiso[6] = 0.001;  p1_chisow[6] = 0.103;  p1_phiso[6] = 0.059;  p1_nhiso[6] = -0.040; 
        p1_chiso[7] = -0.000;  p1_chisow[7] = 0.070;  p1_phiso[7] = 0.065;  p1_nhiso[7] = 0.006; 
        p1_chiso[8] = 0.001;  p1_chisow[8] = 0.040;  p1_phiso[8] = 0.076;  p1_nhiso[8] = 0.020; 

        //asdf this chIso does not be stored. Only used for calculate ID
        // this Iso is needed to be further set from TWIKI

        float chIso = chIsoRaw  - p1_chiso[etabin]*(rho/p1_rho);
        float phoIso = phoIsoRaw - p1_phiso[etabin]*(rho/p1_rho);
        float nhIso = nhIsoRaw  - p1_nhiso[etabin]*(rho/p1_rho);
        float chWorst = chWorstRaw - p1_chisow[etabin]*(rho/p1_rho);


        Int_t i_effArea = 0 ; // effective area for pile up correction for DR04 combine rel. Iso
        if      ( fabs(recoSCEta) < 1.0                                        ) i_effArea = 0 ;
        else if ( fabs(recoSCEta) >= 1.0   && fabs(recoSCEta) < 1.479  ) i_effArea = 1 ;
        else if ( fabs(recoSCEta) >= 1.479 && fabs(recoSCEta) < 2.0    ) i_effArea = 2 ;
        else if ( fabs(recoSCEta) >= 2.0   && fabs(recoSCEta) < 2.2    ) i_effArea = 3 ;
        else if ( fabs(recoSCEta) >= 2.2   && fabs(recoSCEta) < 2.3    ) i_effArea = 4 ;
        else if ( fabs(recoSCEta) >= 2.3   && fabs(recoSCEta) < 2.4    ) i_effArea = 5 ;
        else if ( fabs(recoSCEta) >= 2.4                                       ) i_effArea = 6 ;


        //HEP photon cut ID
        // float s4 = 1-(e2x2Full5x5/e5x5Full5x5);
        // float s25 = 1-(e2x5Full5x5/e5x5Full5x5);

        //tight

        //     if( !(      1-r9 <= 0.226932)) tID += 1<<0   ;
        //     if( !(      sieieFull5x5 <= 0.010497)) tID += 1<<1   ;
        //     if( !(      s4 <= 0.246429)) tID += 1<<2   ;
        //     if( !(      s25 <= 0.0713786)) tID += 1<<3   ;
        //     if( !(      scEtaWidth <= 0.0142831)) tID += 1<<4   ;
        //     if( !(      scPhiWidth <= 0.0458085)) tID += 1<<5   ;
        //     if( !(      phoIso*0.01 <= 0.0996278)) tID += 1<<6   ;
        //     if( !(      chIso*0.01 <= 0.0134503)) tID += 1<<7   ;
        //     if( !(      chWorst*0.01 <= 0.107341)) tID += 1<<8   ;

        //     if( !(      1-r9 <= 0.163415)) mID += 1<<0   ;
        //     if( !(      sieieFull5x5 <= 0.0103467)) mID += 1<<1   ;
        //     if( !(      s4 <= 0.148124)) mID += 1<<2   ;
        //     if( !(      s25 <= 0.067214)) mID += 1<<3   ;
        //     if( !(      scEtaWidth <= 0.0134661)) mID += 1<<4   ;
        //     if( !(      scPhiWidth <= 0.0470788)) mID += 1<<5   ;
        //     if( !(      phoIso*0.01 <= 0.0367301)) mID += 1<<6   ;
        //     if( !(      chIso*0.01 <= 0.0231804)) mID += 1<<7   ;
        //     if( !(      chWorst*0.01 <= 0.651353)) mID += 1<<8   ;

        //     if( !(      1-r9 <= 0.278694)) lID += 1<<0   ;
        //     if( !(      sieieFull5x5 <= 0.0101336)) lID += 1<<1   ;
        //     if( !(      s4 <= 0.241925)) lID += 1<<2   ;
        //     if( !(      s25 <= 0.0757183)) lID += 1<<3   ;
        //     if( !(      scEtaWidth <= 0.0143202)) lID += 1<<4   ;
        //     if( !(      scPhiWidth <= 0.0408808)) lID += 1<<5   ;
        //     if( !(      phoIso*0.01 <= 0.0339198)) lID += 1<<6   ;
        //     if( !(      chIso*0.01 <= 0.00748054)) lID += 1<<7   ;
        //     if( !(      chWorst*0.01 <= 0.74293)) lID += 1<<8   ;
        if( !(      sieieFull5x5 <= 0.0109011)) tID += 1<<0   ;
        if( !(      phoIso*0.01 <= 0.132486)) tID += 1<<1   ;
        if( !(      chIso*0.01 <= 0.0124461)) tID += 1<<2   ;
        if( !(      chWorst*0.01 <= 0.14739)) tID += 1<<3   ;

        if( !(      sieieFull5x5 <= 0.0104677)) mID += 1<<0   ;
        if( !(      phoIso*0.01 <= 0.0292922)) mID += 1<<1   ;
        if( !(      chIso*0.01 <= 0.0220201)) mID += 1<<2   ;
        if( !(      chWorst*0.01 <= 0.239876)) mID += 1<<3   ;

        if( !(      sieieFull5x5 <= 0.0107464)) lID += 1<<0   ;
        if( !(      phoIso*0.01 <= 0.0319888)) lID += 1<<1   ;
        if( !(      chIso*0.01 <= 0.00673979)) lID += 1<<2   ;
        if( !(      chWorst*0.01 <= 0.513861)) lID += 1<<3   ;

        // fill in new tree end }}}
        tt->Fill();
    }

    tt->Write();
    fout->Close();

}


void pt_eta_rw2() {
    std::vector< const char* > inputfiles = {
        "/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/testing/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root",
        "/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/testing/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root",
        "/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/testing/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root"
    };

    ReweightHists hists;
    hists.WeightCounting(inputfiles);
    hists.WritingHists("rw_outFrag.Hists.root");


    int i=0;
    for ( const char* ifile : inputfiles )
        AppendWeightsToFile( ifile, hists, Form("rw_outFrag.%d.root",i++) );
}
void PrintHelp()
{
    printf("------------------------ User Manual ------------------------\n");
    printf("-- Calculate weight of signal and fake photon in gamma+jet --\n");
    printf("-- signal MC. This code weights to photon pt/eta spectrum. --\n");
    printf("-- Considering to statistics in MC, This code weight signal--\n");
    printf("-- photon distribution to fake distribution.               --\n");
    printf("-- Signal definition : 'isMatched == 1'                    --\n");
    printf("-- Fake   definition : 'isMatched != 1'                    --\n");
    printf("\n\n");
    printf("-- input arguments : paths to xAna root files. (separated  --\n");
    printf("-- by space.)                                              --\n");
    printf("-- for example : exec_ReweightTrainingSample a.root b.root --\n");
    printf("-- And it is recommended not to put a dataset of MC in one --\n");
    printf("-- file. Root TFile wuold reach the buffer limit.          --\n");
    printf("-- So this code is able to eat lots of root file.          --\n");
    throw "";
}
std::vector< const char* > GetInputs(int argc, const char** argv)
{
    std::vector< const char* > outputs;
    // arg 0 is the executable. So the input root files come from 1 to N
    for ( int i = 1; i < argc; ++i ) outputs.emplace_back(argv[i]);
    return outputs;
}

int main(int argc, const char** argv)
{
    std::vector< const char* > inputfiles = GetInputs( argc, argv );

    ReweightHists hists;
    hists.WeightCounting(inputfiles);
    hists.WritingHists("rw_outFrag.Hists.root");


    int i=0;
    for ( const char* ifile : inputfiles )
        AppendWeightsToFile( ifile, hists, Form("rw_outFrag.%d.root",i++) );
}
