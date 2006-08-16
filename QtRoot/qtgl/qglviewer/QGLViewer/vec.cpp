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

#include "domUtils.h"
#include "vec.h"

// Most of the methods are declared inline in vec.h

using namespace qglviewer;
using namespace std;

/*! Projects the Vec on the axis of direction \p direction that passes through the origin.

\p direction does not need to be normalized (but must be non null). */
void Vec::projectOnAxis(const Vec& direction)
{
#ifndef QT_NO_DEBUG
  if (direction.squaredNorm() < 1.0E-10)
    qWarning("Vec::projectOnAxis: axis direction is not normalized (norm=%f).", direction.norm());
#endif

  *this = (((*this)*direction) / direction.squaredNorm()) * direction;
}

/*! Projects the Vec on the plane whose normal is \p normal that passes through the origin.

\p normal does not need to be normalized (but must be non null). */
void Vec::projectOnPlane(const Vec& normal)
{
#ifndef QT_NO_DEBUG
  if (normal.squaredNorm() < 1.0E-10)
    qWarning("Vec::projectOnPlane: plane normal is not normalized (norm=%f).", normal.norm());
#endif

  *this -= (((*this)*normal) / normal.squaredNorm()) * normal;
}

Vec Vec::orthogonalVec() const
{
  if ((fabs(y) > fabs(x)) && (fabs(z) > fabs(x)))
    return Vec(0.0, -z, y);
  else
    if ((fabs(x) > fabs(y)) && (fabs(z) > fabs(y)))
      return Vec(-z, 0.0, x);
    else
      return Vec(-y, x, 0.0);
}

/*! Constructs a Vec from a \c QDomElement representing an XML code of the form \c <anyTagName
  x=".." y=".." z=".." />.

If one of these attributes is missing or is not a number, a warning is displayed and the associated
value is set to 0.0.

See also domElement() and initFromDOMElement(). */
Vec::Vec(const QDomElement& element)
{
  QStringList attribute;
  attribute << "x" << "y" << "z";
#if QT_VERSION >= 0x040000
  for (int i=0; i<attribute.size(); ++i)
#else
  for (unsigned int i=0; i<attribute.count(); ++i)
#endif
#ifdef UNION_NOT_SUPPORTED
    this->operator[](i) = DomUtils::floatFromDom(element, attribute[i], 0.0);
#else
    v_[i] = DomUtils::floatFromDom(element, attribute[i], 0.0);
#endif
}

/*! Returns an XML \c QDomElement that represents the Vec.

 \p name is the name of the QDomElement tag. \p doc is the \c QDomDocument factory used to create
 QDomElement.

 When output to a file, the resulting QDomElement will look like:
 \code
 <name x=".." y=".." z=".." />
 \endcode

 Use initFromDOMElement() to restore the Vec state from the resulting \c QDomElement. See also the
 Vec(const QDomElement&) constructor.

 Here is complete example that creates a QDomDocument and saves it into a file:
 \code
 Vec sunPos;
 QDomDocument document("myDocument");
 QDomElement sunElement = document.createElement("Sun");
 document.appendChild(sunElement);
 sunElement.setAttribute("brightness", sunBrightness());
 sunElement.appendChild(sunPos.domElement("sunPosition", document));
 // Other additions to the document hierarchy...

 // Save doc document
 QFile f("myFile.xml");
 if (f.open(IO_WriteOnly))
 {
   QTextStream out(&f);
   document.save(out, 2);
   f.close();
 }
 \endcode

 See also Quaternion::domElement(), Frame::domElement(), Camera::domElement()... */
QDomElement Vec::domElement(const QString& name, QDomDocument& document) const
{
  QDomElement de = document.createElement(name);
  de.setAttribute("x", QString::number(x));
  de.setAttribute("y", QString::number(y));
  de.setAttribute("z", QString::number(z));
  return de;
}

/*! Restores the Vec state from a \c QDomElement created by domElement().

 The \c QDomElement should contain \c x, \c y and \c z attributes. If one of these attributes is
 missing or is not a number, a warning is displayed and the associated value is set to 0.0.

 To restore the Vec state from an xml file, use:
 \code
 // Load DOM from file
 QDomDocument doc;
 QFile f("myFile.xml");
 if (f.open(IO_ReadOnly))
 {
   doc.setContent(&f);
   f.close();
 }
 // Parse the DOM tree and initialize
 QDomElement main=doc.documentElement();
 myVec.initFromDOMElement(main);
 \endcode

 See also the Vec(const QDomElement&) constructor. */
void Vec::initFromDOMElement(const QDomElement& element)
{
  const Vec v(element);
  *this = v;
}

ostream& operator<<(ostream& o, const Vec& v)
{
  return o << v.x << '\t' << v.y << '\t' << v.z;
}

