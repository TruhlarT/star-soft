#ifndef StiFactory_H
#define StiFactory_H 
#include <string.h>
#include <assert.h>
#include <typeinfo>
#include "Sti/Base/Factory.h"
/*!
  Abstract base class defining a  factory mechanism
  <p>
  This class defines the concept of factory, an agent responsible for the
  creation or instantiation of a given type of class. The class is templated.
  The template represents the base class to be intanstiated and served by the
  factory. Implementation (derived class) may serve objects from class derived
  based on the "Factorized" template class.
*/


//______________________________________________________________________________
template<class Object>
class StiHolder  {
public:
	StiHolder();
union {
  StiHolder *fNext;
  long       fLong;
};
 Object fObj;
};

//______________________________________________________________________________
template<class Object>
class StiBlock {
public:
enum {kSize=100};
     StiBlock(StiBlock **bTop,StiHolder<Object> **hTop);
void reset(StiBlock **bTop,StiHolder<Object> **hTop);
int getSize() const {return kSize;}

StiBlock *fNext;
StiHolder<Object> fArr[kSize];
};


//______________________________________________________________________________
template <class Concrete, class Abstract>
class StiFactory : public Factory<Abstract>
{
public:
void   free(Abstract *obj);  
void   free(void *obj) { free((Abstract*)obj);}
  ///Clear/delete all objects owned by this factory
void clear();  

  ///Reset this factory
void reset();

  ///Get a pointer to instance of objects served by this factory.
Abstract* getInstance();
static StiFactory*  myInstance();

private:
   StiFactory();
  ~StiFactory(){clear();}
StiBlock<Concrete>  *fBTop;
StiHolder<Concrete> *fHTop;

};
//______________________________________________________________________________
//______________________________________________________________________________
//______________________________________________________________________________
template <class Object>
StiBlock<Object>::StiBlock(StiBlock **bTop,StiHolder<Object> **hTop)
{
  reset(bTop,hTop);
}
template <class Object>
void StiBlock<Object>::reset(StiBlock **bTop,StiHolder<Object> **hTop)
{
  fNext=*bTop; *bTop=this;
  for (int i=0;i<kSize;i++) {
    fArr[i].fNext = *hTop;
   *hTop = fArr+i;
  }
}
//______________________________________________________________________________
//______________________________________________________________________________
template <class Object>
StiHolder<Object>::StiHolder()
{
  int n = (char*)&fObj -(char*)&fNext;
  memset(&fNext,0,n);
}
//______________________________________________________________________________
//______________________________________________________________________________
template <class Concrete, class Abstract>
StiFactory<Concrete,Abstract>::StiFactory():Factory<Abstract>("")
{
  fHTop=0;fBTop=0;
  setName(typeid(*this).name());
  printf("*** Factory created *** %s\n",getName().c_str());
}
template <class Concrete, class Abstract>
StiFactory<Concrete,Abstract>* StiFactory<Concrete,Abstract>::myInstance() 
{
   static StiFactory* my=0;
   if (!my) my = new StiFactory;
   return my;
}
//______________________________________________________________________________
template <class Concrete, class Abstract>
Abstract *StiFactory<Concrete,Abstract>::getInstance() 
{
  if (!fHTop)  {
    assert(fCurCount < fMaxCount);  
    new StiBlock<Concrete>(&fBTop,&fHTop);
    fCurCount += fBTop->getSize();
  }
  StiHolder<Concrete> *h = fHTop;
  fHTop = h->fNext;
  h->fNext=0;
  h->fObj.reset();
  fUseCount++;
  h->fLong= ((long)this)+1;		//set factory addres+1
  return &h->fObj;  
}  
//______________________________________________________________________________
template <class Concrete, class Abstract>
void StiFactory<Concrete,Abstract>::free(Abstract *obj)
{
  static const int shift = (char*)(&(((StiHolder<Concrete>*)1)->fObj))-(char*)1;
  StiHolder<Concrete>* h = (StiHolder<Concrete>*)((char*)obj-shift);
  assert((h->fLong-1)== (long)this);
  h->fNext = fHTop; fHTop=h; fUseCount--;
}

//______________________________________________________________________________
template <class Concrete, class Abstract>
void StiFactory<Concrete,Abstract>::clear()
{
  double sz=0;
  StiBlock<Concrete>* b = fBTop;
  while (b) {
    StiBlock<Concrete>* d = b;
    b=b->fNext;  delete d;
    sz += sizeof(StiBlock<Concrete>);
  }
  fBTop=0; fHTop=0; fCurCount=0; fUseCount=0;
  printf("*** %s::clear() %g MegaBytes \n",getName().c_str(),sz*1e-6);
}
//______________________________________________________________________________
template <class Concrete, class Abstract>
void StiFactory<Concrete,Abstract>::reset()
{
  if (!fUseCount) return;
  
  typedef StiBlock<Concrete> B_t;
  B_t* b = fBTop;
  fBTop=0;fHTop=0;
  while (b) {
    B_t* n = b->fNext;
    b->reset(&fBTop,&fHTop);
    b=n;
  }
  fUseCount=0;
}
#endif
