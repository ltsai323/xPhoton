#include "xPhoton/xPhoton/interface/xQCDChecker.h"
#include <vector>
#include <TH1D.h>
#include <TLorentzVector.h>


#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TMath.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
using namespace std;
#include <iostream>
#include <TProfile.h>
#include <map>
#include <TNtuple.h>

#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/recoInfo.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include "xPhoton/xPhoton/interface/BTagCalibrationStandalone.h"
#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
#include "xPhoton/xPhoton/interface/JetIDMgr.h"
#include "xPhoton/xPhoton/interface/ShowerShapeCorrectionAdapter.h"
#include "xPhoton/xPhoton/interface/RhoCorrection.h"

#define TEST(format, args...)     fprintf(stderr, ":%20s>>  " format "\n", __PRETTY_FUNCTION__,  ##args)
//#define TESTING
// switches

#define NOTHINGFOUND -1
#define INITVAL -999
namespace _xqcd_{
    void FillStatus(TH1* hist, float val) { hist->Fill(val+0.001); }
};
using namespace _xqcd_;
using namespace std;

struct xQCDTreeContent
{
    xQCDTreeContent(TTree* tout)
    { Clear(); SetMyBranch(tout); }
    void Clear()
    {
        _genidxRec.clear();

        lhePt.clear();
        lheEta.clear();
        lhePhi.clear();
        lheE.clear();
        lhePID.clear();
        lheDeltaR.clear();
        lhePtDiff.clear();
        lheNum = INITVAL;

        leadingJetRawPt = INITVAL;
        leadingJetRawE = INITVAL;
        leadingJetE = INITVAL;
        leadingJetPt = INITVAL;
        leadingJetEta = INITVAL;
        leadingJetPhi = INITVAL;
        leadingJetGenPt = INITVAL;
        leadingJetGenEta = INITVAL;
        leadingJetGenPhi = INITVAL;
        leadingJetHadFlvr = INITVAL;
        leadingJetGenPartonID = INITVAL;
        leadingJetPartonID = INITVAL;
        GenHT = INITVAL;
        genHT_pthatDef = INITVAL;
        MET = INITVAL;

        pthat_PU.clear();
    }
    void AddGenIdx(int idx)
    { _genidxRec.push_back(idx); }
    vector<int>& GenIdxs()
    { return _genidxRec; }
    void SetMyBranch(TTree* t)
    {
        t->Branch("lheNum",   &lheNum);
        t->Branch("lhePt",    &lhePt);
        t->Branch("lheEta",   &lheEta);
        t->Branch("lhePhi",   &lhePhi);
        t->Branch("lheE",     &lheE);
        t->Branch("lhePID",   &lhePID);
        t->Branch("lheDeltaR",&lheDeltaR);
        t->Branch("lhePtDiff",&lhePtDiff);

        t->Branch("leadingJetRawE",   &leadingJetRawE,    "leadingJetRawE/F");
        t->Branch("leadingJetRawPt",  &leadingJetRawPt,   "leadingJetRawPt/F");
        t->Branch("leadingJetE",      &leadingJetE,       "leadingJetE/F");
        t->Branch("leadingJetPt",     &leadingJetPt,      "leadingJetPt/F");
        t->Branch("leadingJetEta",    &leadingJetEta,     "leadingJetEta/F");
        t->Branch("leadingJetPhi",    &leadingJetPhi,     "leadingJetPhi/F");
        t->Branch("leadingJetGenPt",  &leadingJetGenPt,   "leadingJetGenPt/F");
        t->Branch("leadingJetGenEta", &leadingJetGenEta,  "leadingJetGenEta/F");
        t->Branch("leadingJetGenPhi", &leadingJetGenPhi,  "leadingJetGenPhi/F");
        t->Branch("leadingJetHadFlvr",&leadingJetHadFlvr, "leadingJetHadFlvr/I");
        t->Branch("leadingJetPartonID",&leadingJetPartonID, "leadingJetPartonID/I");
        t->Branch("leadingJetGenPartonID",&leadingJetGenPartonID, "leadingJetGenPartonID/I");
        t->Branch("GenHT",            &GenHT,             "GenHT/F");
        t->Branch("genHT_pthatDef", &genHT_pthatDef, "genHT_pthatDef/F");
        t->Branch("MET",              &MET,               "MET/F");
        t->Branch("pthat_PU" ,&pthat_PU);
    }

