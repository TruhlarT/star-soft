//StiKalmanTrack.cxx
/*
 * $Id: StiKalmanTrack.cxx,v 2.48 2004/12/11 04:31:36 perev Exp $
 * $Id: StiKalmanTrack.cxx,v 2.48 2004/12/11 04:31:36 perev Exp $
 *
 * /author Claude Pruneau
 *
 * $Log: StiKalmanTrack.cxx,v $
 * Revision 2.48  2004/12/11 04:31:36  perev
 * set of bus fixed
 *
 * Revision 2.47  2004/12/01 18:04:32  perev
 * test for -ve and too big track length added
 *
 * Revision 2.46  2004/12/01 03:57:08  pruneau
 * d<4
 *
 * Revision 2.45  2004/11/12 22:48:28  fisyak
 * Back to use chi2 instead DCA for Vertex fit
 *
 * Revision 2.44  2004/11/11 03:19:05  pruneau
 * implementation of extrapolation functions for Jan
 *
 * Revision 2.43  2004/11/10 21:44:26  pruneau
 * adding functions for extrapolation
 *
 * Revision 2.42  2004/11/08 15:32:50  pruneau
 * 3 sets of modifications
 * (1) Changed the StiPlacement class to hold keys to both the radial and angle placement. Propagated the use
 * of those keys in StiSvt StiTpc StiSsd and all relevant Sti classes.
 * (2) Changed the StiKalmanTrackFinder::find(StiTrack*) function's algorithm for the navigation of the
 * detector volumes. The new code uses an iterator to visit all relevant volumes. The code is now more robust and compact
 * as well as much easier to read and maintain.
 * (3) Changed the chi2 calculation in StiKalmanTrack::getChi2 and propagated the effects of this change
 * in both StiTrackingPlots and StiStEventFiller classes.
 *
 * Revision 2.41  2004/10/28 19:30:42  perev
 * Hack. Infinite Chi2 skipped in Chi2 calculation. Claude??? (VP)
 *
 * Revision 2.40  2004/10/28 04:59:18  perev
 * Fixed iterator for nodes. v3V2
 *
 * Revision 2.39  2004/10/27 03:25:49  perev
 * Version V3V
 *
 * Revision 2.38  2004/10/26 21:52:07  pruneau
 * No truncation but bad hits dropped
 *
 * Revision 2.37  2004/10/26 06:45:37  perev
 * version V2V
 *
 * Revision 2.36  2004/10/25 14:15:49  pruneau
 * various changes to improve track quality.
 *
 * Revision 2.35  2004/08/17 20:55:42  perev
 * memory cleanup heap==>stack
 *
 * Revision 2.34  2004/08/06 02:28:53  andrewar
 * Added getMaxPointCount(int detectorId)< where detectorId corresponds to the
 * StDetectorId value.
 *
 * Revision 2.33  2004/04/04 23:19:28  jeromel
 * isfinite() -> finite()
 *
 * Revision 2.32  2004/03/31 00:23:41  calderon
 * -Fixed memory leak in StiDetectorTreeBuilder::hangWhere (100 chars were lost
 *  every time this function was called)
 * -Changed algorithm to count fit points in StiKalmanTrack.  Now it is based
 *  on counting the nodes that have a chi2 < chi2Max from
 *  StiKalmanTrackFitterParameters.
 * -Which meant that I had to somehow introduce a pointer to it so that the
 *  track could know about the chi2Max used in the fitter.
 * -And I also added a method to retrieve the pointer to the fitterParams
 *  to be used in StiStEventFiller.
 * -Which was then modified to calculate the encoded fit points based on
 *  a similar algorithm (chi2<chi2Max test).
 * -Cleaned up the includes in StiKalmanTrack.h, left only the ones
 *  needed to keep the code compiling.
 * -Which required a slight modification in the include of StiKalmanTrackFinder
 * -StiTrackKalmanTrackFitter now also sets a pointer to itself in
 *  static StiKalmanTrack::setFitParameters()
 * -Removed some print outs from VectorizedFactory to reduce the size of the log
 *  files.
 *
 * Revision 2.31  2004/03/23 23:10:37  calderon
 * Check for nan's in getTrackLength() calculation.  When the argument for the
 * asin() is >1, the code instead calculates a length iteratively.
 * For these cases, the returned value is negative so that they can be inspected
 * in the gui, or filtered in the StiStEventFiller.
 *
 * Revision 2.30  2004/02/21 18:27:34  pruneau
 * Updates to comply with changes made in abstract interfaces.
 *
 * Revision 2.29  2003/09/02 17:59:41  perev
 * gcc 3.2 updates + WarnOff
 *
 * Revision 2.28  2003/08/02 08:22:43  pruneau
 * best performance so far
 *
 * Revision 2.27  2003/07/30 19:18:25  pruneau
 * sigh
 *
 * Revision 2.25  2003/05/14 21:37:59  pruneau
 * Fixed "chi2" problem. 5 first nodes on a track did not have
 * relevant errors. Fix the problem by inserting a call to calculateError()
 * inside the add(stiHit*...) method used while initializing tracks from the
 * seed finder. CP
 *
 * Revision 2.24  2003/05/06 15:33:49  mmiller
 * iCommitting changes to turn on multiple regions (StiPlacement::StiRegion -> kMidRapidity, kForwardRapidity, etc).
 * Also added a point to StiToolkit for StiMaker.  This allows for the req. GetDataSet calls in the FTPC code.
 * Not so elegant...
 *
 * Revision 2.23  2003/04/29 18:48:21  pruneau
 * *** empty log message ***
 *
 * Revision 2.22  2003/04/22 21:20:05  pruneau
 * Added hit filter
 * Tuning og finder pars
 * Tuning of KalmanTrackNode
 *
 * Revision 2.21  2003/04/10 12:02:13  pruneau
 * various changes
 *
 * Revision 2.20  2003/03/31 17:18:47  pruneau
 * various
 *
 * Revision 2.19  2003/03/17 17:45:31  pruneau
 * *** empty log message ***
 *
 * Revision 2.18  2003/03/14 20:50:29  pruneau
 * Added groupId member and accessor functions to StiDetector, StiDetectorGroup, StiDetectorBuilder,
 * and modified getNodes of the StiKalmanTrack class to use it. This eliminates explicit
 * references to Tpc and Svt within StiKalmanTrack...
 *
 * Revision 2.17  2003/03/14 19:02:20  pruneau
 * various minor updates
 *
 * Revision 2.16  2003/03/13 21:21:26  pruneau
 * getPhase() fixed. MUST inclde -helicity()*pi/2
 *
 * Revision 2.15  2003/03/13 18:59:08  pruneau
 * various updates
 *
 * Revision 2.14  2003/03/13 16:38:11  andrewar
 * Made use of X0() calls in getTrackRadLength()
 *
 * Revision 2.13  2003/03/13 15:16:41  pruneau
 * fixed getPhi, getPseudoRapdity, getPhase methods
 *
 * Revision 2.12  2003/03/12 17:57:29  pruneau
 * Elss calc updated.
 *
 * Revision 2.11  2003/03/04 15:16:22  andrewar
 * Added getTrackRadLength function to return radiation thickness along track (%).
 *
 */



