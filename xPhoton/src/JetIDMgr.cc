#include "xPhoton/xPhoton/interface/JetIDMgr.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include <exception>

void JetIDMgr::etaisoutofrange()
{ throw std::out_of_range( "JetIDCuts() : Input jet Eta is out of range()\n"); }

bool JetIDMgr::FailedSelection( const std::pair<float,float>& selrange, float val )
{
    float range_lower = selrange.first;
    float range_upper = selrange.second;
    if ( range_lower != NO_SELECTION )
        if ( val < range_lower ) return true;
    if ( range_upper != NO_SELECTION )
        if ( val > range_upper ) return true;
    return false;
}

bool JetIDMgr::IDPassed( TreeReader* dataptr, int iJet, JetIDCutsFPtr cut_definition )
{
    float jeteta = dataptr->GetPtrFloat("jetEta")[iJet];

    std::map<std::string, std::pair<float,float> > jetID_criteria = cut_definition(jeteta);

    if ( FailedSelection(jetID_criteria["Fraction_NeutralHadron"]   , dataptr->GetPtrFloat("jetNHF"         )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["Fraction_NeutralEM"]       , dataptr->GetPtrFloat("jetNEF"         )[iJet]) ) return false;
    //if ( FailedSelection(jetID_criteria["NumOfConstituents"]        , dataptr->GetPtrInt  ("jetNConstituents")[iJet]) ) return false; // is it iJet->numberOfDaughters() ?
    if ( FailedSelection(jetID_criteria["Fraction_Muon"]            , dataptr->GetPtrFloat("jetMUF"         )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["Fraction_ChargedHadron"]   , dataptr->GetPtrFloat("jetCHF"         )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["ChargedMultiplicity"]      , dataptr->GetPtrInt  ("jetNCH"         )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["Fraction_ChargedEM"]       , dataptr->GetPtrFloat("jetCEF"         )[iJet]) ) return false;
    if ( FailedSelection(jetID_criteria["NumOfNeutralParticle"]     , dataptr->GetPtrInt  ("jetNNP"         )[iJet]) ) return false; // is it iJet->neutralMultiplicity() ?
    return true;
}
bool JetIDMgr::PUIDPassed( TreeReader* dataptr, int iJet, PUJetIDCutsFPtr cut_definition )
{
    float jetpt  = dataptr->GetPtrFloat("jetPt" )[iJet];
    float jeteta = dataptr->GetPtrFloat("jetEta")[iJet];
    float puid = dataptr->GetPtrFloat("jetPUID")[iJet];

    float jetPUID_criteria = cut_definition(jetpt, jeteta);

    if ( jetpt > 10 )
        LOG_DEBUG("jetID = %.2f, the criteria = %.2f, which is passed ? %d", puid, jetPUID_criteria, (puid>jetPUID_criteria) );
    if ( dataptr->GetPtrFloat("jetPUID")[iJet] > jetPUID_criteria ) return true;
    return false;
}





std::map<std::string,std::pair<float,float>> JetIDMgr::JetIDCuts_ULRun2016_CHS( float jetEta )
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
    etaisoutofrange();
    return std::map<std::string,std::pair<float,float>>();
}
std::map<std::string,std::pair<float,float>> JetIDMgr::JetIDCuts_ULRun2016_PUPPI( float jetEta )
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
    etaisoutofrange();
    return std::map<std::string,std::pair<float,float>>();
}
float JetIDMgr::PUJetIDCuts_ULRun2016_CHS_Tight (  float jetPt, float jetEta )
{ return JetIDMgr::PUJetIDCuts_ULRun2017_CHS_Tight (jetPt,jetEta); }
float JetIDMgr::PUJetIDCuts_ULRun2016_CHS_Medium(  float jetPt, float jetEta )
{ return JetIDMgr::PUJetIDCuts_ULRun2017_CHS_Medium(jetPt,jetEta); }
float JetIDMgr::PUJetIDCuts_ULRun2016_CHS_Loose (  float jetPt, float jetEta ) 
{ return JetIDMgr::PUJetIDCuts_ULRun2017_CHS_Loose (jetPt,jetEta); }


