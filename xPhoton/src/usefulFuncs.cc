#include <math.h>
#include <stdio.h>
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include <cmath>

int usefulFuncs::recordEventSizeWithSeparator( int listSize, int sep )
{ return (listSize<<2)+sep; }
int usefulFuncs::getEventSizeFromSizeSeparator( int sizeSeparator )
{ return sizeSeparator>>2; }
int usefulFuncs::getSepFromSizeSeparator( int sizeSeparator )
{ return sizeSeparator%4; }
int usefulFuncs::inverter ( int sep )
{ return sep==2 ? 1:2; }

bool usefulFuncs::CheckBoolInt(int intBool, int idx)
{ return (intBool>>idx)%2; }
int  usefulFuncs::SetBoolIntoInt(int idx)
{ return 1<<idx; }
void usefulFuncs::PrintBoolIntStatus(int intBool)
{ for ( int i=0; i<32; ++i ) printf( "(%d,%s)\n", i, CheckBoolInt(intBool, i) ? "True":"False" ); }
void usefulFuncs::StoreBoolInfoToHist( TH1* hist, int intBool )
{ for ( int i=0; i<32; ++i ) if ( CheckBoolInt(intBool, i)) hist->Fill(i); }

bool usefulFuncs::isBarrel( float val )
{ return fabs(val) < 1.4442; }
bool usefulFuncs::isEndCap( float val )
{ return fabs(val) > 1.566 && fabs(val) < 2.5; }

double usefulFuncs::deltaPhi(double phi1, double phi2) {
  double dPhi = phi1 - phi2;
  if (dPhi >  M_PI) dPhi -= 2.*M_PI;
  if (dPhi < -M_PI) dPhi += 2.*M_PI;
  return dPhi;
}

double usefulFuncs::deltaR(double eta1, double phi1, double eta2, double phi2) {
  double dEta, dPhi ;
  dEta = eta1 - eta2;
  dPhi = deltaPhi(phi1, phi2);
  return sqrt(dEta*dEta+dPhi*dPhi);
}
