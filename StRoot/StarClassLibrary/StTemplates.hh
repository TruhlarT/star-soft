/***************************************************************************
 *
 * $Id: StTemplates.hh,v 1.1 1999/01/30 03:59:05 fisyak Exp $
 *
 * Author: Thomas Ullrich, Jan 1999
 ***************************************************************************
 *
 * Description: 
 *
 ***************************************************************************
 *
 * $Log: StTemplates.hh,v $
 * Revision 1.1  1999/01/30 03:59:05  fisyak
 * Root Version of StarClassLibrary
 *
 * Revision 1.1  1999/01/30 03:59:05  fisyak
 * Root Version of StarClassLibrary
 *
 * Revision 1.1  1999/01/23 00:28:03  ullrich
 * Initial Revision
 *
 **************************************************************************/
#ifndef ST_TEMPLATES_HH
#define ST_TEMPLATES_HH

#ifdef ST_SOLVE_TEMPLATES

#include "StThreeVector.hh"
static	StThreeVector<float>		dummy1;
static	StThreeVector<double>		dummy2;
static	StThreeVector<long double>	dummy3;
#include "StLorentzVector.hh"
static	StLorentzVector<float>		dummy4;
static	StLorentzVector<double>		dummy5;
static	StLorentzVector<long double>	dummy6;
#include "StMatrix.hh"
static	StMatrix<float>			dummy7;
static	StMatrix<double>		dummy8;
static	StMatrix<long double>		dummy9;

#endif //ST_SOLVE_TEMPLATES

#endif //ST_TEMPLATES_HH

