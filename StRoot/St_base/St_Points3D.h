#ifndef ROOT_St_Points3D
#define ROOT_St_Points3D
// $Id: St_Points3D.h,v 1.5 1999/12/17 23:28:40 fine Exp $ 
// ***********************************************************************
// *  C++ class to define the abstract array of 3D points
// * Copyright(c) 1997~1999  [BNL] Brookhaven National Laboratory, STAR, All rights reserved
// * Author                  Valerie Fine  (fine@bnl.gov)
// * Copyright(c) 1997~1999  Valerie Fine  (fine@bnl.gov)
// *
// * This program is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// *
// * Permission to use, copy, modify and distribute this software and its
// * documentation for any purpose is hereby granted without fee,
// * provided that the above copyright notice appear in all copies and
// * that both that copyright notice and this permission notice appear
// * in supporting documentation.  Brookhaven National Laboratory makes no
// * representations about the suitability of this software for any
// * purpose.  It is provided "as is" without express or implied warranty.
// ************************************************************************

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// St_Points3D                                                          //
//                                                                      //
// A 3-D PolyLine.                                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOT_TPoints3DABC
#include "TPoints3DABC.h"
#endif


class St_Points3D : public TPoints3DABC {

protected:
         enum EOwnerBits {
           kIsOwner         = BIT(23)
         };

        TPoints3DABC *fPoints;

        Bool_t IsOwner() const {return TestBit(kIsOwner);}
        Bool_t DoOwner(Bool_t done=kTRUE);

public:
        St_Points3D(TPoints3DABC *points=0);
        St_Points3D(Int_t n, Option_t *option="");
        St_Points3D(Int_t n, Float_t *p, Option_t *option="");
        St_Points3D(Int_t n, Float_t *x, Float_t *y, Float_t *z, Option_t *option="");
        St_Points3D(const St_Points3D &points);
        virtual ~St_Points3D();

        virtual void      Copy(TObject &points);
        virtual void      Delete();
        virtual Int_t     DistancetoPrimitive(Int_t px, Int_t py);
        virtual void      ExecuteEvent(Int_t event, Int_t px, Int_t py);
        virtual Int_t     GetLastPosition()       const;
        virtual Int_t     GetN() const;
        virtual Float_t  *GetP() const;
        virtual Float_t   GetX(Int_t idx)  const;
        virtual Float_t   GetY(Int_t idx)  const;
        virtual Float_t   GetZ(Int_t idx)  const;
        virtual Float_t  *GetXYZ(Float_t *xyz,Int_t idx,Int_t num=1)  const;
        virtual const Float_t  *GetXYZ(Int_t idx);
        virtual Option_t *GetOption() const ;
#ifndef __CINT__
#if ROOT_VERSION_CODE < ROOT_VERSION(2,23,4)
        virtual Bool_t    Is3D();
#endif
#endif
        virtual void      ls(Option_t *option="");
        virtual void      PaintPoints(Int_t n, Float_t *p,Option_t *option=""){;}
        virtual void      Print(Option_t *option="");
        virtual Int_t     SetLastPosition(Int_t idx);
        virtual void      SetOption(Option_t *option="");
        virtual Int_t     SetPoint(Int_t point, Float_t x, Float_t y, Float_t z); // *MENU*
        virtual Int_t     SetPoints(Int_t n, Float_t *p=0, Option_t *option="");
        virtual Int_t     Size() const;

        ClassDef(St_Points3D,1)  // Defines the abstract array of 3D points
};

inline Int_t     St_Points3D::DistancetoPrimitive(Int_t px, Int_t py) {return fPoints?fPoints->DistancetoPrimitive(px,py):99999;}
inline Int_t     St_Points3D::GetLastPosition()  const   {return fPoints?fPoints->GetLastPosition():0;}
inline Int_t     St_Points3D::GetN()  const              {return fPoints?fPoints->GetN():0;}
inline Float_t  *St_Points3D::GetP()  const              {return fPoints?fPoints->GetP():0;}
inline Float_t   St_Points3D::GetX(Int_t idx)  const     {return fPoints?fPoints->GetX(idx):0;}
inline Float_t   St_Points3D::GetY(Int_t idx)  const     {return fPoints?fPoints->GetY(idx):0;}
inline Float_t   St_Points3D::GetZ(Int_t idx)  const     {return fPoints?fPoints->GetZ(idx):0;}
inline const Float_t  *St_Points3D::GetXYZ(Int_t idx)    {return fPoints?fPoints->GetXYZ(idx):0;}
inline Float_t  *St_Points3D::GetXYZ(Float_t *xyz,Int_t idx,Int_t num)  const
                          {return fPoints?fPoints->GetXYZ(xyz,idx,num):0;}
inline Option_t *St_Points3D::GetOption() const          {return fPoints?fPoints->GetOption():"";}
#ifndef __CINT__
#if ROOT_VERSION_CODE < ROOT_VERSION(2,23,4)
inline Bool_t    St_Points3D::Is3D()                     {return fPoints?fPoints->Is3D():kFALSE;}
#endif
#endif
inline Int_t     St_Points3D::SetLastPosition(Int_t idx) {return fPoints?fPoints->SetLastPosition(idx):0;}
inline void      St_Points3D::SetOption(Option_t *option){if (fPoints) fPoints->SetOption(option);}
inline Int_t     St_Points3D::SetPoint(Int_t point, Float_t x, Float_t y, Float_t z){return fPoints?fPoints->SetPoint(point,x,y,z):0;}
inline Int_t     St_Points3D::SetPoints(Int_t n, Float_t *p, Option_t *option){return fPoints?fPoints->SetPoints(n,p,option):0;}

inline Int_t     St_Points3D::Size() const               {return fPoints?fPoints->Size():0;}
#endif
