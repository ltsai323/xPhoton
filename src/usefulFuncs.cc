#include <math.h>
//#include "/home/ltsai/Work/workspaceGammaPlusJet/interface/usefuleFuncs.h"

namespace usefulFuncs
{
   int recordEventSizeWithSeparator( int listSize, int sep ) { return (listSize<<2)+sep; }
   int getEventSizeFromSizeSeparator( int sizeSeparator ) { return sizeSeparator>>2; }
   int getSepFromSizeSeparator( int sizeSeparator ) { return sizeSeparator%4; }
   int inverter ( int sep ) { return sep==2 ? 1:2; }

   bool CheckBoolInt(int intBool, int idx) { return (intBool>>idx)%2; }
   int  SetBoolIntoInt(int idx) { return 1<<idx; }
   void PrintBoolIntStatus(int intBool) { for ( int i=0; i<32; ++i ) printf( "(%d,%s)\n", i, CheckBoolInt(intBool, i) ? "True":"False" ); }
   void StoreBoolInfoToHist( TH1* hist, int intBool ) { for ( int i=0; i<32; ++i ) if ( CheckBoolInt(intBool, i)) hist->Fill(i); }
}
