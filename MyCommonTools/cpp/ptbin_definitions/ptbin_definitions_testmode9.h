#include "ptbin_definitions_testmode_base.h"
//#include "/wk_cms3/ltsai/wk_cms/ltsai/github/xPhoton/MyCommonTools/cpp/ptbin_definitions/ptbin_definitions_testmode_base.h"

static int test_mode_ = 9;
Int_t TriggerBit( const std::string& dataera, Int_t ptbin)
{ return TriggerBitBase(dataera, ptbin, test_mode_); }

std::vector<float> ptbin_ranges()
{ return ptbin_ranges_base(test_mode_); }