//Std
#include <stdexcept>
#include <cmath>

//SCL
#include "StThreeVector.hh"
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"
#include "StPhysicalHelixD.hh"

#include "StHit.h"

//Sti
#include "StiToolkit.h"
#include "StiTrackFinder.h"
#include "StiHit.h"
#include "StiDefaultMutableTreeNode.h"
#include "StiKalmanTrackNode.h"
#include "StiKalmanTrack.h"
#include "StiDetector.h"
#include "StiPlacement.h"
#include "StiMaterial.h"
#include "StiHitErrorCalculator.h"
#include "StPhysicalHelixD.hh"
#include "StHelix.hh"
#include "StiKalmanTrackFitterParameters.h"
#include "StiKalmanTrackFinderParameters.h"
#include "StiHitContainer.h"

ostream& operator<<(ostream&, const StiHit&);

Factory<StiKalmanTrackNode>* StiKalmanTrack::trackNodeFactory = 0;
StiKalmanTrackFinderParameters* StiKalmanTrack::pars = 0;
StiKalmanTrackFitterParameters* StiKalmanTrack::fitpars = 0;

int debugCount=0;

/*! 
   Reset the class members to their default state.
   This method is called by the ctor of the class to initialize the
   members of the class to an "empty" or null track state. The
   method must also be called everytime an instance of this class is
   retrieved from its factory in order to set the first and last
   nodes to "null" thus guaranteeing that the track object is empty
   i.e. does not represent any track and is thus ready for a new
   search and reconstruction.  
 */
void StiKalmanTrack::reset()
{
  firstNode = 0;
  lastNode  = 0;
  trackingDirection = kOutsideIn;
  fittingDirection  = kOutsideIn;
  mSeedHitCount = 0;
  m      = -1.;
  mFlag  = 0;

  _vDca=-1;
  _vChi2=-2;
}

 

/*! 
  Set the factory used for the creation of kalman track nodes.
  \see StiKalmanTrackNodeFactory
*/
void StiKalmanTrack::setKalmanTrackNodeFactory(Factory<StiKalmanTrackNode>* val)
{
  trackNodeFactory = val;
}


/*!
  Add a hit to this track.
  <p>
  If the current lastNode is non null, 
  <ol>
  <li>Insert the given hit in a StiKalmanTrackNode instance.</li>
  <li>Add the new node as a child to the current last node.</li>
  <li>Make the new node the last node of this track.</li>
  </ol>
  else
  <ol>
  <li>Insert the given hit in a StiKalmanTrackNode instance.</li>
  </ol>
*/
StiKalmanTrackNode * StiKalmanTrack::add(StiHit *h,double alpha, double eta, double curvature, double tanl)
{
  TRACKMESSENGER << "StiKalmanTrack::add(...) -I- Started"<<endl;
  StiKalmanTrackNode * n = trackNodeFactory->getInstance();
  TRACKMESSENGER << "StiKalmanTrack::add(...) -I- have n"<<endl;
  if (!n)
    {
      TRACKMESSENGER << "StiKalmanTrack::add(...) -E- n==0"<<endl;
      throw runtime_error("StiKalmanTrack::add(...) -F- n==0");
    }
  TRACKMESSENGER << "StiKalmanTrack::add(...) -I- have valid n"<<endl;
  n->initialize(h,alpha,eta,curvature,tanl);

  // calculate the estimate error of this node
  const StiHitErrorCalculator * calc = h->detector()->getHitErrorCalculator();
  if (!calc)
    {
      cout << "SKT::add(...) -E- Detector:"<<h->detector()->getName()<<" has no calculator"<<endl;
      throw runtime_error("SKT::add(...) -E- calc==0");
    }
  calc->calculateError(n);

  if (lastNode!=0)
    lastNode->add(n);
  else 
    firstNode = n;
  lastNode = n;
  TRACKMESSENGER << "StiKalmanTrack::add(...) -I- Done"<<endl;
  return lastNode;
}

