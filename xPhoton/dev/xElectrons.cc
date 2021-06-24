#include "xPhoton/xPhoton/interface/xElectrons.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include <map>

enum candF
{
    mcE,
    mcPt,
    mcEta,
    mcPhi,
    recoE,
    recoPt,
    recoEta,
    recoPhi,
    totCandF
};
enum recoF
{
    recoPtCalib,
    recoSCEta,
    r9,
    HoverE,
    chIsoRaw,
    phoIsoRaw,
    nhIsoRaw,
    chWorstIso,
    rho,
    rawE,
    scEtaWidth,
    scPhiWidth,
    esRR,
    esEn,
    mva,
    mva_nocorr,
    officalIDmva,
    r9Full5x5,
    sieieFull5x5,
    sieipFull5x5,
    sipipFull5x5,
    e2x2Full5x5,
    e2x5Full5x5,
    totRecoF
};
enum recoI
{
    isMatched,
    firedTrgs,
    hasPixelSeed,
    IDbits,
    totRecoI
};
enum recoL
{
    firedTrgsL,
    totRecoL
};

enum evtI
{
    Run,
    xsweight,
    puwei,
    pthat,
    MET,
    METPhi,
    nVtx,
    nPU,
    totEvtI
};

enum evtL
{
    HLT,
    HLTPhoIsPrescaled,
    event,
    totEvtL
};



