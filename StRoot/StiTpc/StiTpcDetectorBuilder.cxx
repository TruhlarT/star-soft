#include <stdio.h>
#include <stdexcept>
#include "StDbUtilities/StTpcLocalCoordinate.hh"
#include "StDbUtilities/StTpcCoordinateTransform.hh"
#include "StTpcDb/StTpcDb.h"
#include "StTpcDb/StTpcPadPlaneI.h"
#include "StTpcDb/StTpcDimensionsI.h"
#include "Sti/StiPlanarShape.h"
#include "Sti/StiCylindricalShape.h"
#include "Sti/StiMaterial.h"
#include "Sti/StiPlacement.h"
#include "Sti/StiDetector.h"
#include "Sti/Base/Factory.h"
#include "Sti/StiToolkit.h"
#include "Sti/StiIsActiveFunctor.h"
#include "Sti/StiNeverActiveFunctor.h"
#include "Sti/Base/Messenger.h"
#include "Sti/StiHitErrorCalculator.h"
#include "StiTpcDetectorBuilder.h" 
#include "StiTpcIsActiveFunctor.h"

StiTpcDetectorBuilder::StiTpcDetectorBuilder(bool active)
  : StiDetectorBuilder("TpcBuilder",active)
{
  _innerCalc = new StiDefaultHitErrorCalculator();
  _innerCalc->set(.066, 1.2e-04, 0.0004,
		  .03, 2.2e-4, 2.8-02);
  _outerCalc = new StiDefaultHitErrorCalculator();
  _outerCalc->set(.015, 8e-04, 0.0004,
		  .012, 1.6e-4, 1.3e-01);
  StiTrackingParameters * trackingPars = getTrackingParameters();
  trackingPars->setMaxChi2ForSelection(10.);
  trackingPars->setMinSearchWindow(1.5);
  trackingPars->setMaxSearchWindow(7.);
  trackingPars->setSearchWindowScaling(10.);
}

StiTpcDetectorBuilder::~StiTpcDetectorBuilder()
{
  delete _innerCalc;
  delete _outerCalc;
}

/*! Builds the material required for the TPC
<p>
The material currently used are P10, and NOMEX. The properties
of these materials are extracted from the Particle Data Book.
*/  
void StiTpcDetectorBuilder::buildMaterials()
{
  _messenger << "StiTpcDetectorBuilder::buildMaterials() - INFO - Started" << endl;
  _gas        = add(new StiMaterial("P10",   16.4,  36.2741, 0.00156,  12820.*0.00156, 15.48) ); 
  _fcMaterial = add(new StiMaterial("Nomex",  6.24, 12.40,   0.064,       39.984,  1.)        );
  _messenger << "StiTpcDetectorBuilder::buildMaterials() - INFO - Done" << endl;
}

void StiTpcDetectorBuilder::buildShapes()
{
  _messenger << "StiTpcDetectorBuilder::buildShapes() - INFO - Started/Done" << endl;
}

