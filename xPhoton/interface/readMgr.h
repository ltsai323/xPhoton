#ifndef __READMGR_H__
#define __READMGR_H__
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include <map>
#include <vector>

class readMgr : public TreeReader
{
public:
    // explicit readMgr( const std::vector<std::string>& pathes, std::map<int,const char*> nameMap) : TreeReader(pathes)
    explicit readMgr( const std::vector<std::string>& pathes, const std::vector<const char*>& sourcebranches) : TreeReader(pathes), bnames(sourcebranches)
    {}
    explicit readMgr( const char* filepath, const char* treename, const std::vector<const char*>& sourcebranches) : TreeReader(filepath, treename), bnames(sourcebranches)
    {}

    virtual ~readMgr() {}


    // new conecttion method by enum.
    Char_t*   PtrChar   (int varId) { return (Char_t*)    GetPtr(bnames[varId], kArrChar);   }
    Short_t*  PtrShort  (int varId) { return (Short_t*)   GetPtr(bnames[varId], kArrShort);  }
    Int_t*    PtrInt    (int varId) { return (Int_t*)     GetPtr(bnames[varId], kArrInt);    }
    Long64_t* PtrLong64 (int varId) { return (Long64_t*)  GetPtr(bnames[varId], kArrLong64); }
    Float_t*  PtrFloat  (int varId) { return (Float_t*)   GetPtr(bnames[varId], kArrFloat);  }
    Double_t* PtrDouble (int varId) { return (Double_t*)  GetPtr(bnames[varId], kArrDouble); }
    char*     PtrString (int varId) { return (char*)      GetPtr(bnames[varId], kString);    }
    TObject*  PtrTObject(int varId) { return (TObject*)   GetPtr(bnames[varId], kTObject);   }

    // NOTE: this works only for TLeafO (and not for vector<bool>) branches
    Bool_t*   PtrBool   (int varId) { return (Bool_t*) GetPtr(bnames[varId], kArrBool); }

    // return branch values for elementary types
    Bool_t   Bool  (int varId) { return ((Bool_t*)   GetPtr(bnames[varId], kBool))  [0]; }
    Char_t   Char  (int varId) { return ((Char_t*)   GetPtr(bnames[varId], kChar))  [0]; }
    Short_t  Short (int varId) { return ((Short_t*)  GetPtr(bnames[varId], kShort)) [0]; }
    Int_t    Int   (int varId) { return ((Int_t*)    GetPtr(bnames[varId], kInt))   [0]; }
    Long64_t Long64(int varId) { return ((Long64_t*) GetPtr(bnames[varId], kLong64))[0]; }
    Float_t  Float (int varId) { return ((Float_t*)  GetPtr(bnames[varId], kFloat)) [0]; }
    Double_t Double(int varId) { return ((Double_t*) GetPtr(bnames[varId], kDouble))[0]; }
private:
    //std::map<int, const char*> bnames;
    std::vector<const char*> bnames;
};


#endif
