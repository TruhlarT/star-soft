#ifndef StiDedxCalculator_H
#define StiDedxCalculator_H 1

#include <iostream.h>
#include <stdlib.h>

class StiDedxCalculator 
{
  // Helper class used to perform the calculation of a truncated 
  // dedx average using low and high cuts on the samples.


 public:

  StiDedxCalculator();
  virtual ~StiDedxCalculator(){};
  
  void  setRange(float min, float max)  { low = min; high = max; };
  
  virtual void  setDefaults();
  virtual float getDedx(int nSample, float * samples);

 protected:

  double low;
  double high;
};

#endif