    Int_t lheNum;
    vector<Float_t> lhePt;
    vector<Float_t> lheEta;
    vector<Float_t> lhePhi;
    vector<Float_t> lheE;
    vector<Int_t  > lhePID;
    vector<Float_t> lhePtDiff;
    vector<Float_t> lheDeltaR;
    vector<Float_t> pthat_PU;
    Float_t GenHT;
    Float_t genHT_pthatDef;
    Float_t MET;
    
    Float_t leadingJetRawE;
    Float_t leadingJetRawPt;
    Float_t leadingJetE;
    Float_t leadingJetPt;
    Float_t leadingJetEta;
    Float_t leadingJetPhi;
    Float_t leadingJetGenPt;
    Float_t leadingJetGenEta;
    Float_t leadingJetGenPhi;
    Int_t   leadingJetHadFlvr;
    Int_t   leadingJetPartonID;
    Int_t   leadingJetGenPartonID;

    // used for record event
    vector<int> _genidxRec;
};
void FillEvent(TreeReader* data, xQCDTreeContent* evt)
{
    Int_t*   lhePID = data->GetPtrInt  ("lhePID");
    Float_t* lheE   = data->GetPtrFloat("lheE");
    Float_t* lhePx  = data->GetPtrFloat("lhePx");
    Float_t* lhePy  = data->GetPtrFloat("lhePy");
    Float_t* lhePz  = data->GetPtrFloat("lhePz");

    Float_t  genHT  = data->GetFloat("genHT");
    Float_t  MET    = data->GetFloat("pfMET");


    Int_t    nJet   = data->GetInt("nJet");
    Float_t* jetRawEn  = data->GetPtrFloat("jetRawEn");
    Float_t* jetRawPt  = data->GetPtrFloat("jetRawPt");
    Float_t* jetPt  = data->GetPtrFloat("jetPt");
    Float_t* jetEn  = data->GetPtrFloat("jetEn");
    Float_t* jetEta = data->GetPtrFloat("jetEta");
    Float_t* jetPhi = data->GetPtrFloat("jetPhi");

    //Int_t*   jetPartonID = data->GetPtrInt("jetPartonID");
    Int_t*   jetHadFlvr = data->GetPtrInt("jetHadFlvr");
    Int_t*   jetPartonID    = data->GetPtrInt("jetPartonID");
    Int_t*   jetGenPartonID = data->GetPtrInt("jetGenPartonID");

    Float_t* jetGenJetPt  = data->GetPtrFloat("jetGenJetPt");
    //Float_t* jetGenJetEn  = data->GetPtrFloat("jetGenJetEn");
    Float_t* jetGenJetEta = data->GetPtrFloat("jetGenJetEta");
    Float_t* jetGenJetPhi = data->GetPtrFloat("jetGenJetPhi");

    Float_t* pupthat_max = data->GetPtrFloat("pupthat_max");
    Int_t    nPU = data->GetInt("nPUInfo");

    float ptsum = 0;
    for( int lheIdx : evt->GenIdxs() )
    {
        TLorentzVector lheP4;
        ptsum += lheP4.Pt();
        lheP4.SetPxPyPzE( lhePx[lheIdx], lhePy[lheIdx], lhePz[lheIdx], lheE[lheIdx] );
        evt->lhePt         .push_back(lheP4.Pt());
        evt->lheEta        .push_back(lheP4.Eta());
        evt->lhePhi        .push_back(lheP4.Phi());
        evt->lheE          .push_back(lheP4.E());
        evt->lhePID        .push_back(lhePID[lheIdx]);

        if ( nJet > 0 )
        {
            TLorentzVector jetP4;
            jetP4.SetPtEtaPhiE( jetPt[0], jetEta[0], jetPhi[0], jetEn[0] );

            evt->lheDeltaR.push_back(jetP4.DeltaR(lheP4));
            evt->lhePtDiff.push_back(fabs(jetP4.Pt()-lheP4.Pt()) / lheP4.Pt());
        }
    }
    evt->lheNum = evt->GenIdxs().size();
    evt->GenHT               = genHT;
    evt->genHT_pthatDef      = ptsum / evt->GenIdxs().size();
    evt->MET                 = MET;
    if ( nJet > 0 )
    {
        evt->leadingJetRawE      = jetRawEn[0];
        evt->leadingJetRawPt     = jetRawPt[0];
        evt->leadingJetE         = jetEn[0];
        evt->leadingJetPt        = jetPt[0];
        evt->leadingJetEta       = jetEta[0];
        evt->leadingJetPhi       = jetPhi[0];
        evt->leadingJetGenPt     = jetGenJetPt[0];
        evt->leadingJetGenEta    = jetGenJetEta[0];
        evt->leadingJetGenPhi    = jetGenJetPhi[0];
        evt->leadingJetHadFlvr   = jetHadFlvr[0];
        evt->leadingJetPartonID  = jetPartonID[0];
        evt->leadingJetGenPartonID = jetGenPartonID[0];
    }

    for ( Int_t iPU = 0; iPU < nPU; ++iPU )
        evt->pthat_PU.push_back( pupthat_max[iPU] );
}


