//StiDetector.cxx

//STD
#include <math.h>
#include <iostream>
#include <string>
#include <map>
//SCL
#include "StGetConfigValue.hh"
//Sti
#include "StiMaterial.h"
#include "StiShape.h"
#include "StiPlacement.h"
#include "StiDetectorContainer.h"
#include "StiDetector.h"
#include "StiMapUtilities.h"
#include "StiIsActiveFunctor.h"

StiDetector::StiDetector() : gas(0), material(0), shape(0), placement(0), mNode(0)
{
}

StiDetector::~StiDetector()
{
}

bool StiDetector::isActive(double dYlocal, double dZlocal) const{
  return (*isActiveFunctor)(dYlocal, dZlocal);
} // isActive

bool StiDetector::isActive() const {
  return isActive(placement->getNormalYoffset(), placement->getZcenter());
} // isActive

void StiDetector::copy(StiDetector &detector){

  on = detector.isOn();
  isActiveFunctor = detector.isActiveFunctor;
  continuousMedium = detector.isContinuousMedium();
  discreteScatterer = detector.isDiscreteScatterer();

  gas = detector.getGas();
  material = detector.getMaterial();
  shape = detector.getShape();
  placement = detector.getPlacement();

  setName(detector.getName());
}
 
ostream& operator<<(ostream& os, const StiDetector& d){

    os << d.getName()
       <<"\tR:"<<d.getPlacement()->getCenterRadius()<<"cm\tA:"
       <<d.getPlacement()->getCenterRefAngle()<< " radians";
    return os;
    
} // operator<<