// remove the given hit (and node) from this track
// It is assume that the hit has at most one child
void StiKalmanTrack::removeHit(StiHit *h)
{
  StiKalmanTrackNode * n = findHit(h);
  if (n!=0)
    {
      // the hit belongs to this track, let's remove it
      StiKalmanTrackNode * cn = static_cast<StiKalmanTrackNode *> (n->getFirstChild());
      if (cn==0)
	{
	  // no child, this is the last hit
	  StiKalmanTrackNode * pn = static_cast<StiKalmanTrackNode *> (n->getParent());
	  if (pn==0)
	    firstNode = 0;
	  else
	    pn->remove(n);
	}
      else
	{
	  // child exist
	  StiKalmanTrackNode * pn = static_cast<StiKalmanTrackNode *> (n->getParent());
	  if (pn==0)
	    {
	      // no parent, this is the first hit
	      cn->setParent(0); 
	      firstNode = cn;
	    }
	  else
	    {
	      pn->remove(n);
	      pn->add(cn);
	    }
	}
    }
  else
    throw logic_error("StiKalmanTrack::removeHit() - Error - Given hit does not belong to this track");
}

/*!
  Current implementation only considers the first child of each node
  and must therefore be revised.
*/
StiKalmanTrackNode * StiKalmanTrack::findHit(StiHit * h)
{
  if (firstNode==0)
    return 0;
  else
    {
      if (h==firstNode->getHit())
	return firstNode;
      StiKalmanTrackNode * n = firstNode;
      while (n->getChildCount()>0)
	{
	  n = static_cast<StiKalmanTrackNode *> (n->getFirstChild());
	  if (h==n->getHit())
	    return firstNode;
	}
    }
  return 0;
}

/*! Initialization of this kalman track from external parameters.
  <p>
  This track object is initialized on the basis of parameters determined externally. The
  parameters consist of the track curvature, the tangent of pitch angle, the origin of 
  the helix, and a vector of hits already associated with the track.
  
  <h3>Arguments:</h3>
  <TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="100%">
  <TR> <TD WIDTH="10%">curvature</TD> <TD WIDTH="90%">1/radius of the tack.</TD>  </TR>
  <TR> <TD WIDTH="10%">tanl</TD>      <TD WIDTH="90%">tan(pitch angle)</TD> </TR>
  <TR> <TD WIDTH="10%">origin</TD>    <TD WIDTH="90%">origin of the track in global coordinates.</TD> </TR>
  <TR> <TD WIDTH="10%">v</TD>         <TD WIDTH="90%">vector of hits associated with this track.</TD> </TR>
</TABLE>
<h3>Algorithm:</h3>
<ol>
<li>Verify that a valid node factory exists.</li>
<LI>Use local arrays state and error to add and set all nodes of this track.</LI>
<LI>Use the same curvature, and tanl for all nodes as supplied in argument list.</li>
<li>Use Unit matrix for error matrix.</li>
<li>Loop over all hits of the input hit vector and create a track node for each.</LI>
<li>Paramters of the track node are set according to the y,z of the hits added.</LI>
<li>Hits given are transformed in the local coordinates of their detector.
</ol>
<h3>Notes:</h3>
<OL>
<LI>Throws a logic_error exception if no track node factory is available.</li>
<LI>Throws a logic_error exception if the factory
  is not a castable to a factory of StiKalmanTrackNode.</li>
<li>Throws a logic error exception if hits do not have a valid pointer to a detector object.</li>
</OL>
*/
void StiKalmanTrack::initialize(double curvature,
				double tanl,
				const StThreeVectorD& origin,
				const vector<StiHit*> & hits)
{
  //cout << "StiKalmanTrack::initialize() -I- Started"<<endl;
  reset();
  vector<StiHit*>::const_iterator it;
  //StiKalmanTrackNode * node  = 0;
  double eta   =-99999.;
  double alphaP=-99999.;
  double alpha;
  StThreeVectorD temp;
  const StiDetector* detector;
  for (it=hits.begin(); it!=hits.end(); ++it)
    {
      detector = (*it)->detector();
      if (!detector) 
				{
					cout <<"StiKalmanTrack::initialize() -F- detector==0"<<endl;
					throw logic_error("StiKalmanTrack::initialize() - FATAL - Hit has null detector.");
				}
      // if alpha is same, avoid recalculating eta
      alpha = detector->getPlacement()->getNormalRefAngle();
      if (alphaP!=alpha)
				{
					temp = origin;
					temp.rotateZ(-alpha);
					eta = curvature*temp.x();
					alphaP=alpha;
				}
      add((*it),alpha,eta,curvature,tanl);
    }
  //cout << "StiKalmanTrack::initialize() -I- Done"<<endl;
}

StiKalmanTrackNode * StiKalmanTrack::getNodeNear(double x) const
{
  if (firstNode==0) throw logic_error("StiKalmanTrack::getNodeNear() - FATAL - firstNode==0");
  StiDefaultMutableTreeNodeVector* nodes  = firstNode->breadthFirstEnumeration();
  double minDist  = 1.E10;
  double xx, diff;
  StiKalmanTrackNode * bestNode = firstNode;
  StiDefaultMutableTreeNodeIterator it;
  for (it=nodes->begin(); it!=nodes->end(); it++)
    {
      StiKalmanTrackNode * node = static_cast<StiKalmanTrackNode *>(*it);
      xx = node->_x;
      diff = xx-x; if (diff<0) diff = -diff;
      //TRACKMESSENGER << "===> x/diff:" << xx << "\t" << diff << endl;
      if (diff<minDist) 
	{
	  minDist = diff;
	  bestNode = node;
	}
    }
  delete nodes;
  return bestNode;
}

/*!
  Returns the hit position associated with the node nearest to the given "x" value.
*/
StThreeVector<double>
StiKalmanTrack::getHitPositionNear(double x) const
{
  StiKalmanTrackNode * node = getNodeNear(x);
  if (node==0)
    throw logic_error("StiKalmanTrack::getHitPositionNear(double x) - ERROR - node==0");
  StiHit * hit = node->getHit();
  if (hit==0)
    throw runtime_error("StiKalmanTrack::getHitPositionNear(double x) - ERROR - hit==0");
  StThreeVectorF pos = hit->globalPosition();
  return StThreeVector<double>( pos.x(), pos.y(), pos.z() );
}

