//StiHitFiller.h
//M.L. Miller (Yale Software)
//04/01

//class to define interface between StEvent, StiHitContainer, and StiHitFactory (adaptor)

#ifndef StiHitFiller_HH
#define StiHitFiller_HH

#include <vector>
#include "../pams/global/inc/StDetectorId.h" //for detector enumerations

class ostream;
class StiHitContainer;
class StiHitFactory;
class StTpcCoordinateTransform;

class StiHitFiller
{
public:
    typedef vector<StDetectorId> det_id_vector;
    
    StiHitFiller();
    virtual ~StiHitFiller();

    void addDetector(StDetectorId det);
    void fillHits(StiHitContainer*, StiHitFactory*) const;

    friend ostream& operator<<(ostream&, const StiHitFiller&);

private:
    void fillTpcHits(StiHitContainer*, StiHitFactory*) const;
    void fillSvtHits(StiHitContainer*, StiHitFactory*) const;
    
private:
    StTpcCoordinateTransform* mtransformer;
    det_id_vector mvec;
    
};

ostream& operator<<(ostream&, const StiHitFiller&);

#endif
