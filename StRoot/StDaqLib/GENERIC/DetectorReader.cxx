/***************************************************************************
 * $Id: DetectorReader.cxx,v 1.1 1999/07/02 22:26:55 levine Exp $
 * Author: Jeff Landgraf
 ***************************************************************************
 * Description:  Detector Factory
 *      
 *
 *   change log
 * 02-Jul-99 MJL add #includes for other detectors
 *
 ***************************************************************************
 * $Log: DetectorReader.cxx,v $
 * Revision 1.1  1999/07/02 22:26:55  levine
 * moved from TPC directory. Now is the factory for all detector readers.
 * Detector groups do not have to touch this file - only add functionality
 * to their own directory tree.
 *
 * Revision 1.2  1999/07/02 04:43:22  levine
 * Many changes -
 *  navigates to head of TPCP bank independent of position.
 *  move declarations out of loops where they were upsetting some compilers
 *  suppress output from class libraries with run-time switch 
 *  EventReader.verbose
 *
 *
 **************************************************************************/
#include "StDaqLib/GENERIC/EventReader.hh"
#include "TPC/TPCV1P0_Reader.hh"
#include "TPC/TPCV2P0_Reader.hh"
#include "TRG/TRG_Reader.hh"
#include "SVT/SVT_Reader.hh"
#include "SSD/SSD_Reader.hh"
#include "EMC/EMC_Reader.hh"
#include "RICH/RICH_Reader.hh"
#include "FTPC/FTPC_Reader.hh"



DetectorReader *getDetectorReader(EventReader *er, string det)
{
  DetectorReader *dr;

  if(det == "TPC")
    {
      dr = new TPCV1P0_Reader(er);
    }
  else if (det == "TPCV1P0")
    {
      dr = new TPCV1P0_Reader(er);
    }
   else if (det == "TPCV2P0")
     {
       dr = new TPCV2P0_Reader(er);
     }
  else if  (det == "SSD")
     {
       dr = new SSD_Reader(er);
     }
  else if  (det == "SVT")
     {
       dr = new SVT_Reader(er);
     }
  else if  (det == "RICH")
     {
       dr = new RICH_Reader(er);
     }
  else if  (det == "FTPC")
     {
       dr = new FTPC_Reader(er);
     }
  else if  (det == "EMC")
     {
       dr = new EMC_Reader(er);
     }
  else if  (det == "TRG")
     {
       dr = new TRG_Reader(er);
     }
  else
  {
    dr = NULL;
  }

  return dr;
}
