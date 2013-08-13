#ifndef StiTrackFinder_H
#define StiTrackFinder_H 1
#include <assert.h>
#include <vector>
class StiHit;
class StiTrack;
template<class Filtered>class Filter;


/// An abstract class defining  the interface to the track finder.
class StiTrackFinder 
{
public:
   StiTrackFinder(){mComb=7;}
  /// Initialize the finder
  virtual void initialize()				{;}
  /// Find all tracks of the currently loaded event
  virtual void findTracks()				{assert(0);}; 
  /// Find/extend the given track, in the given direction
  virtual bool find(StiTrack *track, int direction, double rmin=0) {assert(0);return 0;}
  /// Find the next track 
  virtual StiTrack * findTrack(double rMin=0)=0;
  /// Extent all tracks to the given vertex
  virtual void extendTracksToVertex(StiHit* vertex)	{assert(0);}
  virtual void extendTracksToVertices(const std::vector<StiHit*> &vertices){assert(0);}
  /// Reset the tracker
  virtual void reset(){;}
  virtual void unset(){;}
  /// Reset the tracker
  virtual void clear(){;}
  /// Get the track filter currently used by the tracker
  virtual Filter<StiTrack> * getTrackFilter()		{assert(0);return 0;};
  /// Set the vertex finder used by this tracker
  void setComb(int comb=7)				{mComb = comb;}
  int  useComb() const					{return mComb;}
  

protected:
  int mComb; //=silicon+4*tpc
             // silicon/tpc 0=no combinatoric , no tree search
             //             1=combinatoric , only hits count
             //             2=combinatoric , no hits also counts

};

#endif