float JetIDMgr::PUJetIDCuts_ULRun2017_CHS_Tight (  float jetPt, float jetEta ) 
{
    float abseta = fabs(jetEta);
    if ( jetPt < 10 ) return FAILED_PUID;
    if ( abseta < 2.5 )
    {
             if ( jetPt < 20 ) return  0.77;
        else if ( jetPt < 30 ) return  0.90;
        else if ( jetPt < 40 ) return  0.96;
        else if ( jetPt < 50 ) return  0.98;
        return PASSED_PUID;
    }
    else if ( abseta < 2.75 )
    {
             if ( jetPt < 20 ) return  0.38;
        else if ( jetPt < 30 ) return  0.60;
        else if ( jetPt < 40 ) return  0.82;
        else if ( jetPt < 50 ) return  0.92;
        return PASSED_PUID;
    }
    else if ( abseta < 3.0 )
    {
             if ( jetPt < 20 ) return -0.31;
        else if ( jetPt < 30 ) return -0.12;
        else if ( jetPt < 40 ) return  0.20;
        else if ( jetPt < 50 ) return  0.47;
        return PASSED_PUID;
    }
    else if ( abseta < 5.0 )
    {
             if ( jetPt < 20 ) return -0.21;
        else if ( jetPt < 30 ) return -0.13;
        else if ( jetPt < 40 ) return  0.09;
        else if ( jetPt < 50 ) return  0.29;
        return PASSED_PUID;
    }
    return PASSED_PUID;
}
float JetIDMgr::PUJetIDCuts_ULRun2017_CHS_Medium(  float jetPt, float jetEta ) 
{
    float abseta = fabs(jetEta);
    if ( jetPt < 10 ) return FAILED_PUID;
    if ( abseta < 2.5 )
    {
             if ( jetPt < 20 ) return  0.26;
        else if ( jetPt < 30 ) return  0.68;
        else if ( jetPt < 40 ) return  0.90;
        else if ( jetPt < 50 ) return  0.96;
        return PASSED_PUID;
    }
    else if ( abseta < 2.75 )
    {
             if ( jetPt < 20 ) return -0.33;
        else if ( jetPt < 30 ) return -0.04;
        else if ( jetPt < 40 ) return  0.36;
        else if ( jetPt < 50 ) return  0.61;
        return PASSED_PUID;
    }
    else if ( abseta < 3.0 )
    {
             if ( jetPt < 20 ) return -0.54;
        else if ( jetPt < 30 ) return -0.43;
        else if ( jetPt < 40 ) return -0.16;
        else if ( jetPt < 50 ) return  0.14;
        return PASSED_PUID;
    }
    else if ( abseta < 5.0 )
    {
             if ( jetPt < 20 ) return -0.37;
        else if ( jetPt < 30 ) return -0.30;
        else if ( jetPt < 40 ) return -0.09;
        else if ( jetPt < 50 ) return  0.12;
        return PASSED_PUID;
    }
    return PASSED_PUID;
}
float JetIDMgr::PUJetIDCuts_ULRun2017_CHS_Loose (  float jetPt, float jetEta ) 
{
    float abseta = fabs(jetEta);
    if ( jetPt < 10 ) return FAILED_PUID;
    if ( abseta < 2.5 )
    {
             if ( jetPt < 20 ) return -0.95;
        else if ( jetPt < 30 ) return -0.88;
        else if ( jetPt < 40 ) return -0.63;
        else if ( jetPt < 50 ) return -0.19;
        return PASSED_PUID;
    }
    else if ( abseta < 2.75 )
    {
             if ( jetPt < 20 ) return -0.72;
        else if ( jetPt < 30 ) return -0.55;
        else if ( jetPt < 40 ) return -0.18;
        else if ( jetPt < 50 ) return  0.22;
        return PASSED_PUID;
    }
    else if ( abseta < 3.0 )
    {
             if ( jetPt < 20 ) return -0.68;
        else if ( jetPt < 30 ) return -0.60;
        else if ( jetPt < 40 ) return -0.43;
        else if ( jetPt < 50 ) return -0.13;
        return PASSED_PUID;
    }
    else if ( abseta < 5.0 )
    {
             if ( jetPt < 20 ) return -0.47;
        else if ( jetPt < 30 ) return -0.43;
        else if ( jetPt < 40 ) return -0.24;
        else if ( jetPt < 50 ) return -0.03;
        return PASSED_PUID;
    }
    return PASSED_PUID;
}


float JetIDMgr::PUJetIDCuts_ULRun2018_CHS_Tight (  float jetPt, float jetEta ) 
{ return JetIDMgr::PUJetIDCuts_ULRun2017_CHS_Tight (jetPt,jetEta); }
float JetIDMgr::PUJetIDCuts_ULRun2018_CHS_Medium(  float jetPt, float jetEta ) 
{ return JetIDMgr::PUJetIDCuts_ULRun2017_CHS_Medium(jetPt,jetEta); }
float JetIDMgr::PUJetIDCuts_ULRun2018_CHS_Loose (  float jetPt, float jetEta ) 
{ return JetIDMgr::PUJetIDCuts_ULRun2017_CHS_Loose (jetPt,jetEta); }
