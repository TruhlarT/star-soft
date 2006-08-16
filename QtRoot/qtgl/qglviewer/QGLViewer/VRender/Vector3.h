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

#ifndef _VRENDER_VECTOR3_H
#define _VRENDER_VECTOR3_H

#include <stdexcept>

#ifndef FLT_MAX
# define FLT_MAX 9.99E20f
#endif

namespace vrender
{
  class NVector3;

	class Vector3
	{
		public:
			// ---------------------------------------------------------------------------
			//! @name Constant
			//@{
			static const Vector3 inf;
			//@}

			// ---------------------------------------------------------------------------
			//! @name Constructor(s) and destructor
			//@{
			Vector3 ();
			~Vector3 ();
			Vector3 (const Vector3&);
			Vector3 (const NVector3&);
			Vector3 (double, double, double);

			//@}

			// ---------------------------------------------------------------------------
			//! @name Access methods
			//@{
			inline double  x() const { return _xyz[0]; }
			inline double  y() const { return _xyz[1]; }
			inline double  z() const { return _xyz[2]; }
			inline void  setX(double r) { _xyz[0] = r; }
			inline void  setY(double r) { _xyz[1] = r; }
			inline void  setZ(double r) { _xyz[2] = r; }
			inline void  setXYZ (double x,double y,double z) { _xyz[0] = x; _xyz[1] = y; _xyz[2] = z; }
			//@}

			// ---------------------------------------------------------------------------
			//! @name Assignment
			//@{
			inline Vector3& operator= (const Vector3& u)  { _xyz[0] = u._xyz[0]; _xyz[1] = u._xyz[1]; _xyz[2] = u._xyz[2]; return *this; }
			Vector3& operator= (const NVector3& u);
			//@}

			// ---------------------------------------------------------------------------
			//! @name Comparisons
			//@{
			friend bool operator== (const Vector3&,const Vector3&);
			friend bool operator!= (const Vector3&,const Vector3&);
			//@}

			// ---------------------------------------------------------------------------
			//! @name Algebraic operations
			//@{
			inline Vector3& operator+= (const Vector3& v)
			{
				_xyz[0] += v._xyz[0];
				_xyz[1] += v._xyz[1];
				_xyz[2] += v._xyz[2];
				return *this;
			}

			inline Vector3& operator-= (const Vector3& v)
			{
				_xyz[0] -= v._xyz[0];
				_xyz[1] -= v._xyz[1];
				_xyz[2] -= v._xyz[2];
				return *this;
			}

			inline Vector3& operator*= (double f) { _xyz[0] *= f; _xyz[1] *= f; _xyz[2] *= f; return *this;}
			inline Vector3& operator/= (double f) { _xyz[0] /= f; _xyz[1] /= f; _xyz[2] /= f; return *this;}

			static Vector3 mini(const Vector3&,const Vector3&) ;
			static Vector3 maxi(const Vector3&,const Vector3&) ;

			Vector3& operator-= (const NVector3&);
			Vector3& operator+= (const NVector3&);

			friend Vector3 operator- (const Vector3& u) { return Vector3(-u[0], -u[1], -u[2]); }

			inline Vector3 operator+(const Vector3& u) const
			{
				return Vector3(_xyz[0]+u._xyz[0],_xyz[1]+u._xyz[1],_xyz[2]+u._xyz[2]);
			}
			inline Vector3 operator-(const Vector3& u) const
			{
				return Vector3(_xyz[0]-u._xyz[0],_xyz[1]-u._xyz[1],_xyz[2]-u._xyz[2]);
			}

			inline double    operator*(const Vector3& u) const
			{
				return _xyz[0]*u._xyz[0] + _xyz[1]*u._xyz[1] + _xyz[2]*u._xyz[2];
			}

			inline Vector3 operator^(const Vector3& v) const
			{
				return Vector3(	_xyz[1]*v._xyz[2] - _xyz[2]*v._xyz[1],
											_xyz[2]*v._xyz[0] - _xyz[0]*v._xyz[2],
											_xyz[0]*v._xyz[1] - _xyz[1]*v._xyz[0]);
			}

			Vector3 operator/ (double v) { return Vector3(_xyz[0]/v,_xyz[1]/v,_xyz[2]/v); }
			Vector3 operator* (double v) { return Vector3(_xyz[0]*v,_xyz[1]*v,_xyz[2]*v); }

			friend Vector3 operator* (double,const Vector3&);
			//@}

			// ---------------------------------------------------------------------------
			//! @name Metrics
			//@{
			double norm       () const;
			double squareNorm () const;
			double infNorm    () const; /// Should be used for most comparisons, for efficiency reasons.
			//@}
			// ---------------------------------------------------------------------------
			//! @name Stream overrides
			//@{
			friend std::ostream& operator<< (std::ostream&,const Vector3&);
			//@}

			double  operator[] (int i) const
			{
				if((i < 0)||(i > 2))
					throw std::runtime_error("Out of bounds in Vector3::operator[]") ;

				return _xyz[i];
			}

			double& operator[] (int i)
			{
				if((i < 0)||(i > 2))
					throw std::runtime_error("Out of bounds in Vector3::operator[]") ;

				return _xyz[i];
			}

		private:
			double _xyz[3];  //!< The 3 vector components

	}; // interface of Vector3
}
#endif // _VECTOR3_H