/// Find and return the nearest track point in the local coordinates
/// of the detector this track lies in.
StThreeVector<double> StiKalmanTrack::getPointNear(double x) const
{
  StiKalmanTrackNode * node = getNodeNear(x);
  if (node==0) throw logic_error("StiKalmanTrack::getPointNear(double x) - ERROR - node==0");
  return node->getPoint();
}

StThreeVector<double> StiKalmanTrack::getGlobalPointNear(double x) const
{
  StiKalmanTrackNode * node = getNodeNear(x);
  if (node==0) throw logic_error("StiKalmanTrack::getGlobalPointNear(double x) - ERROR - node==0");
  return node->getGlobalPoint();
}

// returns a point along the track in global coordinates at radius "x"
// Note that if the track does not pass at or near the given x value
// the null vector is returned.
//
// Algorithm: One first look for the node closest to "x". A "fresh"
// node is obtained from the factory, and its state is set to that
// of the found node. Then the fresh node is "propagated" to the 
// desired "x" position. A null vector (i.e. [0,0,0]) is returned
// if anything fails...
StThreeVector<double> StiKalmanTrack::getGlobalPointAt(double x) const
{
  StiKalmanTrackNode * nearNode = getNodeNear(x);
  if (nearNode==0) throw logic_error("StiKalmanTrack::getGlobalPointAt(double x) - ERROR - nearNode==0");
  Factory<StiKalmanTrackNode> * f = static_cast<Factory<StiKalmanTrackNode>*>(trackNodeFactory);
  if (f==0) throw logic_error("StiKalmanTrack::getGlobalPointAt(double x) - ERROR - no factory f==0");
  StiKalmanTrackNode * n = f->getInstance();
  if (n==0) throw logic_error("StiKalmanTrack::getGlobalPointAt(double x) - ERROR - n==0");
  n->reset();
  n->setState(nearNode);
  int status = n->propagate(x,0,trackingDirection);
  if (status<0) throw runtime_error(" StiKalmanTrack::getGlobalPointAt() - WARNING - Position not reachable by this track");
  return n->getGlobalPoint();
}

StThreeVector<double> StiKalmanTrack::getMomentumNear(double x)
{
  StiKalmanTrackNode * node = getNodeNear(x);
  double p[3];
  double e[6];
  node->getMomentum(p,e);
  StThreeVector<double> p3(p[0],p[1],p[2]);
  p3.rotateZ(node->_alpha);
  return p3;
}

StThreeVector<double> StiKalmanTrack::getMomentumAtOrigin() const
{
  double px,py,pz;
  px=py=pz=0;
  StiKalmanTrackNode * inner = getInnerMostNode();
  if (inner==0)throw logic_error("StiKalmanTrack::getMomentumAtOrigin() - ERROR - No node");
  inner->propagate(0.,0,trackingDirection);
  double p[3];
  double e[6];
  inner->getMomentum(p,e);
  StThreeVector<double> p3(p[0],p[1],p[2]);
  p3.rotateZ(inner->_alpha);
  return p3;
}

/*! Return the track sign
   <h3>Notes</h3> 
   <ol>
   <li>Use the last node and the field.</li>
   </ol>
*/
int StiKalmanTrack::getCharge() const
{
  return  lastNode->getCharge();
}

/// Return the track chi2 per dof
/// <p>
/// The track chi2 is calculated from the incremental chi2 of all nodes carrying a hit that contributed to the fit of the track. 
/// Note that a hit is not counted as contributing to the fit if its chi2 exceeds "fitpars->getMaxChi2()"
/// Note that this function returns "-1" if the number of fit points is smaller than 6
double  StiKalmanTrack::getChi2() const
{
  double fitHits   = 0;
  double trackChi2 = 0;
  double nodeChi2  = 0;
  double maxChi2   = fitpars->getMaxChi2();
  double theChi2 = 1.e+60;
  if (firstNode)
    {
      theChi2 = 0;
      StiKTNBidirectionalIterator it;
      for (it=begin();it!=end();it++)
	{
	  if ((*it).getHit())
	    {
	      nodeChi2 = (*it)._chi2;
	      if (nodeChi2<maxChi2) 
		{
		  trackChi2 += nodeChi2;
		  ++fitHits;
		}
	    }
	}
    }
  if (fitHits>5)
    return trackChi2/(fitHits-5.);
  else
    return -1.;
}


/*! 
	Calculate and return the number of hits on this track. 
   <h3>Notes</h3> 
   <ol>
   <li>Iterate through all nodes of this track.</li>
   <li>Count number of hits.</li>
   </ol>
	 \return number of hits.
*/
int StiKalmanTrack::getPointCount() const
{
  int nPts = 0;
  if (firstNode)
    {
      StiKTNBidirectionalIterator it;
      for (it=begin();it!=end();it++)
	{
	  if ((*it).getHit())
	    nPts++;
	}
    }
  return nPts;
}

/*! Calculate and return the maximum possible number of hits on this track. 
  <h3>Notes</h3> 
   <ol>
   <li>Iterate through all nodes of this track.</li>
   <li>Count active layers.</li>
   <li>Use the (y,z) position of the node to determine whether point is on
       active region of the detector i.e. RDO were functional.</li>
   </ol>
	 \return maximum number of points
*/
int StiKalmanTrack::getMaxPointCount() const
{
  int nPts = 0;
  if (firstNode)
    {
      StiKTNBidirectionalIterator it;
      int k=0;

      for (it=begin();it!=end();it++,k++)
	{
	  StiHit* h = (*it).getHit();
	  if (h)
	    {
	       const StiDetector * detector = h->detector();
	       if (detector)
		  {
		     if (detector->isActive((*it)._p0,(*it)._p1))
			      	nPts++;
		  }
	       //else
	       //  nPts++; // vertex have no detector...
	     }
	}
    }
  return nPts;
}
int StiKalmanTrack::getMaxPointCount(int detectorId) const
{
  int nPts = 0;
  if (firstNode)
    {
      StiKTNBidirectionalIterator it;
      int k=0;

      for (it=begin();it!=end();it++,k++)
	{
	  StiHit* h = (*it).getHit();
	  if (h)
	    {
	       const StiDetector * detector = h->detector();
	       if (detector)
		  {
		     if (detector->isActive((*it)._p0,(*it)._p1) &&
			 detector->getGroupId() == detectorId)
			      	nPts++;
		  }
	       //else
	       //  nPts++; // vertex have no detector...
	     }
	}
    }
  return nPts;
}


