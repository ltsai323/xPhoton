#ifndef __READMGR_H__
#define __READMGR_H__
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include <map>
#include <vector>

class readMgr : public TreeReader
{
public:
    /*
    explicit readMgr( const std::vector<std::string>& pathes, const std::vector<const char*>& sourcebranches) : TreeReader(pathes), bnames(sourcebranches)
    {}
    explicit readMgr( const char* filepath, const char* treename, const std::vector<const char*>& sourcebranches) : TreeReader(filepath, treename), bnames(sourcebranches)
    {}

    virtual ~readMgr() {}
    */
    explicit readMgr(
            const std::vector<std::string>& pathes,
            const std::vector<const char*>& sourcebranches);
    explicit readMgr(
            const char* filepath,
            const char* treename,
            const std::vector<const char*>& sourcebranches);
    virtual ~readMgr();


    // new conecttion method by enum.
    Char_t*   PtrChar   (int varId);
    Short_t*  PtrShort  (int varId);
    Int_t*    PtrInt    (int varId);
    Long64_t* PtrLong64 (int varId);
    Float_t*  PtrFloat  (int varId);
    Double_t* PtrDouble (int varId);
    char*     PtrString (int varId);
    TObject*  PtrTObject(int varId);

    // NOTE: this works only for TLeafO (and not for vector<bool>) branches
    Bool_t*   PtrBool   (int varId);

    // return branch values for elementary types
    Bool_t   Bool  (int varId);
    Char_t   Char  (int varId);
    Short_t  Short (int varId);
    Int_t    Int   (int varId);
    Long64_t Long64(int varId);
    Float_t  Float (int varId);
    Double_t Double(int varId);
private:
    //std::map<int, const char*> bnames;
    std::vector<const char*> bnames;
};


#endif
