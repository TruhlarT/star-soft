// $Id: EEmcEventHeader.cxx,v 1.2 2003/05/26 14:44:34 zolnie Exp $ 
// $Log: EEmcEventHeader.cxx,v $
// Revision 1.2  2003/05/26 14:44:34  zolnie
// rewritten implementation of EEmcL3Tracks using TClonesArray
// introduced a common Makefile and mklinkdef.pl
//
// Revision 1.1  2003/05/20 19:22:58  zolnie
// new additions for ..... :)
//

#include "EEmcEventHeader.h"
 
#include <iostream.h>

ClassImp(EEmcEventHeader)

  


//--------------------------------------------------
//
//--------------------------------------------------
EEmcEventHeader ::  EEmcEventHeader() {
  mComment=NULL;
  
  clear();
}

//--------------------------------------------------
//
//--------------------------------------------------
EEmcEventHeader ::  ~EEmcEventHeader() { }

//--------------------------------------------------
void EEmcEventHeader :: setComment(const char* s) {
  mCommentLen = (strlen(s)/8+1)*8; //make it 8 byte aligned
  //mCommentLen = (mCommentLen<MaxCommentLen) ? mCommentLen : MaxCommentLen;
  if(mComment) delete [] mComment;
  mComment = new char[mCommentLen];
  strncpy(mComment,s,mCommentLen);
}


//--------------------------------------------------
//
//--------------------------------------------------
void EEmcEventHeader :: clear() {
  mTimeStamp  = -1;
  mProcessingTime  = -1;
  mCommentLen = 0;
  if(mComment) delete [] mComment;
}



//--------------------------------------------------
//
//--------------------------------------------------
void EEmcEventHeader :: print(FILE *fd) const{
  fprintf(fd,"EEmcEventHeader:\n");
  fprintf(fd,"\tevent number : %-6d (0x%06x)\n",mEventNumber,mEventNumber);
  fprintf(fd,"\ttoken        : %-6d (0x%03x)\n",mToken      ,mToken);
  fprintf(fd,"\ttime stamp   : %ld / %s",mTimeStamp,
		  	ctime((const time_t *)&mTimeStamp));
  fprintf(fd,"\tproc. time   : %ld / %s",mProcessingTime,
		  	ctime((const time_t *)&mProcessingTime));
  
  fprintf(fd,"\tcomment      : %s\n"    ,mComment);
}