/*! Return the number of gaps (active layers with no hits) along this track.
  <h3>Notes</h3> 
  <ol>
  <li>A gap consists of one or multiple contiguous active layers through which this track
  passes.</li>
  <li>There can be gaps on the inside or the outside of the track if no hits are found there.</li>
  </ol>
  \returns number of gaps.
*/
int    StiKalmanTrack::getGapCount()    const  
{
  int gaps = 0;
  if (firstNode)
    {
      StiKTNBidirectionalIterator it;
      bool inGap = false;
      for (it=begin();it!=end();it++)
	{
	  const StiDetector * detector = (*it).getDetector();
	  if (detector && detector->isActive())
	    {
	      if ((*it).getHit())
		{
		  if (inGap) 
		    inGap = false;
		}
	      else
		{
		  if (!inGap)
		    {
		      inGap = true;
		      gaps++;
		    }										
		}
	    }
	}
    }
  return gaps;
}

/*! Return the number of hits (points) used in the fit of this track.
  <h3>Notes</h3> 
  <ol>
  <li>Currently no difference is made between points on the track and fit points 
  on the track.</li>
  <li>Call "getPointCount()" to get the count.</li>
  </ol>
  \return number of hits on this track.
*/
int StiKalmanTrack::getFitPointCount()    const  
{
    int fitPointCount  = 0;
    if (firstNode) 
      {
	double chi2Max = fitpars->getMaxChi2();
	StiKTNBidirectionalIterator it;
	for (it=begin();it!=end();it++) 
	  {
	    StiKalmanTrackNode& ktn = (*it);
	    if (ktn.getChi2()<chi2Max) ++fitPointCount;
	  }
      }    
  return fitPointCount;
}

///Get number of fit points in given detector
int StiKalmanTrack::getFitPointCount(int detectorId)    const  
{
    int fitPointCount  = 0;
    if (firstNode) 
      {
	double chi2Max = fitpars->getMaxChi2();
	StiKTNBidirectionalIterator it;
	for (it=begin();it!=end();it++) 
	  {
	    StiKalmanTrackNode& node = (*it); 
	    StiHit* hit = node.getHit();
	    if (hit && 
		hit->detector() && 
		node.getDedx()>0. &&  
		detectorId==hit->detector()->getGroupId() &&
		node.getChi2()<chi2Max) 
	      {
		fitPointCount++;
	      }
	  }
      }    
  return fitPointCount;
}




/*! Calculate and return the track length.
  <h3>Notes</h3> 
   <ol>
   <li>Using helix track model in global reference frame.</li>
   <li>Using only inner most and outer most hits associated with this track.</li>
   </ol>
   \return tracklength
   \throws runtime_error
*/
double StiKalmanTrack::getTrackLength() const
{
  StiKalmanTrackNode * inNode = getInnerMostHitNode(2);
  StThreeVectorD in(inNode->getX(),inNode->getY(),inNode->getZ());
  in.rotateZ(inNode->getRefAngle());
  StiKalmanTrackNode * otNode = getOuterMostHitNode(2);
  StThreeVectorD ot(otNode->getX(),otNode->getY(),otNode->getZ());
  ot.rotateZ(otNode->getRefAngle());
  StPhysicalHelixD hlx(fabs(inNode->getCurvature()),
		            inNode->getDipAngle(),
		            inNode->getPhase(),
		            in,
		            inNode->getHelicity());
  double per = hlx.period();
  double len = hlx.pathLength(ot);
//  StHelix can return negative length if -ve path is shorter then +ve one
//  period ia added in this case;
  while(len<0  ) {len+=per;}
//  StHelix can return length > period id dip is almost zero and by chance
//  this length is more suitable for Z distance. It is wrong solution even
//  it has better distance to end point. Subtruct period in this case
  while(len>per) {len-=per;}

  return len;
}


/*! Calculate and return the track segment length between two nodes.
  <h3>Notes</h3>
  <ol>
  <li>This is basically a wrapper for the StiKalmanTrackNode::pathLToNode function.</li>
  </ol>
  \return length
 */
//  inline double StiKalmanTrack::calculateTrackSegmentLength(const StiKalmanTrackNode &p1, const StiKalmanTrackNode &p2) const
//  {
//    return p1.pathLToNode(&p2);
//  }

/*! Calculates the radiation length of material crossed by the track.

 */
