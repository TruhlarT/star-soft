/*****************************************************************************
 *
 * $Id: EEmcSmdGeom.h,v 1.1 2004/01/29 15:26:10 jwebb Exp $
 *
 * Author: Wei-Ming Zhang
 * 
 * Revisions:
 *
 * 01/28/04 Jason Webb -- Renamed to EEmcSmdGeom, StRoot dependent code moved 
 * to a derived class StEEmcSmdGeom.  The user interface for StEEmcSmdGeom
 * should remain unchanged.  Revision history for StEEmcSmdGeom moved  to end
 * of header file.  
 *
 *****************************************************************************
 *
 * Description: Interface to EEMC-SMD database
 * 
 * The following demensions are defined for SMD in EEmcGeomDefs.h
 * EEmcNumSectors     = 12 (The order follows numbering scheme of TPC sectors)
 * kEEmcNumSmdPlanes  =  3 (1: the innermost and 3: the outermost) 
 * kEEmcNumStrips     =288 (1: the shortes inner and 288: the shortest outer) 
 * kEEmcNumEdgeStrips =283 (1: the shortes inner and 283: the shortest outer)
 * kEEmcNumSmdLayers  =  2 (1: U and 2: V) 
 *
 *****************************************************************************
 *
 * $Log: EEmcSmdGeom.h,v $
 * Revision 1.1  2004/01/29 15:26:10  jwebb
 * The StEEmcSmdGeom class was split into two classes.  All StRoot-independent
 * code has been moved to EEmcSmdGeom.  TVector3 replaces StThreeVectorD in
 * all function calls in EEmcSmdGeom.  StThreeVectorD wrappers are provided
 * in StEEmcSmdGeom, for integration into Star framework.
 *
 *
 *****************************************************************************/

#ifndef EEMCSMDGEOM_H
#define EEMCSMDGEOM_H

#include <iostream>

#include "TObject.h"
#include "TVector3.h"


#include "StEEmcUtil/EEmcGeom/EEmcGeomDefs.h"

#include <vector>
#ifndef ST_NO_NAMESPACES
using std::vector;
using std::cout;
#endif

struct StructEEmcSmdParam {
  float zPlane[kEEmcNumSmdPlanes];  // Z of planes
  float rOffset[kEEmcNumSmdPlanes]; // radius offsets
  float stripWidth;                 // width of strip
};

struct StructEEmcStripId{
  int  stripId;                     // strip Id  1-288 (283 for edge sector)
  int  UVId;                        // 1 for U and 2 for V
  int  sectorId;                    // sector Id 1-12 
  int  planeId;                     // plane Id (depth) 1-3
};

struct StructEEmcStrip{
  StructEEmcStripId stripStructId; // including 4 Ids
  TVector3    end1;          // one end of strip         
  TVector3    end2;          // the other end of strip
  float length;                    // length of strip 
};

// Define vector of strip pointers and its Iterator
#ifndef ST_NO_TEMPLATE_DEF_ARGS
typedef vector<int> intVec;  
typedef vector<StructEEmcStrip*> EEmcStripPtrVec;  
#else
typedef vector<int,allocator<int>> intVec; 
typedef vector<StructEEmcStrip*,allocator<StructEEmcStrip*>> EEmcStripPtrVec; 
#endif   
typedef vector<StructEEmcStrip*>::iterator EEmcStripPtrVecIter; 


struct StructEEmcSmdSector {
  int   sectorId;	
  int   planeId;        
  float phiMin;    // minimun phi
  float phiMax;    // maximum phi
  float rMin;      // minimum radius
  float rMax;      // maximum radius
  EEmcStripPtrVec stripPtrVec;  
};

class EEmcSmdGeom : public TObject {

 public:  

  EEmcSmdGeom();
  virtual ~EEmcSmdGeom(); 

 protected:

  StructEEmcSmdParam     mEEmcSmdParam;  //! general geometry variables
  StructEEmcSmdSector    mEEmcSector[kEEmcNumSmdUVs][kEEmcNumSectors]; //! storage for 2*12 sectors    
  //StructEEmcStrip*       mStripPtrVector[kEEmcNumStrips*kEEmcNumSmdUVs*kEEmcNumSectors]; //! storage for all strip pointers  
  EEmcStripPtrVec       mStripPtrVector; //! storage for all strip pointers  
  bool                   mIsSectorIn[kEEmcNumSectors];    //! sector status. 

  void buildSmdGeom();
  static EEmcSmdGeom* sInstance;

 public:

  static EEmcSmdGeom* instance();   // handle the only instance
  static EEmcSmdGeom* instance(intVec sectorIdVec);   

  void init();         // init the dbase

  // build mStripPtrVector   
  void buildStripPtrVector();

  // set sectors for partial EEMC
  void setSectors(const intVec sectorIdVec); 
  
  // return sector status   
  bool IsSectorIn(const Int_t iSec) const; 
  
  // instance and initialize a strip 
  StructEEmcStrip initStrip();

  //
  // geometry access members
  //

  // return SMD geometry parameters  
  StructEEmcSmdParam getEEmcSmdParam() const; 

  // return structure-sector from iUV and iSec 
  StructEEmcSmdSector getEEmcSector(const Int_t iUV, const Int_t iSec) const;

