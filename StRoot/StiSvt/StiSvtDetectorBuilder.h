#ifndef StiSvtDetectorBuilder_H
#define StiSvtDetectorBuilder_H
#include "StSvtClassLibrary/StSvtConfig.hh"
#include "StSvtClassLibrary/StSvtGeometry.hh"
#include "StThreeVector.hh"
#include "Sti/StiDetectorBuilder.h"
#include "Sti/StiHitErrorCalculator.h"

class StiSvtDetectorBuilder : public StiDetectorBuilder
{
 public:
	StiSvtDetectorBuilder(bool active, const string & inputFile);
	virtual ~StiSvtDetectorBuilder(); 
	virtual void loadDS(TDataSet&);
	virtual void loadFS(ifstream& inFile);

	virtual void buildDetectors(StMaker& source);	
	virtual void setDefaults();
	virtual void useVMCGeometry();		
	void    setSiMat(StiMaterial     *m) {_siMat = m;}
	void    setHybridMat(StiMaterial *m) {_hybridMat = m;}
	StiMaterial *getSiMat()    {return _siMat;}
	StiMaterial *getHybridMat(){return _hybridMat;}
	static void setDebug(int m = 0) {_debug = m;}
	static int  debug() {return _debug;}
 protected:
	StiMaterial    * _siMat;
	StiMaterial    * _hybridMat;
	StiPlanarShape * _waferShape[6];
	StiPlanarShape * _hybridShape[6];
	StSvtConfig    * _config;
	StSvtGeometry  * _geometry;
	StiDefaultHitErrorCalculator  _calc;
	static int       _debug;
};
#endif 