double StiKalmanTrack::getTrackRadLength() const
{
  double x1, x2, x3;  //lengths in different media
  double totalR=0.;
  //Are we going in or out? Makes a difference which material to call
  bool trackIn = (kOutsideIn==getTrackingDirection());

  StiKTNBidirectionalIterator tNode = begin();

  //set initial conditions for tNode, the 'current' node;
  //will also need 'nextNode', ie node which is next 
  StiKalmanTrackNode *thisNode = &(*tNode);

  x1=thisNode->pathlength()/2.; 
  x3=0.;


  while ((tNode++)!=end() && (*tNode).getDetector())
    {

      StiKalmanTrackNode *nextNode = &(*(tNode)); //incrimented tNode
    

      x2=thisNode->pathLToNode(nextNode); 
      x3=nextNode->pathlength()/2.;

      if(x3==-1.) continue;  
      //if there is an error with "next" node, proceed along track
      //without updating current node. This should provide
      //function thisNode=thisNode, nextNode=new node

      if (x2> (x1+x3)) x2 = x2 - x1 - x3; //x2 is now the gap distance
      else x2=0.;

      TRACKMESSENGER
	   <<"getTrackRadLength:"
	   <<"\n\tIn Detector: "<<thisNode->getDetector()->getName()
	   <<"\n\t\tMaterial: "<<thisNode->getDetector()->getMaterial()
	   <<"\n\t\tLength: "<<x1
	   <<"\t\tGap Length: "<<x2
           <<"\n\tNext Detector: "<<nextNode->getDetector()->getName()
	   <<"\n\t\tMaterial: "<<nextNode->getDetector()->getMaterial()
	   <<"\n\t\tLength: "<<x3
           << endl;
      if(trackIn)
	{
	  if (thisNode->getX0()>0)    totalR += x1/thisNode->getX0();
	  if (nextNode->getGasX0()>0) totalR += x2/nextNode->getGasX0();
	  if (nextNode->getX0()>0)    totalR += x3/nextNode->getX0();
	}
      else
	{
	  if (thisNode->getX0()>0)    totalR += x1/thisNode->getX0();
	  if (thisNode->getGasX0()>0) totalR += x2/thisNode->getGasX0();
	  if (nextNode->getX0()>0)    totalR += x3/nextNode->getX0();
	}
      //cache nextNode for next iteration...
      thisNode = nextNode;
      x1       = x3;
    }
  if (totalR>200.)
    cout <<"StiKalmanTrack::getTrackRadLength() -W- Total Rad Length Error: "<<totalR;
  return totalR;
}

/*! Return the inner most hit associated with this track.
   <h3>Notes</h3>
   <ol>
   <li>Throws logic_error exception if firstNode or lastNode are not defined, or if track has no hit.</li>
   <li>Loop through all nodes from end() to begin() (or vice versa if tracking 
       direction is outside-in) and search for node with hit. Return first hit found.</li>
   </ol>
	 \return inner most hit node on this track
	 \throws logic_error
*/
StiKalmanTrackNode * StiKalmanTrack::getInnOutMostNode(int inot,int qua)  const
{
  if (firstNode==0 || lastNode==0)
 {
  //cout << "StiKalmanTrack::getInnOutMostHitNode() -E- firstNode||lastNode==0" << endl;
  throw runtime_error("StiKalmanTrack::getInnOutMostNode() -E- firstNode||lastNode==0");
 }
  
  StiKalmanTrackNode *node;
  if (trackingDirection!=kOutsideIn) inot = !inot;
  StiKTNBidirectionalIterator it =(inot) ? begin():rbegin();
  for (;(node=it());it++){
    if (qua   && !node->getHit()) 		continue;
    if (qua>1 && node->getChi2()>10000.)	continue;
    return node;
  }
  //cout << "StiKalmanTrack::getInnOutMostHitNode() -E- Track has no hit" << endl;
  throw runtime_error("StiKalmanTrack::getInnOutMostNode() -E- Track has no hit");
}
StiKalmanTrackNode * StiKalmanTrack::getOuterMostHitNode(int qua)  const
{
  return getInnOutMostNode(1,qua);
}


/*! Return the inner most hit associated with this track.
   <h3>Notes</h3>
   <ol>
   <li>Throws logic_error exception if firstNode or lastNode are not defined, or if track has no hit.</li>
   <li>Loop through all nodes from begin() to end() (or vice versa if tracking 
       direction is outside-in) and search for node with hit. Return first hit found.</li>
   </ol>
	 \return outer most hit node on this track
*/

StiKalmanTrackNode * StiKalmanTrack::getInnerMostHitNode(int qua)   const
{
  return getInnOutMostNode(0,qua);
}

/*! Return true if inner most hit associated with this track is main vertex.
   <h3>Algorithm</h3>
   <ol>
   <li>Find the inner most hit node associated with this tracks.</li>
   <li>Return true if "x" of inner most hit is less than 2 cm.
   </ol>
	 \return true if "x" of inner most hit is less than 2 cm.
*/
bool  StiKalmanTrack::isPrimary() const
{
  StiKalmanTrackNode * node = getInnerMostHitNode();
  return (fabs(node->_x)<2.) ? true : false;
}

/*! Swap the track node sequence inside-out
   <h3>Algorithm</h3>
   <ol>
   <li>Loop through the node sequence starting with the firstNode and invert the parent child relationships.</li>
   <li>Include removal of all children for each node.</li>
   <li>Include change of parent</li>
   <li>Set parent of last node as "0" to complete swap.</li>
   <li>Change the "trackingDirection" flag to reflect the swap.
   </ol>
 */
void StiKalmanTrack::swap()
{
  StiKalmanTrackNode * parent = 0;
  StiKalmanTrackNode * child  = 0;
  StiKalmanTrackNode * grandChild = 0;
  
  parent = firstNode;
  firstNode = lastNode;
  lastNode = parent; 
  if (parent && parent->getChildCount()>0)
    {
      child  = dynamic_cast<StiKalmanTrackNode *>(parent->getFirstChild());
      parent->removeAllChildren();			
      while (child)
	{
	  if (child->getChildCount()>0)
	    {
	      grandChild = dynamic_cast<StiKalmanTrackNode *>(child->getFirstChild());
	      child->removeAllChildren();
	    }
	  else
	    grandChild = 0;
	  child->add(parent);
	  parent = child;
	  child = grandChild;
	}
      // last parent has no parent
      parent->setParent(0);
    }
  if (trackingDirection==kOutsideIn)
    trackingDirection = kInsideOut;
  else
    trackingDirection = kOutsideIn;
}


