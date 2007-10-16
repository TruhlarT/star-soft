/***************************************************************************
 *
 * $Id: StMcEventTypes.hh,v 2.12 2007/10/16 19:49:14 fisyak Exp $
 *
 * Author: Manuel Calderon de la Barca
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StMcEventTypes.hh,v $
 * Revision 2.12  2007/10/16 19:49:14  fisyak
 * rename Hft => Pxl, remove Hpd, Igt and Fst
 *
 * Revision 2.11  2006/09/25 14:20:43  fisyak
 * Add Hpd Hits
 *
 * Revision 2.10  2005/11/22 21:44:51  fisyak
 * Add compress Print for McEvent, add Ssd collections
 *
 * Revision 2.9  2005/07/07 18:20:49  calderon
 * Added support for IGT detector.
 *
 * Revision 2.8  2005/04/18 20:11:33  calderon
 * Addition of Fgt and Fst files.  Modified other files to accomodate changes.
 *
 * Revision 2.7  2004/09/14 05:00:29  calderon
 * Added support for Ist, Ssd and changes to Pixel, from "El Kai".
 *
 * Revision 2.6  2003/08/20 18:50:21  calderon
 * Addition of Tof classes and Pixel classes.  Modified track, event, and
 * container code to reflect this.
 * Fix bug in StMcVertex and in clearing of some hit collections.
 *
 * Revision 2.5  2003/02/19 03:16:05  calderon
 * Introduction of Ctb Hit Class and Ctb Hit Collection class, modified
 * StMcTrack, and StMcEvent accordingly.  Clearing of hits in StMcSvtWaferHitCollection.
 *
 * Revision 2.4  2000/06/06 02:58:41  calderon
 * Introduction of Calorimeter classes.  Modified several classes
 * accordingly.
 *
 * Revision 2.3  2000/03/06 20:33:08  calderon
 * svt layer -> svt barrel
 *
 * Revision 2.2  2000/03/06 18:05:21  calderon
 * 1) Modified SVT Hits storage scheme from layer-ladder-wafer to
 * barrel-ladder-wafer.
 * 2) Added Rich Hit class and collection, and links to them in other
 * classes.
 *
 * Revision 2.1  1999/12/03 21:31:19  calderon
 * Initial Revision
 *
 *
 **************************************************************************/
#ifndef StMcEventTypes_hh
#define StMcEventTypes_hh

#include "StMcContainers.hh"
#include "StMcCalorimeterHit.hh"
#include "StMcCtbHit.hh"
#include "StMcCtbHitCollection.hh"
#include "StMcEmcModuleHitCollection.hh"
#include "StMcEmcHitCollection.hh"
#include "StMcEvent.hh"
#include "StMcFtpcHit.hh"
#include "StMcFtpcHitCollection.hh"
#include "StMcFtpcPlaneHitCollection.hh"
#include "StMcHit.hh"
#include "StMcHitComparisons.hh"
#include "StMcRichHit.hh"
#include "StMcRichHitCollection.hh"
#include "StMcSvtHit.hh"
#include "StMcSvtHitCollection.hh"
#include "StMcSvtBarrelHitCollection.hh"
#include "StMcSvtLadderHitCollection.hh"
#include "StMcSvtWaferHitCollection.hh"
#include "StMcSsdHit.hh"
#include "StMcSsdHitCollection.hh"
#include "StMcSsdLadderHitCollection.hh"
#include "StMcTpcHit.hh"
#include "StMcTpcHitCollection.hh"
#include "StMcTpcPadrowHitCollection.hh"
#include "StMcTpcSectorHitCollection.hh"
#include "StMcTofHit.hh"
#include "StMcTofHitCollection.hh"
#include "StMcPixelHit.hh"
#include "StMcPixelHitCollection.hh"
#include "StMcPixelLayerHitCollection.hh"
#include "StMcIstHit.hh"
#include "StMcIstHitCollection.hh"
#include "StMcIstLayerHitCollection.hh"
#include "StMcFgtHit.hh"
#include "StMcFgtHitCollection.hh"
#include "StMcFgtLayerHitCollection.hh"
#include "StMcTrack.hh"
#include "StMcVertex.hh"
#endif
