#include "ptbin_definitions.h"
#include <fstream>
using RDF = ROOT::RDataFrame;
std::vector<float> phopt_def;

float get_mc_weight(const char* inputFILEname)
{
    auto ifile = TFile::Open(inputFILEname);
    auto itree = (TTree*) ifile->Get("t");
    float mcweight = 0;
    itree->SetBranchAddress("mcweight",&mcweight);
    itree->GetEntry(3);
    float output = mcweight;
    ifile->Close();
    return output;
}
struct LumiRDF
{
    LumiRDF( double lumi, const char* ifilename ) :
        _lumi(lumi), _ifilename(ifilename), _rdf("selRes", _ifilename),
        // remove testing events
        node(_rdf.Filter("GenPhoNumbering==0") ) { }

    LumiRDF( const char* ifilename ) :
        _ifilename(ifilename), _rdf("selRes", _ifilename),
        // remove testing events
        node(_rdf.Filter("GenPhoNumbering==0") ) {
        _lumi = get_mc_weight(ifilename);
        }

    double _lumi;
    const char* _ifilename;
    RDF _rdf;

    double LumiWeight() const { return _lumi; }
    ROOT::RDF::RNode node;
};

const char* PhoEtaCut(int bin)
{
    if ( bin == 0 ) // is barrel
        return "(fabs(mcEta)<1.4442)";
    if ( bin == 1 ) // is endcap
        return "(fabs(mcEta)>1.566 && fabs(mcEta)<2.5)";
    return "input photon eta bin is undefined";
}
const char* JetEtaCut(int bin)
{ return "1"; } // disable this cut
const char* PhoPtCut(int ibin)
{
    if ( ibin == phopt_def.size()-1 )
        return Form("(mcPt>%.3f)",phopt_def[ibin]);
    if ( ibin < phopt_def.size()-1 )
        return Form("(mcPt>%.3f && mcPt<%.3f)",phopt_def[ibin],phopt_def[ibin+1]);
    return "input photon pt bin is out of range";
}

struct value_and_error
{ float nominal_value; float std_error2; 
    value_and_error() { nominal_value = std_error2 = 0; }
};
class efficiency_record
{
    public:
    value_and_error passed;
    value_and_error total;

    efficiency_record() : passed(),total() {}
    value_and_error get_efficiency()
    {
        value_and_error eff;

        // passed values
        float pv = passed.nominal_value;
        float pe2= passed.std_error2;
        float tv = total.nominal_value;
        float te2= total.std_error2;
        // failed values
        float fv = tv - pv;
        float fe2= te2 - pe2;

        if ( pv == 0 ) return eff;

        eff.nominal_value = pv / tv;
        eff.std_error2 = pe2*(fv/tv/tv)*(fv/tv/tv) + fe2*(pv/tv/tv)*(pv/tv/tv);
        return eff;
    }
};
efficiency_record BinnedPreSelEfficiency( const std::vector<LumiRDF*>& rdfs,
        int pEtaBin, int jEtaBin, int pPtBin )
{
    double totalSel = 0.;
    double totalEvt = 0.;

    efficiency_record eff;
    for ( unsigned idx = 0; idx < rdfs.size() ; ++idx )
    {
        const char* ptcut = PhoPtCut(pPtBin);
        const char* etacut = PhoEtaCut(pEtaBin);
        const char* jetcut = "";

        auto binnednode = ROOT::RDF::RNode(
                rdfs[idx]->node.Filter( Form("%s && %s",ptcut,etacut) )
                );
        auto binnednode_passsed = ROOT::RDF::RNode( binnednode.Filter("passed==1") );

        totalSel += *(binnednode_passsed.Count()) * rdfs[idx]->LumiWeight();
        totalEvt += *(binnednode        .Count()) * rdfs[idx]->LumiWeight();
        double passed_val = *(binnednode_passsed.Count());
        double total__val = *(binnednode        .Count());
        eff.passed.nominal_value += passed_val * rdfs[idx]->LumiWeight();
        eff.passed.std_error2 += passed_val * rdfs[idx]->LumiWeight() * rdfs[idx]->LumiWeight();
        eff.total.nominal_value += total__val * rdfs[idx]->LumiWeight();
        eff.total.std_error2 += total__val * rdfs[idx]->LumiWeight() * rdfs[idx]->LumiWeight();
    }

    return eff;
}
struct OutputModule
{
    OutputModule(const char* oFILEname, const char* columnDEFINITION)
    {
        output.open(oFILEname);
        output << columnDEFINITION << "\n";
    }
    virtual void Write( int pETAbin, int jETAbin, int pPTbin, value_and_error rec) = 0;
    virtual ~OutputModule() { output.close(); }
    
    std::ofstream output;
};
struct OutputModule_TreeText : OutputModule
{
    OutputModule_TreeText(const char* oFILEname) :
        OutputModule(oFILEname, "ptbin/I:EBEE/I:jetbin/I:efficiency/F:error/F") { }

    virtual void Write( int pETAbin, int jETAbin, int pPTbin, value_and_error rec ) override
    { output << Form("%d %d %d %.10f %.10f\n", pPTbin,pETAbin,jETAbin, rec.nominal_value, sqrt(rec.std_error2)); }

};
void preselection_efficiency(const std::vector<const char*> iFILEnames)
{
    ROOT::EnableImplicitMT();
    const char* oFileName = "dat_preselectionEfficiency.dat";
    std::vector<LumiRDF*> rdfs;
    rdfs.reserve(iFILEnames.size());
    for ( auto ifilename : iFILEnames )
        rdfs.push_back( new LumiRDF(ifilename) );

    phopt_def = ptbin_ranges(); // from makehisto.h
    const int NUMBIN_PHOPT = phopt_def.size();

    OutputModule* outs = new OutputModule_TreeText(oFileName);
    for ( int pEtaBin = 0; pEtaBin < 2; ++pEtaBin )
        for ( int jEtaBin = 0; jEtaBin < 3; ++jEtaBin )
            //for ( int pPtBin = 0; pPtBin < NUMBIN_PHOPT- 1; ++pPtBin )
            for ( int pPtBin = 0; pPtBin < NUMBIN_PHOPT; ++pPtBin )
    // for test
    // for ( int pEtaBin = 0; pEtaBin < 1; ++pEtaBin ) // for test
    //     for ( int jEtaBin = 0; jEtaBin < 1; ++jEtaBin )
    //         for ( int pPtBin = 0; pPtBin < 1; ++pPtBin )
    {
        efficiency_record efficiency = BinnedPreSelEfficiency( rdfs, pEtaBin, jEtaBin, pPtBin );
        value_and_error eff = efficiency.get_efficiency();

        outs->Write(pEtaBin,jEtaBin,pPtBin, eff);
    }
    delete outs;

    for ( auto rdf_ptr : rdfs )
        delete rdf_ptr;
}
void preselectionEfficiency()
{
    std::vector<const char*> iFileNames({
    "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root",
    "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root",
    "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root"});
    preselection_efficiency(iFileNames);
}