///return vector of nodes with hits
vector<StiKalmanTrackNode*> StiKalmanTrack::getNodes(int detectorId) const
{
  StiKalmanTrackNode* leaf = getLastNode();
  StiKTNForwardIterator it(leaf);
  StiKTNForwardIterator end = it.end();
  vector<StiKalmanTrackNode*> nodeVec;
  while (it!=end) 
    {
      const StiKalmanTrackNode& node = *it;
      StiHit* hit = node.getHit();
      if (hit && 
	  hit->detector() && 
	  node.getDedx()>0. &&  
	  detectorId==hit->detector()->getGroupId() ) 
	{
	  nodeVec.push_back(const_cast<StiKalmanTrackNode*>(&node));
	}
      ++it;
    }
  return nodeVec;
}

///return hits;
vector<StMeasuredPoint*> StiKalmanTrack::stHits() const
{
  StiKalmanTrackNode* leaf = getLastNode();
  StiKTNForwardIterator it(leaf);
  StiKTNForwardIterator end = it.end();
  vector<StMeasuredPoint*> hits;
  for (;it!=end;++it) {
    const StiKalmanTrackNode& node = *it;
    if (node.getChi2()>10000.) continue;
    StiHit* hit = node.getHit();
    if (!hit) 			continue;
    StHit *stHit = (StHit*)dynamic_cast<const StHit*>(hit->stHit());
    if (!stHit) 		continue;
    hits.push_back(stHit);
  }
  return hits;
}


/*! Prune the track to select the best branch of the tree identified by given leaf node.
  <p>
  The best brach is assumed to be the one given by the leaf "node".
  All siblings of the given node, are removed, and iteratively
  all siblings of its parent are removed from the parent of the
  parent, etc.
*/
void StiKalmanTrack::prune()
{
  StiKalmanTrackNode * node   = lastNode;
  StiKalmanTrackNode * parent = static_cast<StiKalmanTrackNode *>(node->getParent());
  while (parent)
    {
      parent->removeAllChildrenBut(node);
      node = parent;
      parent = static_cast<StiKalmanTrackNode *>(node->getParent());
    }
}

/*! Declare hits associated with given track as used.
  <p>
  Declare hits on the track ending at "node" as used. 
  This method starts with the last node and seeks the
  parent of each node recursively. The hit associated with each
  node (when there is a hit) is set to "used".
*/	
void StiKalmanTrack::reserveHits()
{
  StiKTNForwardIterator it(lastNode);
  for_each( it, it.end(), SetHitUsed() );
}

/*! Extend track to the given vertex.
  <p>
  Attempt an extension of the track  the given vertex. 
  <p>
  <ol>
  <li>Get node from node factory.</li>
  <li>Reset node.</li>
  <li>Propagate the node from given parent node "sNode", to the given vertex using a 
  call to "propagate".</li>
  <li>Evaluate the chi2 of the extrapolated if the vertex is added to the track. Done
  using a call to "evaluateChi2".</li>
  <li>If chi2 is less than max allowed "maxChi2ForSelection", update track parameters
  using the vertex as a measurement and add the vertex to the track as the last node.</li>
  </ol>
  <h3>Notes</h3>
  <ul>
  <li>Throws logic_error if no node can be obtained from the node factory.</li>
  <li>The methods "propagate", "evaluateChi2", and "updateNode" may throw 
  runtime_error exceptions which are NOT caught here...</li>
  </ul>
*/
bool StiKalmanTrack::extendToVertex(StiHit*vertex, const StiDetector * alternate)
{
  if (!alternate)
    return extendToVertex(vertex);
  cout << " alternate propagate =========="<<endl;
  cout << *alternate<<endl;
  cout << "lastNode:"<<*lastNode<<endl;
  StiKalmanTrackNode * tNode = trackNodeFactory->getInstance();
  if (tNode==0) throw logic_error("SKTF::extendTrackToVertex() -E- tNode==null");
  tNode->reset();
  int status = tNode->propagate(lastNode,alternate,trackingDirection);
  cout << "propagate status:"<<status<<endl;
  return false;
}


bool StiKalmanTrack::extendToVertex(StiHit* vertex)
{
  if (trackingDirection==kInsideOut) 
    throw logic_error("SKT::extendToVertex(const StiHit*) -E- Extension to vtx only allowed for OutsideIn");
  double chi2;
  StiKalmanTrackNode * sNode=0;
  StiKalmanTrackNode * tNode=0;
  bool trackExtended = false;

	StiKalmanTrackNode * innerMostHitNode = getInnerMostHitNode();
	if (!innerMostHitNode) return false;
	// track with hits in the outer portion of the TPC only are not considered
	if (innerMostHitNode->getX()>100.) return false;
		
  StiHit localVertex = *vertex;
  sNode = lastNode;

  double xxxx = lastNode->_x;
  bool   check = false;
  //if (xxxx>4.1) check = true;

  localVertex.rotate(sNode->getRefAngle());
  tNode = trackNodeFactory->getInstance();
  if (tNode==0) throw logic_error("SKTF::extendTrackToVertex() -E- tNode==null");
  tNode->reset();
  StiHit *myHit;
  //cout << "SKT::extendToVertex() -I- x,y,z:"<< localVertex.x() 
  //     << " " <<  localVertex.y() << " " << localVertex.z() << endl;
  //cout << "SKT::extendToVertex() -I- sNode->_x:"<<sNode->_x<<endl;
  //cout << "SKT::extendToVertex() -I-0 tNode->_x:"<< tNode->_x<<endl;
  if (tNode->propagate(sNode, &localVertex,trackingDirection))
    { 
      //cout << " on vertex plane:";
      chi2 = tNode->evaluateChi2(&localVertex); 
      
      double dx,dy,dz,d;
      dx=tNode->_x- localVertex.x();
      dy=tNode->_p0- localVertex.y();
      dz=tNode->_p1- localVertex.z();
      d= ::sqrt(dx*dx+dy*dy+dz*dz);
      //cout << "chi2 @ vtx " << chi2 << endl;
      /*	cout << " dx:"<< dx
		<< " dy:"<< dy
		<< " dz:"<< dz
		<< " d: "<< d<<endl;*/
      _vDca = d;
      _vChi2= chi2;
      //if (chi2<pars->maxChi2Vertex)
      if (d<4.)
	{
	  //_dca = ::sqrt(dy*dy+dz*dz);
	  myHit = StiToolkit::instance()->getHitFactory()->getInstance();
	  *myHit = localVertex;
	  tNode->setHit(myHit);
	  tNode->setChi2(chi2);
	  tNode->setDetector(0);
	  add(tNode);
	  trackExtended = true;
	}
    }
  //else
  //  cout <<" TRACK NOT REACHING THE VERTEX PLANE!"<<endl;
  return trackExtended;
}