  // return index of a sector from a point in a plane 
  Int_t getEEmcISec(const Int_t iPlane, const TVector3& point) const;
  
  // return a strip pointer from indices   
  StructEEmcStrip* getStripPtr(const Int_t iStrip, const Int_t iUV, const Int_t iSec);

  // return a DCA strip pointer from a point (float *dca carries sign)  
  StructEEmcStrip* getDcaStripPtr(const Int_t iPlane, const TVector3& point, Float_t* dca);
  StructEEmcStrip* getDcaStripPtr(const Int_t iPlane, const Int_t iSec, const TVector3& point, Float_t* dca);
  
  /////////////////////////////////////////////////////////////////////////////
  //
  // Given two strips (alternatively sector and strip Id's), return a 
  //   vector pointing to the center of the trapezoid formed by their
  //   crossing.  These functions may return non-physical locations,
  //   for instance, when a U,V pair does not cross within the 
  //   fiducial area of the detector.  Note: the z-component returned
  //   will be the average z of the U and V detector planes.
  //
  TVector3 getIntersection ( Int_t iSec, Int_t iUStrip, Int_t iVStrip );
  TVector3 getIntersection ( StructEEmcStrip *u, StructEEmcStrip *v );
  // 
  // Return the number of strips for the specified orientation for this
  //   sector
  //
  Int_t getNStrips ( Int_t iSec, Int_t iUV ) { return getEEmcSector(iUV,iSec).stripPtrVec.size();  }
  //
  /////////////////////////////////////////////////////////////////////////////

  // match two strips 
  bool matchStrips(const StructEEmcStripId stripStructId1, const StructEEmcStripId stripStructId2, Int_t nTolerance);


  // Will need to move to StRoot-enabled version
#if 0
  //
  // three methods for ITTF
  //

  // return phiMin and phiMax of a sector including empty sector 
  pairD getEEmcSmdPhiMinMax(const Int_t iPlane, const Int_t iSec);
  // return delta_phi of a sector including empty sector 
  float getEEmcSmdDelPhi(const Int_t iPlane, const Int_t iSec);
  // return center phi of a sector including empty sector 
  float getEEmcSmdCenterPhi(const Int_t iPlane, const Int_t iSec);
#endif

  // mehtod for C-scripts

  // return strip-end of 3D-vector   
  TVector3  getstripEnd(const StructEEmcStrip strip, const Int_t endId);

  //
  // methods of printout 
  //

  void printGeom(ostream& os = cout) const;
  void printSector(const StructEEmcSmdSector Sector, ostream& os = cout) const;
  void printStrip(const StructEEmcStrip Strip, ostream& os = cout) const;
  void printStripId(const StructEEmcStripId StripId, ostream& os = cout) const;
  //void printSectorPhis(const Int_t iPlane, const Int_t iSec,ostream& os = cout);

  
 protected:  

  ClassDef(EEmcSmdGeom,1)  // STAR Endcap Electromagnetic Calorimeter SMD Geometry Class

};

inline bool EEmcSmdGeom::IsSectorIn(Int_t iSec)
       const {return mIsSectorIn[iSec];}
inline StructEEmcSmdParam EEmcSmdGeom::getEEmcSmdParam()
       const {return mEEmcSmdParam;}
inline StructEEmcSmdSector EEmcSmdGeom::getEEmcSector(const Int_t iUV, 
	   	                                        const Int_t iSec) 
       const {return mEEmcSector[iUV][iSec];}

#endif
 
/*******************************************************************
 *
 * Id: StEEmcSmdGeom.h,v 1.6 2003/12/05 00:06:11 jwebb Exp 
 *
 * Author: Wei-Ming Zhang
 *****************************************************************
 *
 * Description: Interface to EEMC-SMD database
 * 
 * The following demensions are defined for SMD in EEmcGeomDefs.h
 * EEmcNumSectors     = 12 (The order follows numbering scheme of TPC sectors)
 * kEEmcNumSmdPlanes  =  3 (1: the innermost and 3: the outermost) 
 * kEEmcNumStrips     =288 (1: the shortes inner and 288: the shortest outer) 
 * kEEmcNumEdgeStrips =283 (1: the shortes inner and 283: the shortest outer)
 * kEEmcNumSmdLayers  =  2 (1: U and 2: V) 
 *
 *****************************************************************
 *
 * Log: StEEmcSmdGeom.h,v 
 * Revision 1.6  2003/12/05 00:06:11  jwebb
 * Member function added to return a vector pointing to the intersection of
 * two strips.
 *
 * Revision 1.5  2003/10/15 15:26:03  wzhang
 * improved and reorganized
 *
 * Revision 1.4  2003/08/22 15:14:03  wzhang
 * Added ClassDef and method stripEnd
 *
 * Revision 1.3  2003/06/11 18:58:15  wzhang
 * added geometry methods for StiEEmc
 *
 * Revision 1.2  2003/04/04 15:33:31  wzhang
 * included EEmcGeomDefs.h & improved codes
 *
 * Revision 1.1  2003/03/28 15:50:00  balewski
 * first
 *
 *
 ****************************************************************/
