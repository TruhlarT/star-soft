// Hey Emacs this is -*-c++-*-
// $Id: EEmcTTMatch.h,v 1.2 2004/05/05 21:37:38 zolnie Exp $
#ifndef STAR_EEmcTTMatch
#define STAR_EEmcTTMatch


#include <ostream>


#include "TObject.h"
#include "TVector3.h"


#if !defined(ST_NO_NAMESPACES)
using std::ostream;
#endif

class StMuTrack;
class EEmcTower;


class EEmcTTMatch : public TObject {
public:
  /// the constructor
  EEmcTTMatch();
  /// the destructor
  virtual ~EEmcTTMatch(); 

  /// clears list of matches
  void    Clear(Option_t *opt);
  /// adds tower data
  void    Add(EEmcTower *t);
  /// adds a track to list of matches
  void    Add(StMuTrack *t);
  /// returns a tower data
  EEmcTower *Tower()   { return mTower;   }
  /// returns a list of matched tracks
  TList     *Tracks()  { return mTracks;  }
  /// returns number of matched tracks
  Int_t      Matches() { return mNTracks; }


  /// prints itself to a ostream
  /// \param out ostream reference
  ostream& Out(ostream &out ) const; 

  /// extrapolate given track to depth z 
  /// \param track a pointer to StMuTrack
  /// \param z     depth to extrapolate to
  /// \param r     resulting 3-d vector 
  static  Bool_t  ExtrapolateToZ    ( const StMuTrack *track , const double  z, TVector3 &r); 

private:
  /// tower data
  EEmcTower *mTower;   //->
  /// list of matched tracks
  TList     *mTracks;  //->
  /// number of matched tracks (do not trust root)
  Int_t      mNTracks; //! 

public:

  ClassDef(EEmcTTMatch, 1)   // 

};

ostream&  operator<<(ostream &out, const StMuTrack    &t  );  
ostream&  operator<<(ostream &out, const EEmcTTMatch  &m  );

#endif
