/******************************************************
 *
 * $Id: StPmdHit.cxx,v 1.1 2002/08/27 12:18:55 subhasis Exp $
 * Author: Subhasis Chattopadhyay, Dec 2001
 *
 ******************************************************
 *
 *Description: This is the class for Pmd hit objects
 *
 ******************************************************
 * $Log: StPmdHit.cxx,v $
 * Revision 1.1  2002/08/27 12:18:55  subhasis
 * First version
 *
 *
 ******************************************************/
#include "StPmdHit.h"

ClassImp(StPmdHit)

//__________________________________________________________
StPmdHit::StPmdHit(TArrayI *hits) : StObject() 
{
}
//__________________________________________________________
StPmdHit::StPmdHit() : StObject() 
{
  mGsuper = 0;  mSubdet = 0; 
  mRow =0;  mCol=0;
  
}

void
StPmdHit::print(ostream *os)
{
  //! Printing member function.
  *os << "Gsuper " << Gsuper();
  *os << " SubDetector " << SubDetector();
  *os << " Row " << Row();
  *os << " Column " << Column();
  *os << " Edep " << Edep();
}

ostream &operator<<(ostream &os, StPmdHit &cl)
{
  cl.print(&os); return os;
}

void 
StPmdHit::Browse(TBrowser *b)
{
  cout << (*this) << endl;
  StObject::Browse(b);
}