void xQCDChecker(vector<string> pathes, Char_t oname[200], const std::string dataEra)
{
    LOG_INFO("end of loading csv file");


    TreeReader data(pathes);


    TFile* fout = new TFile(oname,"recreate");
    fout->cd();
    TTree* tout = new TTree("t", "");

    xQCDTreeContent storage(tout);


    LOG_INFO(" processing entries %lld \n", data.GetEntriesFast());


    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
        if ( ev %10000 == 0 ) 
            LOG_INFO(" processing entries %lld in %lld \n", ev, data.GetEntriesFast());

        data.GetEntry(ev);
        storage.Clear();

        Int_t    nLHE   = data.GetInt("nLHE");
        Float_t* lhePx  = data.GetPtrFloat("lhePx");
        Float_t* lhePy  = data.GetPtrFloat("lhePy");

        /*
        // pt sorting
        std::map<float, int, std::greater<float>> genIdx_ptSorted;
        for ( int iLHE = 0; iLHE < nLHE; ++iLHE )
        {
            float pt2 = lhePx[iLHE]*lhePx[iLHE] + lhePy[iLHE]*lhePy[iLHE];
            genIdx_ptSorted[ pt2 ] = iLHE;
        }
        for ( auto iter = genIdx_ptSorted.begin(); iter != genIdx_ptSorted.end(); ++iter )
        { storage.AddGenIdx(iter->second); }
        */
        // orig sorting
        for ( int iLHE = 0; iLHE < nLHE; ++iLHE )
        { storage.AddGenIdx(iLHE); }

        FillEvent( &data, &storage );

        tout->Fill();
#ifdef TESTING
        if ( ev > 1000 ) break;
#endif

    } // event loop end

    fout->cd();
    tout->Write();


    fout->Close();

    fprintf(stderr, "Processed all events\n");

}




void xQCDChecker(std::vector<std::string> ipath, int outID, const std::string dataEra)
{

    Char_t oname[200];
    sprintf(oname, "output_job_PhotonHFJet_%d.root", outID);

    xQCDChecker(ipath, oname, dataEra);

}