void xElectrons(
        std::vector<std::string> pathes,
        char oname[200] )
{
    TreeReader data(pathes);

    TFile *fout_;
    fout_ = new TFile(oname,"recreate");

    TTree *outtree_ = new TTree("t", "mini tree");
    

    std::map<int, Float_t > ele1CandF,ele2CandF, ZCandF;
    std::map<int, Float_t > ele1RecoF,ele2RecoF;
    std::map<int, Int_t   > ele1RecoI,ele2RecoI;
    std::map<int, Long64_t> ele1RecoL,ele2RecoL;
    std::map<int, Int_t   > eventI;
    std::map<int, Long64_t> eventL;

    /*
    std::map<candF, Float_t > ele1CandF,ele2CandF, ZCandF;
    std::map<recoF, Float_t > ele1RecoF,ele2RecoF;
    std::map<recoI, Int_t   > ele1RecoI,ele2RecoI;
    std::map<recoL, Long64_t> ele1RecoL,ele2RecoL;
    std::map<evtI , Int_t   > eventI;
    std::map<evtL , Long64_t> eventL;
    */
    for ( int i=0; i<totCandF; ++i )
    { ele1CandF[i] = 0; ele2CandF[i] = 0; ZCandF[i] = 0; }
    for ( int i=0; i<totRecoF; ++i )
    { ele1RecoF[i] = 0; ele2RecoF[i] = 0; }
    for ( int i=0; i<totRecoI; ++i )
    { ele1RecoI[i] = 0; ele2RecoI[i] = 0; }
    for ( int i=0; i<totRecoL; ++i )
    { ele1RecoL[i] = 0; ele2RecoL[i] = 0; }
    for ( int i=0; i<totEvtI; ++i )
    { eventI[i] = 0; }
    for ( int i=0; i<totEvtL; ++i )
    { eventL[i] = 0; }


    /*
    Float_t ele1CandF[totCandF], ele2CandF[totCandF], ZCandF[totCandF];
    Float_t ele1RecoF[totRecoF], ele2RecoF[totRecoF];
    Int_t   ele1RecoI[totRecoI], ele2RecoI[totRecoI];
    Int_t   eventI[totEvtI];

    Long64_t ele1RecoL[totRecoL], ele2RecoL[totRecoL];
    Long64_t eventL[totEvtL];
    */


    //ele1
// candF
outtree_->Branch("ele1.mcE",&ele1CandF[candF::mcE],"ele1.mcE/F");
outtree_->Branch("ele1.mcPt",&ele1CandF[candF::mcPt],"ele1.mcPt/F");
outtree_->Branch("ele1.mcEta",&ele1CandF[candF::mcEta],"ele1.mcEta/F");
outtree_->Branch("ele1.mcPhi",&ele1CandF[candF::mcPhi],"ele1.mcPhi/F");
outtree_->Branch("ele1.recoE",&ele1CandF[candF::recoE],"ele1.recoE/F");
outtree_->Branch("ele1.recoPt",&ele1CandF[candF::recoPt],"ele1.recoPt/F");
outtree_->Branch("ele1.recoEta",&ele1CandF[candF::recoEta],"ele1.recoEta/F");
outtree_->Branch("ele1.recoPhi",&ele1CandF[candF::recoPhi],"ele1.recoPhi/F");
// recoF
outtree_->Branch("ele1.recoPtCalib",&ele1RecoF[recoF::recoPtCalib],"ele1.recoPtCalib/F");
outtree_->Branch("ele1.recoSCEta",&ele1RecoF[recoF::recoSCEta],"ele1.recoSCEta/F");
outtree_->Branch("ele1.r9",&ele1RecoF[recoF::r9],"ele1.r9/F");
outtree_->Branch("ele1.HoverE",&ele1RecoF[recoF::HoverE],"ele1.HoverE/F");
outtree_->Branch("ele1.chIsoRaw",&ele1RecoF[recoF::chIsoRaw],"ele1.chIsoRaw/F");
outtree_->Branch("ele1.phoIsoRaw",&ele1RecoF[recoF::phoIsoRaw],"ele1.phoIsoRaw/F");
outtree_->Branch("ele1.nhIsoRaw",&ele1RecoF[recoF::nhIsoRaw],"ele1.nhIsoRaw/F");
outtree_->Branch("ele1.chWorstIso",&ele1RecoF[recoF::chWorstIso],"ele1.chWorstIso/F");
outtree_->Branch("ele1.rho",&ele1RecoF[recoF::rho],"ele1.rho/F");
outtree_->Branch("ele1.rawE",&ele1RecoF[recoF::rawE],"ele1.rawE/F");
outtree_->Branch("ele1.scEtaWidth",&ele1RecoF[recoF::scEtaWidth],"ele1.scEtaWidth/F");
outtree_->Branch("ele1.scPhiWidth",&ele1RecoF[recoF::scPhiWidth],"ele1.scPhiWidth/F");
outtree_->Branch("ele1.esRR",&ele1RecoF[recoF::esRR],"ele1.esRR/F");
outtree_->Branch("ele1.esEn",&ele1RecoF[recoF::esEn],"ele1.esEn/F");
outtree_->Branch("ele1.mva",&ele1RecoF[recoF::mva],"ele1.mva/F");
outtree_->Branch("ele1.mva_nocorr",&ele1RecoF[recoF::mva_nocorr],"ele1.mva_nocorr/F");
outtree_->Branch("ele1.officalIDmva",&ele1RecoF[recoF::officalIDmva],"ele1.officalIDmva/F");
outtree_->Branch("ele1.r9Full5x5",&ele1RecoF[recoF::r9Full5x5],"ele1.r9Full5x5/F");
outtree_->Branch("ele1.sieieFull5x5",&ele1RecoF[recoF::sieieFull5x5],"ele1.sieieFull5x5/F");
outtree_->Branch("ele1.sieipFull5x5",&ele1RecoF[recoF::sieipFull5x5],"ele1.sieipFull5x5/F");
outtree_->Branch("ele1.sipipFull5x5",&ele1RecoF[recoF::sipipFull5x5],"ele1.sipipFull5x5/F");
outtree_->Branch("ele1.e2x2Full5x5",&ele1RecoF[recoF::e2x2Full5x5],"ele1.e2x2Full5x5/F");
outtree_->Branch("ele1.e2x5Full5x5",&ele1RecoF[recoF::e2x5Full5x5],"ele1.e2x5Full5x5/F");
// recoI
outtree_->Branch("ele1.isMatched",&ele1RecoI[recoI::isMatched],"ele1.isMatched/I");
outtree_->Branch("ele1.firedTrgs",&ele1RecoI[recoI::firedTrgs],"ele1.firedTrgs/I");
outtree_->Branch("ele1.hasPixelSeed",&ele1RecoI[recoI::hasPixelSeed],"ele1.hasPixelSeed/I");
outtree_->Branch("ele1.IDbits",&ele1RecoI[recoI::IDbits],"ele1.IDbits/I");

// ele1 end

// Z
// candF
outtree_->Branch("Z.mcE",&ZCandF[candF::mcE],"Z.mcE/F");
outtree_->Branch("Z.mcPt",&ZCandF[candF::mcPt],"Z.mcPt/F");
outtree_->Branch("Z.mcEta",&ZCandF[candF::mcEta],"Z.mcEta/F");
outtree_->Branch("Z.mcPhi",&ZCandF[candF::mcPhi],"Z.mcPhi/F");
outtree_->Branch("Z.recoE",&ZCandF[candF::recoE],"Z.recoE/F");
outtree_->Branch("Z.recoPt",&ZCandF[candF::recoPt],"Z.recoPt/F");
outtree_->Branch("Z.recoEta",&ZCandF[candF::recoEta],"Z.recoEta/F");
outtree_->Branch("Z.recoPhi",&ZCandF[candF::recoPhi],"Z.recoPhi/F");


// evt
// evtI
outtree_->Branch("evt.Run",&eventI[evtI::Run],"evt.Run/I");
outtree_->Branch("evt.xsweight",&eventI[evtI::xsweight],"evt.xsweight/I");
outtree_->Branch("evt.puwei",&eventI[evtI::puwei],"evt.puwei/I");
outtree_->Branch("evt.pthat",&eventI[evtI::pthat],"evt.pthat/I");
outtree_->Branch("evt.MET",&eventI[evtI::MET],"evt.MET/I");
outtree_->Branch("evt.METPhi",&eventI[evtI::METPhi],"evt.METPhi/I");
outtree_->Branch("evt.nVtx",&eventI[evtI::nVtx],"evt.nVtx/I");
outtree_->Branch("evt.nPU",&eventI[evtI::nPU],"evt.nPU/I");

// evtL
outtree_->Branch("evt.HLT",&eventL[evtL::HLT],"evt.HLT/L");
outtree_->Branch("evt.HLTPhoIsPrescaled",&eventL[evtL::HLTPhoIsPrescaled],"evt.HLTPhoIsPrescaled/L");
outtree_->Branch("evt.event",&eventL[evtL::event],"evt.event/L");









/*






// recoL
outtree_->Branch("BRAHfiredTrgsL",&firedTrgsL,"BRAHfiredTrgsL/L");

// evtL
outtree_->Branch("BRAHHLT",&HLT,"BRAHHLT/L");
outtree_->Branch("BRAHHLTPhoIsPrescaled",&HLTPhoIsPrescaled,"BRAHHLTPhoIsPrescaled/L");
outtree_->Branch("BRAHevent",&event,"BRAHevent/L");

// recoI
outtree_->Branch("BRAHisMatched",&isMatched,"BRAHisMatched/I");
outtree_->Branch("BRAHfiredTrgs",&firedTrgs,"BRAHfiredTrgs/I");
outtree_->Branch("BRAHhasPixelSeed",&hasPixelSeed,"BRAHhasPixelSeed/I");
outtree_->Branch("BRAHIDbits",&IDbits,"BRAHIDbits/I");

// evtI
outtree_->Branch("BRAHRun",&Run,"BRAHRun/I");
outtree_->Branch("BRAHxsweight",&xsweight,"BRAHxsweight/I");
outtree_->Branch("BRAHpuwei",&puwei,"BRAHpuwei/I");
outtree_->Branch("BRAHpthat",&pthat,"BRAHpthat/I");
outtree_->Branch("BRAHMET",&MET,"BRAHMET/I");
outtree_->Branch("BRAHMETPhi",&METPhi,"BRAHMETPhi/I");
outtree_->Branch("BRAHnVtx",&nVtx,"BRAHnVtx/I");
outtree_->Branch("BRAHnPU",&nPU,"BRAHnPU/I");

// candF
outtree_->Branch("BRAHmcE",&mcE,"BRAHmcE/F");
outtree_->Branch("BRAHmcPt",&mcPt,"BRAHmcPt/F");
outtree_->Branch("BRAHmcEta",&mcEta,"BRAHmcEta/F");
outtree_->Branch("BRAHmcPhi",&mcPhi,"BRAHmcPhi/F");
outtree_->Branch("BRAHrecoE",&recoE,"BRAHrecoE/F");
outtree_->Branch("BRAHrecoPt",&recoPt,"BRAHrecoPt/F");
outtree_->Branch("BRAHrecoEta",&recoEta,"BRAHrecoEta/F");
outtree_->Branch("BRAHrecoPhi",&recoPhi,"BRAHrecoPhi/F");

// recoF
outtree_->Branch("BRAHrecoPtCalib",&recoPtCalib,"BRAHrecoPtCalib/F");
outtree_->Branch("BRAHrecoSCEta",&recoSCEta,"BRAHrecoSCEta/F");
outtree_->Branch("BRAHr9",&r9,"BRAHr9/F");
outtree_->Branch("BRAHHoverE",&HoverE,"BRAHHoverE/F");
outtree_->Branch("BRAHchIsoRaw",&chIsoRaw,"BRAHchIsoRaw/F");
outtree_->Branch("BRAHphoIsoRaw",&phoIsoRaw,"BRAHphoIsoRaw/F");
outtree_->Branch("BRAHnhIsoRaw",&nhIsoRaw,"BRAHnhIsoRaw/F");
outtree_->Branch("BRAHchWorstIso",&chWorstIso,"BRAHchWorstIso/F");
outtree_->Branch("BRAHrho",&rho,"BRAHrho/F");
outtree_->Branch("BRAHrawE",&rawE,"BRAHrawE/F");
outtree_->Branch("BRAHscEtaWidth",&scEtaWidth,"BRAHscEtaWidth/F");
outtree_->Branch("BRAHscPhiWidth",&scPhiWidth,"BRAHscPhiWidth/F");
outtree_->Branch("BRAHesRR",&esRR,"BRAHesRR/F");
outtree_->Branch("BRAHesEn",&esEn,"BRAHesEn/F");
outtree_->Branch("BRAHmva",&mva,"BRAHmva/F");
outtree_->Branch("BRAHmva_nocorr",&mva_nocorr,"BRAHmva_nocorr/F");
outtree_->Branch("BRAHofficalIDmva",&officalIDmva,"BRAHofficalIDmva/F");
outtree_->Branch("BRAHr9Full5x5",&r9Full5x5,"BRAHr9Full5x5/F");
outtree_->Branch("BRAHsieieFull5x5",&sieieFull5x5,"BRAHsieieFull5x5/F");
outtree_->Branch("BRAHsieipFull5x5",&sieipFull5x5,"BRAHsieipFull5x5/F");
outtree_->Branch("BRAHsipipFull5x5",&sipipFull5x5,"BRAHsipipFull5x5/F");
outtree_->Branch("BRAHe2x2Full5x5",&e2x2Full5x5,"BRAHe2x2Full5x5/F");
outtree_->Branch("BRAHe2x5Full5x5",&e2x5Full5x5,"BRAHe2x5Full5x5/F");
*/
    
    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
        data.GetEntry(ev);
        // 1. load data
        // 2. build electron 4mom and pass electron preselection
        // 3. build Z candidate and reject event.
        // 4. mc truth matching.
        // 5. fill tree
        outtree_->Fill();
    }


    fout_->cd();
    outtree_->Write();
    fout_->Close();
    LOG_INFO("All %lld Events processed", data.GetEntriesFast());
}
void xElectrons(std::string ipath, int outID)
{
   char fname[200];
   std::vector<std::string> pathes;

   pathes.push_back(ipath);

   char oname[200];
   sprintf(oname, "output_job_PhotonHFJet_%d.root", outID);

   xElectrons(pathes, oname);
}

