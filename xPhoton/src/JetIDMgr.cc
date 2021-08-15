#include "xPhoton/xPhoton/interface/JetIDMgr.h"
#include <exception>

void EtaIsOutOfRange()
{ throw std::out_of_range( "JetIDCuts() : Input jet Eta is out of range()\n"); }
// -1 : skip this.
// The bigger and smaller relation needs to check twiki.
std::map<std::string,std::pair<float,float>> JetIDCuts_ULRun2016_CHS( float jetEta )
{
    float abseta = fabs(jetEta);
    if ( abseta < 2.4 )
        return std::map<std::string,std::pair<float,float>>( {
                {"Fraction_NeutralHadron", { NO_SELECTION, 0.9          } },
                {"Fraction_NeutralEM",     { NO_SELECTION, 0.9          } },
                {"NumOfConstituents",      { 1.0         , NO_SELECTION } },
                {"Fraction_Muon",          { NO_SELECTION, 0.8          } },
                {"Fraction_ChargedHadron", { 0.          , NO_SELECTION } },
                {"ChargedMultiplicity",    { 0.          , NO_SELECTION } },
                {"Fraction_ChargedEM",     { NO_SELECTION, 0.8          } },
                {"NumOfNeutralParticle",   { NO_SELECTION, NO_SELECTION } }
                } );
    if ( abseta < 2.7 )
        return std::map<std::string,std::pair<float,float>>( {
                {"Fraction_NeutralHadron", { NO_SELECTION, 0.9          } },
                {"Fraction_NeutralEM",     { NO_SELECTION, 0.99         } },
                {"NumOfConstituents",      { NO_SELECTION, NO_SELECTION } },
                {"Fraction_Muon",          { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedHadron", { NO_SELECTION, NO_SELECTION } },
                {"ChargedMultiplicity",    { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedEM",     { NO_SELECTION, NO_SELECTION } },
                {"NumOfNeutralParticle",   { NO_SELECTION, NO_SELECTION } }
                } );
    if ( abseta < 3.0 )
        return std::map<std::string,std::pair<float,float>>( {
                {"Fraction_NeutralHadron", { NO_SELECTION, 0.90         } },
                {"Fraction_NeutralEM",     { 0.          , 0.99         } },
                {"NumOfConstituents",      { NO_SELECTION, NO_SELECTION } },
                {"Fraction_Muon",          { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedHadron", { NO_SELECTION, NO_SELECTION } },
                {"ChargedMultiplicity",    { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedEM",     { NO_SELECTION, NO_SELECTION } },
                {"NumOfNeutralParticle",   { 1.          , NO_SELECTION } }
                } );
    if ( abseta < 5.0 )
        return std::map<std::string,std::pair<float,float>>( {
                {"Fraction_NeutralHadron", { 0.2         , NO_SELECTION } },
                {"Fraction_NeutralEM",     { NO_SELECTION, 0.9          } },
                {"NumOfConstituents",      { NO_SELECTION, NO_SELECTION } },
                {"Fraction_Muon",          { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedHadron", { NO_SELECTION, NO_SELECTION } },
                {"ChargedMultiplicity",    { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedEM",     { NO_SELECTION, NO_SELECTION } },
                {"NumOfNeutralParticle",   { 10.         , NO_SELECTION } }
                } );
    EtaIsOutOfRange();
    return std::map<std::string,std::pair<float,float>>();
}
std::map<std::string,std::pair<float,float>> JetIDCuts_ULRun2016_PUPPI( float jetEta )
{
    float abseta = fabs(jetEta);
    if ( abseta < 2.4 )
        return std::map<std::string,std::pair<float,float>>( {
                {"Fraction_NeutralHadron", { NO_SELECTION, 0.90         } },
                {"Fraction_NeutralEM",     { NO_SELECTION, 0.90         } },
                {"NumOfConstituents",      { 1.0         , NO_SELECTION } },
                {"Fraction_Muon",          { NO_SELECTION, 0.80         } },
                {"Fraction_ChargedHadron", { 0.          , NO_SELECTION } },
                {"ChargedMultiplicity",    { 0.          , NO_SELECTION } },
                {"Fraction_ChargedEM",     { NO_SELECTION, 0.80         } },
                {"NumOfNeutralParticle",   { NO_SELECTION, NO_SELECTION } }
                } );
    if ( abseta < 2.7 )
        return std::map<std::string,std::pair<float,float>>( {
                {"Fraction_NeutralHadron", { NO_SELECTION, 0.98         } },
                {"Fraction_NeutralEM",     { NO_SELECTION, 0.99         } },
                {"NumOfConstituents",      { NO_SELECTION, NO_SELECTION } },
                {"Fraction_Muon",          { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedHadron", { NO_SELECTION, NO_SELECTION } },
                {"ChargedMultiplicity",    { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedEM",     { NO_SELECTION, NO_SELECTION } },
                {"NumOfNeutralParticle",   { NO_SELECTION, NO_SELECTION } }
                } );
    if ( abseta < 3.0 )
        return std::map<std::string,std::pair<float,float>>( {
                {"Fraction_NeutralHadron", { NO_SELECTION, NO_SELECTION } },
                {"Fraction_NeutralEM",     { NO_SELECTION, NO_SELECTION } },
                {"NumOfConstituents",      { NO_SELECTION, NO_SELECTION } },
                {"Fraction_Muon",          { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedHadron", { NO_SELECTION, NO_SELECTION } },
                {"ChargedMultiplicity",    { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedEM",     { NO_SELECTION, NO_SELECTION } },
                {"NumOfNeutralParticle",   { 0.          , NO_SELECTION } } // >= 1 at twiki
                } );
    if ( abseta < 5.0 )
        return std::map<std::string,std::pair<float,float>>( {
                {"Fraction_NeutralHadron", { NO_SELECTION, NO_SELECTION } },
                {"Fraction_NeutralEM",     { NO_SELECTION, 0.9          } },
                {"NumOfConstituents",      { NO_SELECTION, NO_SELECTION } },
                {"Fraction_Muon",          { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedHadron", { NO_SELECTION, NO_SELECTION } },
                {"ChargedMultiplicity",    { NO_SELECTION, NO_SELECTION } },
                {"Fraction_ChargedEM",     { NO_SELECTION, NO_SELECTION } },
                {"NumOfNeutralParticle",   { 2.0         , NO_SELECTION } }
                } );
    EtaIsOutOfRange();
    return std::map<std::string,std::pair<float,float>>();
}



bool FailedSelection( const std::pair<float,float>& selrange, float val )
{
    float range_lower = selrange.first;
    float range_upper = selrange.second;
    if ( range_lower != NO_SELECTION )
        if ( val < range_lower ) return true;
    if ( range_upper != NO_SELECTION )
        if ( val > range_upper ) return true;
    return false;
}

bool JetID( TreeReader* dataptr, int iJet, JetIDCutsFPtr cut_definition )
{
    float jeteta = dataptr->GetPtrFloat("jetEta")[iJet];

    std::map<std::string, std::pair<float,float> > jetID_criteria = cut_definition(jeteta);

    if ( FailedSelection(jetID_criteria["Fraction_NeutralHadron"]   , dataptr->GetPtrFloat(""               )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["Fraction_NeutralEM"]       , dataptr->GetPtrFloat(""               )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["NumOfConstituents"]        , dataptr->GetPtrFloat(""               )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["Fraction_Muon"]            , dataptr->GetPtrFloat(""               )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["Fraction_ChargedHadron"]   , dataptr->GetPtrFloat(""               )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["ChargedMultiplicity"]      , dataptr->GetPtrFloat(""               )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["Fraction_ChargedEM"]       , dataptr->GetPtrFloat(""               )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["NumOfNeutralParticle"]     , dataptr->GetPtrFloat(""               )[iJet]) ) return false;
    return true;
}

