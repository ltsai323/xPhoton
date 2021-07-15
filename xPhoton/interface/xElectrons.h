#ifndef __xElectrons_h__
#define __xElectrons_h__
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <TTree.h>
#include <TFile.h>


#define PASS_HLTBIT -1
#define BINNING 100
#define MASS_ELECTRON 0.511*0.001
#define MASS_Z 90
#define WINDOW_Z 40
// 0 : veto, 1 : loose, 2: medium, 3: tight. Minus : Disable
#define ELECTRONWORKINGPOINT -1
struct rec_Electron
{
    Float_t
        mcE,
        mcPt,
        mcEta,
        mcPhi,
        recoPt,
        recoEta,
        recoPhi;
    Float_t
        recoPtCalib,
        recoSCEta,
        r9,
        HoverE,
        chIsoRaw,
        phoIsoRaw,
        nhIsoRaw,
        chWorstIso,
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
        sipipFull5x5,
        e2x2Full5x5,
        e2x5Full5x5;
    Float_t
        scEtaWidth_corrected,
        r9Full5x5_corrected,
        s4_corrected,
        sieieFull5x5_corrected;


    Int_t
        firedTrgs,
        isMatched;
    Long64_t
        firedTrgsL;
};
struct rec_Z
{
    Float_t
        mcE,
        mcPt,
        mcEta,
        mcPhi,
        recoMass,
        recoE,
        recoPt,
        recoEta,
        recoPhi;

    Int_t
        isMatched;
};
struct rec_Event
{
    Int_t
        run,
        xsweight,
        puwei,
        pthat,
        nVtx,
        nPU;
    Float_t
        rho,
        MET,
        METPhi,
        genweight;

