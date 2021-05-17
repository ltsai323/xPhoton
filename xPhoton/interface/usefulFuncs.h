#ifndef __usefulFuncs_h__
#define __usefulFuncs_h__
#include <vector>
#include <utility> // std::pair
#include <stdio.h>
#include "TH1.h"

namespace usefulFuncs
{
   int recordEventSizeWithSeparator( int listSize, int sep );
   int getEventSizeFromSizeSeparator( int sizeSeparator );
   int getSepFromSizeSeparator( int sizeSeparator );
   int inverter ( int sep );

   bool CheckBoolInt(int intBool, int idx);
   int  SetBoolIntoInt(int idx);
   void PrintBoolIntStatus(int intBool);
   void StoreBoolInfoToHist( TH1* hist, int intBool );

   bool isBarrel( float val );
   bool isEndCap( float val );
};
#endif