bool StiKalmanTrack::find(int direction)
{
  bool trackExtended=false;  
  bool trackExtendedOut=false;
  setFlag(0);
  // invoke tracker to find or extend this track
  //cout <<"StiKalmanTrack::find(int) -I- Outside-in"<<endl;
  try 
    {
      if (trackFinder->find(this,kOutsideIn))
	{
	  //cout<<"/////////////////fit(InOut)";
	 fit(kInsideOut);  
	  //------ 
	 fit(kOutsideIn);
	  trackExtended = true;
	  //cout<<"/////////////////fit(InOut) Done";
	}	
    }
  catch (runtime_error & error)
    {
      cout << "SKT:find(int dir) -W- ERROR:" << error.what()<<endl;
    }
  // decide if an outward pass is needed.
  const StiKalmanTrackNode * outerMostNode = getOuterMostHitNode();
  if (!outerMostNode)
    {
      setFlag(-1);
      return false;
    }
  if (outerMostNode->getX()<185. )
    {
      // swap the track inside-out in preparation for the outward search/extension
      //cout<<"StiKalmanTrack::find(int) -I- Swap track"<<endl;
      swap();      
      try
	{
	  trackExtendedOut= trackFinder->find(this,kInsideOut);
	}
      catch (...)
	{
	  cout << "StiKalmanTrack::find(int direction) -W- Exception while in insideOut find"<<endl;
	}
      try
	{
	  if (trackExtendedOut) fit(kOutsideIn);
	}
      catch (...)
	{
	  cout << "StiKalmanTrack::find(int direction) -W- Exception while in OutsideIn fit"<<endl;
	} 
      //cout<<"StiKalmanTrack::find(int) -I- Swap back track"<<endl;
      swap();
      setTrackingDirection(kOutsideIn);
      //cout<<"StiKalmanTrack::find(int) -I- Swap back track Done"<<endl;
    }
  setFlag(1);
  //cout << " find track done" << endl;
  return trackExtended||trackExtendedOut;
}

void StiKalmanTrack::setParameters(StiKalmanTrackFinderParameters *parameters)
{
  pars = parameters;
}

void StiKalmanTrack::setFitParameters(StiKalmanTrackFitterParameters *parameters)
{
  fitpars = parameters;
}

///Return all the hits associated with this track, including those with a large incremental
///chi2 that may not contribute to the fit.
vector<StiHit*> StiKalmanTrack::getHits()
{
  vector<StiHit*> hits;
  StiKalmanTrackNode* leaf = getLastNode();
  StiKTNForwardIterator it(leaf);
  StiKTNForwardIterator end = it.end();
  for (;it!=end;++it) 
    {
      const StiKalmanTrackNode& node = *it;
      if (node.getChi2()>10000.) continue;
      StiHit* hit = node.getHit();
      if (hit) hits.push_back(hit);
    }
  return hits;
}

/// Return global dca of the track relative to given vertex or point.
double  StiKalmanTrack::getDca(const StiHit * vertex)    const
{
  StiKalmanTrackNode*	lastNode;
  StiKalmanTrackNode*	node;

  lastNode = getInnerMostHitNode(); 
  if (lastNode->_x<2.)
    node = static_cast<StiKalmanTrackNode*>(lastNode->getParent());
  else
    node = lastNode;
  StThreeVectorD originD(node->getX(),node->getY(),node->getZ());
  StThreeVectorD vxDD(vertex->x_g(), vertex->y_g(),vertex->z_g());
  StPhysicalHelixD physicalHelix(0.,0.,0.,originD,-1);
  originD.rotateZ(node->getRefAngle());
  physicalHelix.setParameters(fabs(node->getCurvature()),
			       node->getDipAngle(),
			       node->getPhase(),
			       originD,
			       node->getHelicity());
  double dca = physicalHelix.distance(vxDD);
  return dca;
}

///Extrapolate this track to the beam axis (x==0) to provide an estimate of the
///track location at the beam axis.
///Returns a null pointer is the operation cannot be completed i.e. the track does not reach
///the beam axis plane.
StiKalmanTrackNode * StiKalmanTrack::extrapolateToBeam()
{
  StiKalmanTrackNode * innerMostNode = getInnerMostNode();
  //return null if there is no node to extrapolate from.
  if (!innerMostNode) return 0;
  StiKalmanTrackNode * n = trackNodeFactory->getInstance();
  if (n->propagateToBeam(innerMostNode,trackingDirection)) return n;
  return 0;
}

StiKalmanTrackNode * StiKalmanTrack::extrapolateToRadius(double radius)
{
  StiKalmanTrackNode * outerMostNode = getOuterMostNode();
  //return null if there is no node to extrapolate from.
  if (!outerMostNode) return 0;
  StiKalmanTrackNode * n = trackNodeFactory->getInstance();
  if (n->propagateToRadius(outerMostNode,radius,trackingDirection)>=0) return n;
  return 0;
}
