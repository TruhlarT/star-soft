/***************************************************************************
 *
 * $Id: StEstTrack.cc,v 1.2 2001/01/25 18:20:38 lmartin Exp $
 *
 * Author: PL,AM,LM,CR (Warsaw,Nantes)
 ***************************************************************************
 *
 * Description: Methods for the StEstTrack class
 *
 ***************************************************************************
 *
 * $Log: StEstTrack.cc,v $
 * Revision 1.2  2001/01/25 18:20:38  lmartin
 * Destructor completed to prevent memory leak.
 * New method RemoveLastBranch added to force the last branch destruction.
 *
 * Revision 1.1  2000/12/07 11:14:27  lmartin
 * First CVS commit
 *
 **************************************************************************/
#include "StEstBranch.hh"
#include "StEstHit.hh"
#include "StEstTrack.hh"
#include "StEstTPCTrack.hh"

StEstTrack::StEstTrack(long maxbranch, StEstTPCTrack *tr=NULL) {
  mMaxBranch = maxbranch;
  mTPCTrack  = tr;
  mNBranch   = 0;
  mBranch    = new StEstBranch*[mMaxBranch];
  mIdealPattern=0;
  mIdealNHits=0;
  mFindablePattern=0;
  mFindableNHits=0;
  mFlag      = 0;
  mDone      = 0;
  mHelix = NULL;
  
  
  if(mBranch==NULL)
    cerr << "ERROR StEstTrack::StEstTrack mBranch==NULL" << endl;
  //  mMaxTPCHits = 40;
};

StEstTrack::~StEstTrack() {
  // StEstTrack destructor. The TPCTrack, Ideal and Findable branches are deleted
  // Then all the branches are deleted with a special method for the 
  // last remaining branch.
    long i,brtot,nhits;

    delete mTPCTrack;
    if (mFindableBranch!=NULL) {
      nhits=mFindableBranch->GetNHits();
      for (i=nhits-1;i>=0;i--)
	mFindableBranch->RemoveHit(i);
      delete mFindableBranch;
    }
    if (mIdealBranch!=NULL) {
      nhits=mIdealBranch->GetNHits();
      for (i=nhits-1;i>=0;i--)
	mIdealBranch->RemoveHit(i);
      delete mIdealBranch;
    }
    brtot=mNBranch;
    for (i=mNBranch-1;i>=0;i--)
      this->RemoveBranch(i);
    this->RemoveLastBranch();
    delete [] mBranch;
    if (mHelix!=NULL) delete mHelix;
};


void StEstTrack::SetHelix(StHelix *hel) {
  if (mHelix!=NULL)
    delete mHelix;
  mHelix=hel;
};

StEstBranch* StEstTrack::GetBranch(long int nbr) {
  if (nbr<0) {
    cerr << "ERROR StEstTrack::GetBranch nbr<0" <<endl;
    cout << "ERROR StEstTrack::GetBranch nbr<0" <<endl;
    return NULL;
  }
  if (mNBranch<nbr) {
    cerr << "ERROR StEstTrack::GetBranch mNBranch<nbr" << endl;
    cout << "ERROR StEstTrack::GetBranch mNBranch<nbr" << endl;
    cout << "mNBranch="<<mNBranch<<" nbr="<<nbr<<" TPC Id = "<<endl;
    return NULL;
  }
  return mBranch[nbr];
};

int StEstTrack::RemoveBranch(long int nbr) {

  // method to remove and kill the branch nbr
  // first the hits are released. then if the track possesses
  // more than one branch, the branch is delete and the branch list modified
  // accordingly if the branch is unique only the hits are released.
  long i,j,nhits;

  if (mNBranch<nbr) {
    cerr << "ERROR  StEstTrack::RemoveBranch nbr>mNBranch" << endl;
    return 1; 
  }
  if(nbr<0) {
    cerr << "ERROR  StEstTrack::RemoveBranch nbr<0" << endl;
    return 1; 
  }
  nhits=mBranch[nbr]->GetNHits();
  for (j=nhits-1;j>=0;j--) {
    mBranch[nbr]->GetHit(j)->LeaveBranch(mBranch[nbr]);
  }
  if (mNBranch>1) {
    delete mBranch[nbr];
    for (i=nbr; i<mNBranch-1;i++) mBranch[i] = mBranch[i+1];
    mBranch[mNBranch-1] = NULL;
    mNBranch--;
  }
  return 0; 
};
int StEstTrack::RemoveLastBranch() {

  // method to remove and kill the last branch 
  // If more than one branch still exist or the last branch is empty
  // a error is returned. This method is only used in the cleaning method
  // CleanUp.
  if (mNBranch!=1) {
    cerr << "ERROR  StEstTrack::RemoveLastBranch more that one branch" << endl;
    return 1; 
  }
  if(!mBranch[0]) {
    cerr << "ERROR  StEstTrack::RemoveLastBranch last branch empty" << endl;
    return 1; 
  }
  delete mBranch[0];
  mNBranch--;
  return 0; 
};
