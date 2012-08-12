#include "StMessMgr.h"
#include "StFgtDb.h"
#include <fstream>
using namespace std;

void
StFgtDb::printFgtDumpCSV1(TString fname, int myDate, int myTime) {

  ofstream fd;
  fd.open(fname.Data());

  if (fd.is_open())
    {

      cout<<"Saving FGT output in "<<fname.Data()<<endl;
      
      fd<<"#  FGT mapping, timeStamp "<< myDate<<" "<<myTime<<"\n";
      fd<<"# electId,geoID,   RDO(1;2),ARM(0-4),APV(0-9;12-21),chan(0-127),  disk(1-6),quad(A-D),layer(P;R),strip(P:0-719;R0-279+400-679), ordinate(rad;cm),lowSpan(cm;rad),upSpan(cm;rad), geoName, stat,ped(ADC),sigPed(ADC)\n";
      

      StFgtDb *fgtDb=this;

      int nTry=0, nMap=0;
      for (int rdo=1;rdo<=2;rdo++){// 2 RDOs numbered 1,2
	for (int arm=0;arm<6;arm++){//6 arms numbered from 0
	  for (int apv=0;apv<=21;apv++){//24 APVs numbered 0-23 but in real life APV# 10,11,22,23 are unused so 0-19 in determining electronic Id
	    if ((apv==10)||(apv==11)) continue;	
	  
	    for (int channel=0;channel<128;channel++){//128 channels numbered from 0
	      
	      nTry++;
	      int geoId=fgtDb->getGeoIdFromElecCoord(rdo, arm, apv, channel);
	      if (geoId<0) continue;
	      nMap++;
	      Short_t disk,quad,quad2,strip; Char_t layer;
	      Double_t  ordinate,  lowerSpan,  upperSpan;
	      StFgtGeom::decodeGeoId(geoId,disk,quad,layer,strip);
	      quad2= quad;
	      StFgtGeom::getPhysicalCoordinate(geoId,disk,quad2,layer,ordinate,lowerSpan,upperSpan);
	      
	      double  ped=fgtDb->getPedestalFromElecCoord(rdo,arm,apv,channel);
	      double  pedSig=fgtDb->getPedestalSigmaFromElecCoord(rdo,arm,apv,channel);
	      Short_t stat=fgtDb->getStatusFromElecCoord(rdo,arm,apv,channel);	      
	      int     electId = StFgtGeom::getElectIdFromElecCoord(rdo,arm,apv,channel);
	      std::string  geoName=fgtDb->getGeoNameFromElecCoord(rdo,arm,apv,channel);	 

	      
	      fd<<electId<<", "<<geoId<<", "<<rdo<<", "<<arm<<", "<<apv<<", "<<channel<<", "<<disk+1<<", "<<quad<<", "<<layer<<", "<<strip<<", "<<ordinate<<", "<<lowerSpan<<", "<<upperSpan<<", "<<geoName.data()<<", "<<stat<<", "<<ped<<",  "<<pedSig<<"\n";
	    
	    }
	  }
	}
      }
    

      fd<<"#  FGT mapping end, nTry= "<<nTry<<" nMap="<< nMap<<" from StFgtDb\n";
      fd.close();
      
    }
  else
   {
     cout << "Error opening file";
   }
  
}




Int_t StFgtDb::getElecCoordFromGeoId(
    Int_t geoId, Int_t& rdo, Int_t& arm, Int_t& apv, Int_t& channel
)
{
    if ( geoId < 0 || geoId >= kFgtNumGeoIds )
    {
        LOG_DEBUG << "GeoId " << geoId << " out of range in StFgtDb::getElecCoordFromGeoId." << endm;
        rdo = kFgtError;
        arm = kFgtError;
        apv = kFgtError;
        channel = kFgtError;

        return kFgtError;
    }

    Int_t elecId = m_rmap->Mapping[ geoId ];

    StFgtGeom::decodeElectronicId( elecId, rdo, arm, apv, channel );

    return 0;
}

Int_t StFgtDb::getElecCoordFromGeoName(
    const std::string & geoName,
    Int_t& rdo, Int_t& arm, Int_t& apv, Int_t& channel
)
{
    Int_t geoId =
	StFgtGeom::translateGeoNameToGeoId( geoName );

    if ( geoId < 0 )
    {
	rdo = kFgtError;
	arm = kFgtError;
	apv = kFgtError;
	channel = kFgtError;

	return kFgtError;
    }

    getElecCoordFromGeoId( geoId, rdo, arm, apv, channel );

    return 0;
}

Double_t StFgtDb::getPedestalFromGeoId( Int_t geoId )
{
    if ( geoId < 0 || geoId >= kFgtNumGeoIds )
    {
        LOG_DEBUG << "GeoId " << geoId << " out of range in StFgtDb::getPedestalFromGeoId." << endm;
        return kFgtError;
    }

    Int_t elecId = m_rmap->Mapping[ geoId ];
    return m_pedestal->AdcPedestal[ elecId ];
}

Double_t StFgtDb::getPedestalFromElecId( Int_t elecId)
{
    if ( elecId < 0 || elecId >= kFgtNumElecIds )
    {
        LOG_DEBUG << "Electronic ID " << elecId << " out of range in StFgtDb::getPedestalFromElecId." << endm;
        return kFgtError;
    }

    return m_pedestal->AdcPedestal[ elecId ];
}

