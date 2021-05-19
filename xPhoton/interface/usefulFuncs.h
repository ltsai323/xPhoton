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
   double deltaPhi(
       double phi1,
       double phi2);
   double deltaR(
       double eta1,
       double phi1,
       double eta2,
       double phi2);
};
#endif
