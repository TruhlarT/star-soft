/*
 This file is part of the VRender library.
 Copyright (C) 2005 Cyril Soler (Cyril.Soler@imag.fr)
 Version 1.0.0, released on June 27, 2005.

 http://artis.imag.fr/Members/Cyril.Soler/VRender

 VRender is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 VRender is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with VRender; if not, write to the Free Software Foundation, Inc.,
 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

/****************************************************************************

 This file is part of the QGLViewer library.
 Copyright (C) 2002, 2003, 2004, 2005, 2006 Gilles Debunne (Gilles.Debunne@imag.fr)
 Version 2.2.1-1, released on March 30, 2006.

 http://artis.imag.fr/Members/Gilles.Debunne/QGLViewer

 libQGLViewer is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 libQGLViewer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with libQGLViewer; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/

#ifndef _PRIMITIVEPOSITIONING_H
#define _PRIMITIVEPOSITIONING_H

#include <vector>
#include "gpc.h"

namespace vrender
{
	class Primitive ;

	// This class implements a static method for positioning two primitives relative to each other.

	class PrimitivePositioning
	{
		public:
			typedef enum { Independent = 0x0,
								Upper 		= 0x1,
								Lower 		= 0x2 } RelativePosition ;

			static int computeRelativePosition(const Primitive *p1,const Primitive *p2) ;

			static void splitPrimitive(Primitive *P,const NVector3& v,double c,Primitive *& prim_up,Primitive *& prim_lo) ;

			static void split(Segment *S,	const NVector3& v,double C,Primitive * & P_plus,Primitive * & P_moins) ;
			static void split(Point *P,	const NVector3& v,double C,Primitive * & P_plus,Primitive * & P_moins) ;
			static void split(Polygone *P,const NVector3& v,double C,Primitive * & P_plus,Primitive * & P_moins) ;

		private:
			static void getsigns(const Primitive *P,const NVector3& v,
										double C,std::vector<int>& signs,std::vector<double>& zvals,
										int& Smin,int& Smax,double I_EPS) ;

			static int computeRelativePosition(const Polygone  *p1,const Polygone  *p2) ;
			static int computeRelativePosition(const Polygone  *p1,const Segment   *p2) ;
			static int computeRelativePosition(const Polygone  *p1,const Point     *p2) ;
			static int computeRelativePosition(const Segment   *p1,const Segment   *p2) ;

			//  2D intersection/positioning methods. Parameter I_EPS may be positive of negative
			// depending on the wanted degree of conservativeness of the result.

			static bool pointOutOfPolygon_XY(const Vector3&  P,const Polygone *Q,double I_EPS) ;
			static bool intersectSegments_XY(const Vector2& P1,const Vector2& Q1,
														const Vector2& P2,const Vector2& Q2,
														double I_EPS,double & t1,double & t2) ;
			static gpc_polygon createGPCPolygon_XY(const Polygone *P) ;


			static int inverseRP(int) ;

			//  This value is *non negative*. It may be used with a negative sign
			// in 2D methods such as pointOutOfPolygon() so as to rule the behaviour of
			// the positionning.

			static double _EPS ;
	};
}

#endif
