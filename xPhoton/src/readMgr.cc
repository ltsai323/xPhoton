#include "xPhoton/xPhoton/interface/readMgr.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include <map>
#include <vector>


readMgr::readMgr(
        const std::vector<std::string>& pathes,
        const std::vector<const char*>& sourcebranches
    ) :
    TreeReader(pathes),
    bnames(sourcebranches)
{}
readMgr::readMgr(
        const char* filepath,
        const char* treename,
        const std::vector<const char*>& sourcebranches
    ) :
    TreeReader(filepath, treename),
    bnames(sourcebranches)
{}

readMgr::~readMgr() {}

Char_t*   readMgr::PtrChar   (int varId) { return (Char_t*)    GetPtr(bnames[varId], kArrChar);   }
Short_t*  readMgr::PtrShort  (int varId) { return (Short_t*)   GetPtr(bnames[varId], kArrShort);  }
Int_t*    readMgr::PtrInt    (int varId) { return (Int_t*)     GetPtr(bnames[varId], kArrInt);    }
Long64_t* readMgr::PtrLong64 (int varId) { return (Long64_t*)  GetPtr(bnames[varId], kArrLong64); }
Float_t*  readMgr::PtrFloat  (int varId) { return (Float_t*)   GetPtr(bnames[varId], kArrFloat);  }
Double_t* readMgr::PtrDouble (int varId) { return (Double_t*)  GetPtr(bnames[varId], kArrDouble); }
char*     readMgr::PtrString (int varId) { return (char*)      GetPtr(bnames[varId], kString);    }
TObject*  readMgr::PtrTObject(int varId) { return (TObject*)   GetPtr(bnames[varId], kTObject);   }

    // NOTE: this works only for TLeafO (and not for vector<bool>) branches
Bool_t*   readMgr::PtrBool   (int varId) { return (Bool_t*) GetPtr(bnames[varId], kArrBool); }

    // return branch values for elementary types
Bool_t    readMgr::Bool  (int varId) { return ((Bool_t*)   GetPtr(bnames[varId], kBool))  [0]; }
Char_t    readMgr::Char  (int varId) { return ((Char_t*)   GetPtr(bnames[varId], kChar))  [0]; }
Short_t   readMgr::Short (int varId) { return ((Short_t*)  GetPtr(bnames[varId], kShort)) [0]; }
Int_t     readMgr::Int   (int varId) { return ((Int_t*)    GetPtr(bnames[varId], kInt))   [0]; }
Long64_t  readMgr::Long64(int varId) { return ((Long64_t*) GetPtr(bnames[varId], kLong64))[0]; }
Float_t   readMgr::Float (int varId) { return ((Float_t*)  GetPtr(bnames[varId], kFloat)) [0]; }
Double_t  readMgr::Double(int varId) { return ((Double_t*) GetPtr(bnames[varId], kDouble))[0]; }
