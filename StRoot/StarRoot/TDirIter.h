#ifndef ROOT_TDirIter
#define ROOT_TDirIter


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TDirIter                                                             //
//                                                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
#include "TString.h"
#include "TRegexp.h"

class TDirIter
{
public:
   TDirIter(const char *path, Int_t maxlev = 99);
  ~TDirIter(){;}
void 	Reset  (const char *path, Int_t maxlev = 99);
const char *NextFile();

private:
TString 	MakeWild(const char *re);
const char 	*NextFileQQ();
void 		ResetQQ(const char *path);

//              Data members
   Int_t fMaxLev; 
   Int_t fMaxLevQQ; 
   Int_t fLevel; 
   Int_t fState; 
   Int_t fSele; 
   Int_t fSkip; 
   TString fFull;
   TString fFile;
   TRegexp fRegx;
   void   *fEntrStk[100];
   Int_t   fLengStk[100];
   
//   ClassDef(TDirIter,1)

};
#endif //ROOT_TDirIter
