#ifndef __StvFtsHitErrCalculatorulator_h_
#define __StvFtsHitErrCalculatorulator_h_
#include "StvUtil/StvHitErrCalculator.h"
class StvHit;

class StvFtsHitErrCalculator : public StvHitErrCalculator {

public:	
  StvFtsHitErrCalculator(const char *name="FtsHitErr"):StvHitErrCalculator(name,2){};
int CalcDcaErrs(const StvHit* hit,double hRR[3]);
int CalcDetErrs(const float hiPos[3],const float hiDir[3][3],double hRR[3]);
int CalcDcaErrs(const float hiPos[3],const float hiDir[3][3],double hRR[3])
   {return StvHitErrCalculator::CalcDcaErrs(hiPos,hiDir,hRR);}

protected:
enum {
kYErr  	=0, 	/* Intrinsic resolution, padrow or Y direction		*/
kZErr  	=1}; 	/* Intrinsic resolution, z direction			*/

static double mgRPhiErrs[2]; 	//these errors are used only for CalcDetErrs
				//when the concrete hit is not defined


ClassDef(StvFtsHitErrCalculator,0)
};

#endif