    Long64_t
        HLT,
        HLTPhoIsPrescaled,
        event;
};
void RegBranch( TTree* t, const std::string& name, rec_Electron* var );
/*
{
    //t->Branch(name, var, "mcE/F:mcPt/F:mcEta/F:mcPhi/F:recoPt/F:recoEta/F:recoPhi/F:recoPtCalib/F:recoSCEta/F:r9/F:HoverE/F:chIsoRaw/F:phoIsoRaw/F:nhIsoRaw/F:chWorstIso/F:rawE/F:scEtaWidth/F:scPhiWidth/F:esRR/F:esEn/F:mva/F:mva_nocorr/F:officalIDmva/F:r9Full5x5/F:sieieFull5x5/F:sipipFull5x5/F:e2x2Full5x5/F:e2x5Full5x5/F:firedTrgs/I:isMatched/I:firedTrgsL/L");

    t->Branch( (name+".mcE").c_str()                ,&var->mcE          , (name+".mcE/F").c_str()              );
    t->Branch( (name+".mcPt").c_str()               ,&var->mcPt         , (name+".mcPt/F").c_str()             );
    t->Branch( (name+".mcEta").c_str()              ,&var->mcEta        , (name+".mcEta/F").c_str()            );
    t->Branch( (name+".mcPhi").c_str()              ,&var->mcPhi        , (name+".mcPhi/F").c_str()            );
    t->Branch( (name+".recoPt").c_str()             ,&var->recoPt       , (name+".recoPt/F").c_str()           );
    t->Branch( (name+".recoEta").c_str()            ,&var->recoEta      , (name+".recoEta/F").c_str()          );
    t->Branch( (name+".recoPhi").c_str()            ,&var->recoPhi      , (name+".recoPhi/F").c_str()          );
    t->Branch( (name+".recoPtCalib").c_str()        ,&var->recoPtCalib  , (name+".recoPtCalib/F").c_str()      );
    t->Branch( (name+".recoSCEta").c_str()          ,&var->recoSCEta    , (name+".recoSCEta/F").c_str()        );
    t->Branch( (name+".r9").c_str()                 ,&var->r9           , (name+".r9/F").c_str()               );
    t->Branch( (name+".HoverE").c_str()             ,&var->HoverE       , (name+".HoverE/F").c_str()           );
    t->Branch( (name+".chIsoRaw").c_str()           ,&var->chIsoRaw     , (name+".chIsoRaw/F").c_str()         );
    t->Branch( (name+".phoIsoRaw").c_str()          ,&var->phoIsoRaw    , (name+".phoIsoRaw/F").c_str()        );
    t->Branch( (name+".nhIsoRaw").c_str()           ,&var->nhIsoRaw     , (name+".nhIsoRaw/F").c_str()         );
    t->Branch( (name+".chWorstIso").c_str()         ,&var->chWorstIso   , (name+".chWorstIso/F").c_str()       );
    t->Branch( (name+".rawE").c_str()               ,&var->rawE         , (name+".rawE/F").c_str()             );
    t->Branch( (name+".scEtaWidth").c_str()         ,&var->scEtaWidth   , (name+".scEtaWidth/F").c_str()       );
    t->Branch( (name+".scPhiWidth").c_str()         ,&var->scPhiWidth   , (name+".scPhiWidth/F").c_str()       );
    t->Branch( (name+".esRR").c_str()               ,&var->esRR         , (name+".esRR/F").c_str()             );
    t->Branch( (name+".esEn").c_str()               ,&var->esEn         , (name+".esEn/F").c_str()             );
    t->Branch( (name+".mva").c_str()                ,&var->mva          , (name+".mva/F").c_str()              );
    t->Branch( (name+".mva_nocorr").c_str()         ,&var->mva_nocorr   , (name+".mva_nocorr/F").c_str()       );
    t->Branch( (name+".officalIDmva").c_str()       ,&var->officalIDmva , (name+".officalIDmva/F").c_str()     );
    t->Branch( (name+".r9Full5x5").c_str()          ,&var->r9Full5x5    , (name+".r9Full5x5/F").c_str()        );
    t->Branch( (name+".sieieFull5x5").c_str()       ,&var->sieieFull5x5 , (name+".sieieFull5x5/F").c_str()     );
    t->Branch( (name+".sipipFull5x5").c_str()       ,&var->sipipFull5x5 , (name+".sipipFull5x5/F").c_str()     );
    t->Branch( (name+".e2x2Full5x5").c_str()        ,&var->e2x2Full5x5  , (name+".e2x2Full5x5/F").c_str()      );
    t->Branch( (name+".e2x5Full5x5").c_str()        ,&var->e2x5Full5x5  , (name+".e2x5Full5x5/F").c_str()      );


    t->Branch( (name+".firedTrgs").c_str()          ,&var->firedTrgs    , (name+".firedTrgs/I").c_str()        );
    t->Branch( (name+".isMatched").c_str()          ,&var->isMatched    , (name+".isMatched/I").c_str()        );

    t->Branch( (name+".firedTrgsL").c_str()         ,&var->firedTrgsL   , (name+".firedTrgsL/L").c_str()       );
}
*/
void RegBranch( TTree* t, const std::string& name, rec_Z* var );
/*
{
    t->Branch( (name+".mcE").c_str()            ,&var->mcE       , (name+".mcE/F").c_str()        );
    t->Branch( (name+".mcPt").c_str()           ,&var->mcPt      , (name+".mcPt/F").c_str()       );
    t->Branch( (name+".mcEta").c_str()          ,&var->mcEta     , (name+".mcEta/F").c_str()      );
    t->Branch( (name+".mcPhi").c_str()          ,&var->mcPhi     , (name+".mcPhi/F").c_str()      );
    t->Branch( (name+".recoMass").c_str()       ,&var->recoMass  , (name+".recoMass/F").c_str()   );
    t->Branch( (name+".recoE").c_str()          ,&var->recoE     , (name+".recoE/F").c_str()      );
    t->Branch( (name+".recoPt").c_str()         ,&var->recoPt    , (name+".recoPt/F").c_str()     );
    t->Branch( (name+".recoEta").c_str()        ,&var->recoEta   , (name+".recoEta/F").c_str()    );
    t->Branch( (name+".recoPhi").c_str()        ,&var->recoPhi   , (name+".recoPhi/F").c_str()    );

    t->Branch( (name+".isMatched").c_str()      ,&var->isMatched , (name+".isMatched/I").c_str()  );
}
*/
void RegBranch( TTree* t, const std::string& name, rec_Event* var );
/*
{
    t->Branch(name, var, "run/I:xsweight/I:puwei/I:pthat/I:MET/I:METPhi/I:nVtx/I:rho/F:nPU/I:HLT/L:HLTPhoIsPrescaled/L:event/L");
}
*/

#include <string.h>
template<typename T>
void ClearStruct(T* obj) { memset( obj, 0x00, sizeof(T) ); }


void xElectrons(
        std::vector<std::string> pathes,
        char oname[200]);

void xElectrons(std::string ipath, int outID);
#endif