/*! Build all detector components of the TPC.
<p>
The detector components of the TPC include the 24 sectors, 45 padrow gas volumes, and
the inner and outer field cage of the TPC. The padrows  are polygonal with 12  sides
whereas  the field cage are cylindrical. However to match the 12 fold symmetry of the 
TPC, the field cage are artificially segmented into 12 sectors each.
*/
  void StiTpcDetectorBuilder::buildDetectors()
{
  char name[50];
  _messenger << "StiTpcDetectorBuilder::buildDetectors() - INFO - Started" << endl;
  unsigned int row;

  // Inner field cage
  StiCylindricalShape *ifcShape = new StiCylindricalShape;
  ifcShape->setName("tpc/ifc");
  ifcShape->setThickness(1.27); 
  ifcShape->setHalfDepth( _dimensions->tpcTotalLength()/2. );
  ifcShape->setOpeningAngle( M_PI/6. );
  ifcShape->setOuterRadius(_dimensions->ifcRadius() + ifcShape->getThickness()/2.);

  //Outer  field cage
  StiCylindricalShape *ofcShape = new StiCylindricalShape;
  ofcShape->setName("tpc/ofc");
  ofcShape->setThickness(1.27); 
  ofcShape->setHalfDepth( _dimensions->tpcTotalLength()/2. );
  ofcShape->setOpeningAngle( M_PI/6. );
  ofcShape->setOuterRadius(_dimensions->ofcRadius() + ofcShape->getThickness()/2.);
  if (!ifcShape || !ofcShape)
    throw runtime_error("StiTpcDetectorBuilder::buildDetectors() - FATAL - ifcShape==0||ofcShape==0");
  float fIfcRadius = _dimensions->ifcRadius();   
  float fOfcRadius = _dimensions->ofcRadius();   

  StiPlacement *p;
  //for(unsigned int sector = 0; sector<getNSectors(); sector++) 
  for(unsigned int sector = 0; sector<12; sector++)
    {
      // inner field cage
      p = new StiPlacement;
      p->setZcenter(0.);
      p->setLayerRadius(fIfcRadius);
      p->setNormalRep(phiForTpcSector(sector), fIfcRadius, 0.);
      p->setRegion(StiPlacement::kMidRapidity);
      
      StiDetector *ifcVolume = _detectorFactory->getInstance();
      sprintf(name, "TPC/Ifc/Sector_%d", sector);
      ifcVolume->setName(name);
      ifcVolume->setIsOn(true);
      ifcVolume->setIsActive(new StiNeverActiveFunctor);
      ifcVolume->setIsContinuousMedium(false);
      ifcVolume->setIsDiscreteScatterer(true);
      ifcVolume->setShape(ifcShape);
      ifcVolume->setPlacement(p);
      ifcVolume->setGas(_gas);
      ifcVolume->setMaterial(_fcMaterial);
      add(ifcVolume);
      
      // outer field cage
      p = new StiPlacement;
      p->setZcenter(0.);
      p->setLayerRadius(fOfcRadius);
      p->setNormalRep(phiForTpcSector(sector), fOfcRadius, 0.);
      p->setRegion(StiPlacement::kMidRapidity);      

      
      StiDetector *ofcVolume = _detectorFactory->getInstance();
      sprintf(name, "TPC/Ofc/Sector_%d", sector);
      ofcVolume->setName(name);
      ofcVolume->setIsOn(true);
      ofcVolume->setIsActive(new StiNeverActiveFunctor);
      ofcVolume->setIsContinuousMedium(false);
      ofcVolume->setIsDiscreteScatterer(true);
      ofcVolume->setShape(ofcShape);
      ofcVolume->setPlacement(p);
      ofcVolume->setGas(_gas);
      ofcVolume->setMaterial(_fcMaterial);
      // remove it for now...
      //add(ofcVolume);
  } 
  StiPlanarShape *pShape;
  //Active TPC padrows 
  unsigned int _nInnerPadrows = _padPlane->numberOfInnerRows();
  for(row = 0; row<getNRows(); row++)
    {
      // create properties shared by all sectors in this padrow
      float fRadius = _padPlane->radialDistanceAtRow(row+1);
      sprintf(name, "Tpc/Padrow_%d", row);
      pShape = new StiPlanarShape;
      if (!pShape)
	throw runtime_error("StiTpcDetectorBuilder::buildDetectors() - FATAL - pShape==0||ofcShape==0");
      if(row<_nInnerPadrows)
	pShape->setThickness(_padPlane->innerSectorPadLength());
      else
	pShape->setThickness(_padPlane->outerSectorPadLength());
      pShape->setHalfDepth(_dimensions->tpcTotalLength()/2.);
      pShape->setHalfWidth(_padPlane->PadPitchAtRow(row+1) *
			   _padPlane->numberOfPadsAtRow(row+1) / 2.);
      pShape->setName(name);
      for(unsigned int sector = 0; sector<getNSectors(); sector++)
	{
	  // create unique detector properties (placement & name)
	  StiPlacement *pPlacement = new StiPlacement;
	  pPlacement->setZcenter(0.);
	  pPlacement->setNormalRep(phiForTpcSector(sector), fRadius, 0.); 
	  pPlacement->setLayerRadius(fRadius);
	  pPlacement->setRegion(StiPlacement::kMidRapidity);
	  sprintf(name, "Tpc/Padrow_%d/Sector_%d", row, sector);
	  // fill in the detector object and save it in our vector
	  StiDetector *pDetector = _detectorFactory->getInstance();
	  pDetector->setName(name);
	  pDetector->setIsOn(true);
	  if (_active)
	    pDetector->setIsActive(new StiTpcIsActiveFunctor(sector, row));
	  else
	    pDetector->setIsActive(new StiNeverActiveFunctor());
	  pDetector->setIsContinuousMedium(true);
	  pDetector->setIsDiscreteScatterer(false);
	  pDetector->setMaterial(_gas);
	  pDetector->setGas(_gas);
	  pDetector->setShape(pShape);
	  pDetector->setPlacement(pPlacement);
	  if (row<15)
	    pDetector->setHitErrorCalculator(_innerCalc);
	  else
	    pDetector->setHitErrorCalculator(_outerCalc);
	  add(row,sector,pDetector);
	}// for sector
    }// for row

  _messenger << "StiTpcDetectorBuilder::buildDetectors() - INFO - Done" << endl;
}

void StiTpcDetectorBuilder::loadDb()
{
  if (!gStTpcDb) 
		throw runtime_error("StiTpcDetectorBuilder::buildShapes() - ERROR - gStTpcDb==0");
	_padPlane = gStTpcDb->PadPlaneGeometry();
  if (!_padPlane) 
		throw runtime_error("StiTpcDetectorBuilder::buildShapes() - ERROR - _padPlane==0");
	_dimensions = gStTpcDb->Dimensions();
  if (!_dimensions)
		throw runtime_error("StiTpcDetectorBuilder::loadDb() - ERROR - _dimensions==0");
  _transform = new StTpcCoordinateTransform(gStTpcDb);
  if (!_transform)
    throw runtime_error("StiTpcDetectorBuilder::loadDb() - ERROR - gStTpcDb==0");
  StTpcPadPlaneI *_padPlane = gStTpcDb->PadPlaneGeometry();
  if (!_padPlane)
    throw runtime_error("StiTpcDetectorBuilder::loadDb() - ERROR - _padPlane==0");
  unsigned int nRows = _padPlane->numberOfRows();
  setNRows(nRows);
  for(unsigned int row = 0; row<nRows;row++)
    {
      setNSectors(row,12);
    }
}