Double_t StFgtDb::getPedestalSigmaFromGeoId( Int_t geoId )
{
    if ( geoId < 0 || geoId >= kFgtNumGeoIds )
    {
        LOG_DEBUG << "GeoId " << geoId << " out of range in StFgtDb::getPedestalSigmaFromGeoId." << endm;
        return kFgtError;
    }

    Int_t elecId = m_rmap->Mapping[ geoId ];
    return m_pedestal->AdcPedestalRMS[ elecId ];
}

Double_t StFgtDb::getPedestalSigmaFromElecId( Int_t elecId )
{
    if ( elecId < 0 || elecId >= kFgtNumElecIds )
    {
        LOG_DEBUG << "Electronic ID " << elecId << " out of range in StFgtDb::getPedestalSigmaFromElecId." << endm;
        return kFgtError;
    }

    return m_pedestal->AdcPedestalRMS[ elecId ];
}

Char_t StFgtDb::getPedestalStatusFromGeoId( Int_t geoId )
{
    if ( geoId < 0 || geoId >= kFgtNumGeoIds )
    {
        LOG_DEBUG << "GeoId " << geoId << " out of range in StFgtDb::getPedestalStatusFromGeoId." << endm;
        return kFgtErrorChar;
    }

    Int_t elecId = m_rmap->Mapping[ geoId ];
    return m_pedestal->Status[ elecId ];
}

Char_t StFgtDb::getPedestalStatusFromElecId( Int_t elecId )
{
    if ( elecId < 0 || elecId >= kFgtNumElecIds )
    {
        LOG_DEBUG << "Electronic ID " << elecId << " out of range in StFgtDb::getPedestalStatusFromElecId." << endm;
        return kFgtErrorChar;
    }

    return m_pedestal->Status[ elecId ];
}

Char_t StFgtDb::getStatusFromGeoId( Int_t geoId )
{
    if ( geoId < 0 || geoId >= kFgtNumGeoIds )
    {
        LOG_DEBUG << "GeoId " << geoId << " out of range in StFgtDb::getStatusFromGeoId." << endm;
        return kFgtErrorChar;
    }

    Int_t elecId = m_rmap->Mapping[ geoId ];
    return m_status->Status[ elecId ];
}

Char_t StFgtDb::getStatusFromElecId( Int_t elecId )
{
    if ( elecId < 0 || elecId >= kFgtNumElecIds )
    {
        LOG_DEBUG << "Electronic ID " << elecId << " out of range in StFgtDb::getStatusFromElecId." << endm;
        return kFgtErrorChar;
    }

    return m_status->Status[ elecId ];
}

Double_t StFgtDb::getGainFromGeoId( Int_t geoId )
{
    if ( geoId < 0 || geoId >= kFgtNumGeoIds )
    {
        LOG_DEBUG << "GeoId " << geoId << " out of range in StFgtDb::getGainFromGeoId." << endm;
        return kFgtError;
    }

    Int_t elecId = m_rmap->Mapping[ geoId ];
    return m_gain->Gain[ elecId ];
}

Double_t StFgtDb::getGainFromElecId( Int_t elecId )
{
    if ( elecId < 0 || elecId >= kFgtNumElecIds )
    {
        LOG_DEBUG << "Electronic ID " << elecId << " out of range in StFgtDb::getGainFromElecId." << endm;
        return kFgtError;
    }

    return m_gain->Gain[ elecId ];
}

Char_t StFgtDb::getGainStatusFromGeoId( Int_t geoId )
{
    if ( geoId < 0 || geoId >= kFgtNumGeoIds )
    {
        LOG_DEBUG << "GeoId " << geoId << " out of range in StFgtDb::getGainStatusFromGeoId." << endm;
        return kFgtErrorChar;
    }

    Int_t elecId = m_rmap->Mapping[ geoId ];
    return m_gain->Status[ elecId ];
}

Char_t StFgtDb::getGainStatusFromElecId( Int_t elecId )
{
    if ( elecId < 0 || elecId >= kFgtNumElecIds )
    {
        LOG_DEBUG << "Electronic ID " << elecId << " out of range in StFgtDb::getGainStatusFromElecId." << endm;
        return kFgtErrorChar;
    }

    return m_gain->Status[ elecId ];
}

Double_t StFgtDb::getMapping(
    Int_t rdo, Int_t arm, Int_t apv, Int_t channel
)
{
	Short_t disc, quadrant;
	Char_t layer;
	Double_t ordinate, lowerSpan, upperSpan;

	if ( getPhysCoordFromElecCoord(
		rdo, arm, apv, channel,
		disc, quadrant, layer,
		ordinate, lowerSpan, upperSpan
	     ) < 0
	)
	    return kFgtError;
     
	return ordinate;
}

//  This, similarly, seems needlessly complicated.
bool StFgtDb::isR(
    Int_t rdo, Int_t arm, Int_t apv, Int_t channel
)
{
	Short_t disc, quadrant;
	Char_t layer;
	Double_t ordinate, lowerSpan, upperSpan;

	//  Can't do any boundry checking return value thing here. Going to
	//  have to let the call here handle the warning message.
	getPhysCoordFromElecCoord(
	    rdo, arm, apv, channel,
	    disc, quadrant, layer,
	    ordinate, lowerSpan, upperSpan
	);
     
	return (layer == 'R');
}




