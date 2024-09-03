#include <iostream>

#define MAXBIT 8

struct PtRangeBoundary
{
    PtRangeBoundary( float low, float high, int sep ) : _low(low), _high(high), _sep(sep) // sep is the bin width
    { }
    PtRangeBoundary() : _low(0),_high(1),_sep(1) {}
    float _low, _high; int _sep;
    //int nbin() const { return (_high-_low) / float(_sep); }
    int nbin() const { return 40; }
    int sep()  const { return _sep; }
    float xmin() const { return _low; }
    float xmax() const { return _high;}
    const char* Formatted(const char* histname) const { return Form("%s(%d,%.1f,%.1f)",histname, nbin(),xmin(),xmax()); }
};
PtRangeBoundary GetPtRangeBoundary(int HLTbit)
{
    if ( HLTbit == 0 ) // EG22
        return PtRangeBoundary( 10, 50, 1);
    if ( HLTbit == 1 ) // EG30
        return PtRangeBoundary( 25, 80, 1);
    if ( HLTbit == 2 ) // EG36
        return PtRangeBoundary( 28,100, 2);
    if ( HLTbit == 3 ) // EG50
        return PtRangeBoundary( 40,120, 2);
    if ( HLTbit == 4 ) // EG75
        return PtRangeBoundary( 60,150, 2);
    if ( HLTbit == 5 ) // EG90
        return PtRangeBoundary( 80,200, 2);
    if ( HLTbit == 6 ) // EG120
        return PtRangeBoundary(100,250, 2);
    if ( HLTbit == 7 ) // EG175
        return PtRangeBoundary(150,400, 2);
    if ( HLTbit == 8 ) // EG300er
        return PtRangeBoundary(200,800, 2);
    return PtRangeBoundary();
}

const char* EventSelections_EndcapPhoton()
{ return "phoPFChIso[0]<2&&((phoIDbit[0]>>2)&1) == 1 && phoIDMVA[0] > 0.9  && fabs(phoEta[0]) > 1.5 && phoEleVeto[0] == 1"; }
const char* EventSelections_BarrelPhoton()
{ return "phoPFChIso[0]<2&&((phoIDbit[0]>>2)&1) == 1 && phoIDMVA[0] > 0.9  && fabs(phoEta[0]) < 1.5 && phoEleVeto[0] == 1"; }

const char* EventSelections()
//{ return EventSelections_EndcapPhoton(); }
{ return EventSelections_BarrelPhoton(); }
const char* PassTrg(int ibit)
{ return Form("( ((phoFiredSingleTrgs[0]>>%d)&1) == 1 )", ibit); }
const char* PassJetTrg()
{ return "jetFiredTrgs[0]!=0"; }
const char* FailJetTrg()
{ return "jetFiredTrgs[0]==0"; }
const char* FailTrg(int ibit)
{ return Form("( ((phoFiredSingleTrgs[0]>>%d)&1) == 0 )", ibit); }


TString Selections( const std::vector<const char*>& cuts )
{
    TString output="nPho>0 && nJet>0";
    for ( auto cut : cuts )
    { output += "&&"; output += TString(cut); }
    return output;
}
void HLTPassingHists( TTree* tin, int ibin_HLT )
{
    int rangeBit = ibin_HLT;
    PtRangeBoundary rangeDef = GetPtRangeBoundary(rangeBit);
    if ( ibin_HLT == MAXBIT ) ibin_HLT = MAXBIT-1;


    const char* hLow        = Form("Range%d_passingJetHLT",
            rangeBit);
    tin->Draw( Form("phoEt[0] >> %s", rangeDef.Formatted(hLow) ), 
        Selections({EventSelections(), PassJetTrg()                          }).Data()
        );

    const char* hHigh       = Form("Range%d_passingHLT%d",
            rangeBit, ibin_HLT );
    tin->Draw( Form("phoEt[0] >> %s", rangeDef.Formatted(hHigh)), 
        Selections({EventSelections(),                    PassTrg(ibin_HLT+1)}).Data()
        );

    const char* hAll        = Form("Range%d",
            rangeBit);
    tin->Draw( Form("phoEt[0] >> %s", rangeDef.Formatted(hAll) ), 
        Selections({EventSelections()                                        }).Data()
        );

    const char* hBoth       = Form("Range%d_passingBothJetHLT%d",
            rangeBit, ibin_HLT);
    tin->Draw( Form("phoEt[0] >> %s", rangeDef.Formatted(hBoth)), 
        Selections({EventSelections(), PassTrg(ibin_HLT), PassJetTrg()       }).Data()
        );

    const char* hOnlyLow    = Form("Range%d_passingHLT%d_noJetTrg",
            rangeBit, ibin_HLT );
    tin->Draw( Form("phoEt[0] >> %s", rangeDef.Formatted(hOnlyLow)),
        Selections({EventSelections(), PassTrg(ibin_HLT), FailJetTrg()       }).Data()
        );

    const char* hOnlyHigh   = Form("Range%d_passingJetHLT_noHLT%d",
            rangeBit, ibin_HLT );
    tin->Draw( Form("phoEt[0] >> %s", rangeDef.Formatted(hOnlyHigh)),
        Selections({EventSelections(), FailTrg(ibin_HLT), PassJetTrg()       }).Data()
        );
    const char* hTurnOn     = Form("Range%d_triggerTurnOn",
            rangeBit);
    TH1* hNumerator   = (TH1*) gROOT->FindObject(hBoth)->Clone();
    TH1* hDenominator = (TH1*) gROOT->FindObject(hLow);
    hNumerator->SetName(hTurnOn);
    hNumerator->Divide(hDenominator);
}
void TriggerTurnOnGGNtupleMaterials_AbsTriggerEfficiency(const char* ifile = "../2016.data.root", const char* ofile = "HLTTurnOnChecking.root")
{
    TFile* f = TFile::Open(ifile);
    TTree* t = (TTree*) f->Get("ggNtuplizer/EventTree");
    TFile* fout = new TFile(ofile, "RECREATE");
    fout->cd();
    for ( int ibin = 0; ibin <= MAXBIT; ++ibin )
    {
        printf("processing range %d in %d\n", ibin, MAXBIT);
        HLTPassingHists(t, ibin);
    }
    fout->Write();
    fout->Close();
}
