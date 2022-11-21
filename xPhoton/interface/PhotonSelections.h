#ifndef photonpreselection
#define photonpreselection
#include <TMath.h>
#include <TMVA/Reader.h>
/* #include <TRandom3.h> */
#include <TFile.h>
#include <TGraph.h>
#include <string>
#include <map>
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/ShowerShapeCorrectionAdapter.h"

        
// pre-selection of photon.
Int_t PhotonPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto=kTRUE);

//Int_t PhotonSkimPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto=kTRUE);
//Int_t HggPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto=kTRUE);

//void select_photon(Int_t iWP, TreeReader &data, std::vector<int>& accepted);

//float select_photon_mva(TreeReader &data, Int_t i, TGraph *tgr[20]);

// only for RS trained xml file!!!!!
//float select_photon_mvanoIso(TreeReader &data, Int_t i, TGraph *tgr[20]);
//float select_photon_mvanoIso(TreeReader &data, Int_t i, std::map<std::string, TGraph *> barrelCorr, std::map<std::string, TGraph *> endcapCorr);
//float select_photon_mvanoIso(TreeReader &data, Int_t i, ShowerShapeCorrectionAdapter& SScorr);


//float select_photon_mva_hgg(TreeReader &data, Int_t i);
bool passSelection_PhotonKinematicParameters( float pt, float eta );

struct MVAVariables
{
    float
        recoPhi,
        r9Full5x5,
        sieieFull5x5,
        sieipFull5x5,
        s4Full5x5,
        recoSCEta,
        rawE,
        scEtaWidth,
        scPhiWidth,

        esEnergyOverSCRawEnergy,
        esRR,
        rho;
    virtual void LoadVars( int varIdx ) { }
    bool isEndcap() { return fabs(recoSCEta) > 1.5; }
    virtual ~MVAVariables() {}
};
//void LoadVars_ggAnalysis( TreeReader* data_, std::

class PhotonMVACalculator
{
    public:
        PhotonMVACalculator( TreeReader* data_, std::string dataEra_ );
        virtual ~PhotonMVACalculator();

        float GetMVA_noIso( Int_t iPho_, ShowerShapeCorrectionAdapter* SScorr_ );
        float GetMVA_noIso( Int_t iPho_, TGraph* tgr[8]);
        float GetMVA_noIso( Int_t iPho_ );
    private:
        TreeReader* _data;
        std::string _dataEra;
        TMVA::Reader* tmvaReader[2];

        virtual void LoadingVars( Int_t iPho_ );
        void ShowerShapeCorrection( TGraph* tgr[8] );
        void ShowerShapeCorrection( ShowerShapeCorrectionAdapter* SScorr_ );

        // mva variables
        float phoPhi, phoR9Full5x5;
        //float phoPhi, phoR9;
        float phoSCEtaWidth, phoSCPhiWidth, rho;
        float phoSCEta, phoSCRawE;
        float phoPFPhoIso, phoPFChIso, phoPFChIsoWorst;
        float phoESEnToRawE, phoESEffSigmaRR;

        float sieieFull5x5, sieipFull5x5, s13Full5x5, s4Full5x5, s25Full5x5;
        // s13, s25 is disabled
        // PFPhoIso, PFChIso and PFChIsoWorst are disabled
        bool isEE;
};
//class PhotonMVACalculator_fromxPhoton : public PhotonMVACalculator

#endif
