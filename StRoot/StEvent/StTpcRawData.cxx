/***************************************************************************
 *
 * $Id: StTpcRawData.cxx,v 2.2 2008/04/24 16:06:25 fisyak Exp $
 *
 * Author: Yuri Fisyak, Mar 2008
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StTpcRawData.cxx,v $
 * Revision 2.2  2008/04/24 16:06:25  fisyak
 * Clean up before next move
 *
 * Revision 2.1  2008/03/13 16:42:24  ullrich
 * Initial Revision
 *
 **************************************************************************/
#include "StTpcRawData.h"
#include "Riostream.h"
#include <assert.h>
#include "TMath.h"
#include "StDaqLib/TPC/trans_table.hh"

static const Int_t NumberOfPadsAtRow[__NumberOfRows__] = {
    88, 96,104,112,118,126,134,142,150,158, // Inner
   166,174,182,
                98,100,102,104,106,106,108, // Outer
   110,112,112,114,116,118,120,122,122,124,
   126,128,128,130,132,134,136,138,138,140,
   142,144,144,144,144
};

ClassImp(StTpcDigitalSector);
ClassImp(StTpcRawData);
//________________________________________________________________________________
Int_t StTpcDigitalSector::numberOfPadsAtRow(Int_t row) {return (row >= 1 && row <= __NumberOfRows__) ? NumberOfPadsAtRow[row-1] : 0;}
//________________________________________________________________________________
StTpcDigitalSector::StTpcDigitalSector(void *db) {
  StDigitalTimeBins  timeBins;
  StDigitalPadRow    padRow;
  for(UInt_t irow=0; irow< __NumberOfRows__; irow++) {
    padRow.resize(NumberOfPadsAtRow[irow], timeBins);
    mData.push_back(padRow);
  }
}
//________________________________________________________________________________
void StTpcDigitalSector::clear() {// clears only the time bins
  for(UInt_t irow=0; irow<mData.size(); irow++) {
    for(UInt_t ipad=0; ipad<mData[irow].size(); ipad++) {
      mData[irow][ipad].clear();
    }
  }
}
//________________________________________________________________________________
void StTpcDigitalSector::assignTimeBins(Int_t rowN, Int_t padN, StDigitalTimeBins* tbins) {
  if (mData[(rowN-1)][(padN-1)].size())
    mData[(rowN-1)][(padN-1)].clear();
  mData[(rowN-1)][(padN-1)].swap(*tbins);
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::cleanup() {
  UInt_t numberOfEmptyRows=0;
  for (UInt_t iRow=0; iRow<mData.size(); iRow++) {
    UInt_t numberOfEmptyPads=0;
    for (UInt_t iPad=0; iPad<mData[iRow].size(); iPad++) {
      if (mData[iRow][iPad].size()<7) {
	mData[iRow][iPad].clear();
	numberOfEmptyPads++;
      }
    } // Pads are now clean
    if (numberOfEmptyPads == mData[iRow].size()) {
      mData[iRow].clear();
      numberOfEmptyRows++;
    }
  } // Rows are now clean
    //cout << "This sector had " << numberOfEmptyRows << " empty rows." << endl;
  if (numberOfEmptyRows==mData.size()) return 1;
  else return 0;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::getSequences(Int_t PadRow, Int_t Pad, Int_t *nSeq, StSequence** Seq, UShort_t ***Ids) {
  *Seq=0;
  if (Ids) *Ids=0;*nSeq=0;
  mSequence.clear();
  mIds.clear();
  StDigitalTimeBins* TrsPadData = timeBinsOfRowAndPad(PadRow,Pad);
  if (!TrsPadData) return 1;
  StDigitalTimeBins &trsPadData = *TrsPadData;
  Int_t nTimeBins = trsPadData.size();
  if (!nTimeBins) return 2;
  // Construct the sequences:
  StSequence aSequence;
  static UShort_t ids[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for (Int_t ibin=0;ibin<nTimeBins;ibin++)  {
    aSequence.length       = trsPadData[ibin].size();
    if (aSequence.length > 31) aSequence.length = 31;
    aSequence.startTimeBin = trsPadData[ibin].time();
    aSequence.firstAdc     = trsPadData[ibin].adc();
    mSequence.push_back(aSequence);
    if (trsPadData[ibin].isIdt()) mIds.push_back(trsPadData[ibin].idt());
    else                          mIds.push_back(&ids[0]);
  }
  *nSeq = mSequence.size();
  *Seq = &mSequence[0];
  if (Ids) *Ids = &mIds[0];
  return 0;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::getPadList(Int_t padRow, UChar_t **padList) {
  mPadList.clear();
  assert( padRow>=1 && padRow <=__NumberOfRows__);
  // Loop over all the pads:
  for(Int_t ii = 1; ii<=NumberOfPadsAtRow[padRow-1]; ii++) {
    if (numberOfTimeBins(padRow,ii) > 0) {
      mPadList.push_back(ii);
    }
  }
  *padList = &mPadList[0];
  return mPadList.size();
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::putTimeAdc(Int_t row, Int_t pad, UShort_t *ADCs, UShort_t *IDTs) {// 10 -> 8 conversion
  Int_t ntimebins = 0;
  StDigitalTimeBins  digPadData;
  Int_t tbC = -999;
  for (Int_t tb = 0; tb < __MaxNumberOfTimeBins__; tb++) {
    if (! ADCs[tb]) continue;
    if (tb != tbC+1) digPadData.push_back(StDigitalPair(tb));
    tbC = tb;
    UChar_t adc = log10to8_table[ADCs[tb]];
    if (IDTs) digPadData.back().add(adc,IDTs[tb]);
    else      digPadData.back().add(adc);
    ntimebins++;
  }
  if (ntimebins) assignTimeBins(row,pad,&digPadData);
  return ntimebins;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::putTimeAdc(Int_t row, Int_t pad, UChar_t *ADCs, UShort_t *IDTs) {// no conversion
  Int_t ntimebins = 0;
  StDigitalTimeBins  digPadData;
  Int_t tbC = -999;
  for (Int_t tb = 0; tb < __MaxNumberOfTimeBins__; tb++) {
    if (! ADCs[tb]) continue;
    if (tb != tbC+1) digPadData.push_back(StDigitalPair(tb));
    tbC = tb;
    UChar_t adc = ADCs[tb];
    if (IDTs) digPadData.back().add(adc,IDTs[tb]);
    else      digPadData.back().add(adc);
    ntimebins++;
  }
  assignTimeBins(row,pad,&digPadData);
  return ntimebins;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::getTimeAdc(Int_t row, Int_t pad, UShort_t ADCs[__MaxNumberOfTimeBins__], UShort_t IDTs[__MaxNumberOfTimeBins__]) { 
  // 8->10 conversion
  Int_t ntimebins = 0;
  memset (ADCs, 0, sizeof(ADCs));
  memset (IDTs, 0, sizeof(IDTs));
  StSequence *list;
  UShort_t  **listOfIdt = 0;
  Int_t       nseq = 0;
  if (getSequences(row,pad,&nseq,&list,&listOfIdt)) return ntimebins;
  for (Int_t i = 0; i < nseq; i++) {
    Int_t tb = list[i].startTimeBin;
    tb = TMath::Max(0,TMath::Min(511,tb));
    Int_t seqLen=list[i].length;
    for (Int_t j = 0; j < seqLen; j++) {
      ntimebins++;
      ADCs[tb+j] = log8to10_table[list[i].firstAdc[j]];
      IDTs[tb+j] = (listOfIdt) ? listOfIdt[i][j] : 0;
    }
  }
  return ntimebins;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::getTimeAdc(Int_t row, Int_t pad, UChar_t ADCs[__MaxNumberOfTimeBins__], UShort_t IDTs[__MaxNumberOfTimeBins__]) {
  // no conversion
  Int_t ntimebins = 0;
  memset (ADCs, 0, sizeof(ADCs));
  memset (IDTs, 0, sizeof(IDTs));
  StSequence *list;
  UShort_t  **listOfIdt = 0;
  Int_t       nseq = 0;
  if (getSequences(row,pad,&nseq,&list,&listOfIdt)) return ntimebins;
  for (Int_t i = 0; i < nseq; i++) {
    Int_t tb = list[i].startTimeBin;
    tb = TMath::Max(0,TMath::Min(511,tb));
    Int_t seqLen=list[i].length;
    for (Int_t j = 0; j < seqLen; j++) {
      ntimebins++;
      ADCs[tb+j] = list[i].firstAdc[j];
      IDTs[tb+j] = (listOfIdt) ? listOfIdt[i][j] : 0;
    }
  }
  return ntimebins;
}
//________________________________________________________________________________
StTpcDigitalSector &StTpcDigitalSector::operator+= (StTpcDigitalSector& v) {
  static UShort_t ADCs1[__MaxNumberOfTimeBins__], ADCs2[__MaxNumberOfTimeBins__];
  static UShort_t IDTs1[__MaxNumberOfTimeBins__], IDTs2[__MaxNumberOfTimeBins__];
  for (Int_t row = 1; row <= __NumberOfRows__; row++) {
    Int_t npad2 = v.numberOfPadsInRow(row);
    if (! npad2) continue;
    for (Int_t pad = 1; pad <= NumberOfPadsAtRow[row-1]; pad++) {
      Int_t ntb2 =  v.numberOfTimeBins(row,pad);
      if (! ntb2) continue;
      Int_t ntb1 =    numberOfTimeBins(row,pad);
      if (! ntb1) {
	StDigitalTimeBins *tbins2 = v.timeBinsOfRowAndPad(row,pad);
	assignTimeBins(row,pad,tbins2);
	continue;
      }
      getTimeAdc(row,pad,ADCs1,IDTs1);
      v.getTimeAdc(row,pad,ADCs2,IDTs2);
      Bool_t ifIDT = false;
      for (Int_t i = 0; i < __MaxNumberOfTimeBins__; i++) {
	if (! ifIDT && (IDTs1[i] || IDTs2[i])) ifIDT = true;
	if ((IDTs1[i] || IDTs2[i]) && ADCs1[i] < ADCs2[i]) IDTs1[i] = IDTs2[i];
	ADCs1[i] += ADCs2[i];
      }
      if (ifIDT) putTimeAdc(row, pad, ADCs1, IDTs1);
      else       putTimeAdc(row, pad, ADCs1);
    }
  }
  return *this;
}
//________________________________________________________________________________
void StTpcDigitalSector::Print(const Option_t *opt) const {
  Int_t nrows = __NumberOfRows__;
  for (Int_t row = 1; row <= nrows; row++) {
    //    cout << "sector/row " << mSector << "/" << row << endl;
    Int_t npads = numberOfPadsInRow(row);
    for (Int_t pad = 1; pad <= npads; pad++) {
      //      cout << "sector/row/pad = " << mSector << "/" << row << "/" << pad << endl;
      Int_t ntb = numberOfTimeBins(row,pad);
      if (! ntb) continue;
      cout << "sector/row/pad = " << mSector << "/" << row << "/" << pad << " = " << ntb << " time sequences" << endl;
    }
  }
}
//________________________________________________________________________________
void StTpcRawData::setSector(UInt_t  sector, StTpcDigitalSector* digitSector) {    
  if (sector > 0 && sector <= mSectors.size()) {
    if (mSectors[sector-1]) delete mSectors[sector-1];
    digitSector->setSector(sector);
    mSectors[sector-1] = digitSector;
  }
}
//________________________________________________________________________________
void StTpcRawData::Clear(const Option_t*) {
  for (UInt_t ii=0; ii<mSectors.size(); ii++) {SafeDelete(mSectors[ii]);}
}
//________________________________________________________________________________
StTpcRawData &StTpcRawData::operator+=(StTpcRawData &v) {
  for (Int_t i = 1; i <= 24; i++) {
    StTpcDigitalSector *s1 =   GetSector(i);
    StTpcDigitalSector *s2 = v.GetSector(i);
    if (! s2) continue;
    if (! s1) {
      setSector(i, s2);
      continue;
    }
    *s1 += *s2;
  }
  return *this;
}
//________________________________________________________________________________
Int_t StTpcRawData::getVecOfPixels(StVectPixel &pixels, Int_t sector, Int_t row, Int_t padMin, Int_t padMax, Int_t tMin, Int_t tMax) {
  pixels.clear();
  StTpcDigitalSector *s =   GetSector(sector);
  static UShort_t ADCs[__MaxNumberOfTimeBins__],  IDTs[__MaxNumberOfTimeBins__];
  Int_t npads = s->numberOfPadsInRow(row);
  if (npads) {
    for (Int_t pad = padMin; pad <= padMax; pad++) {
      Int_t ntbs =    s->numberOfTimeBins(row,pad);
      if (ntbs) {
	s->getTimeAdc(row,pad,ADCs,IDTs);
	for (Int_t tb = tMin; tb <= tMax; tb++) {
	  if (ADCs[tb])	pixels.push_back(StTpcPixel(kTpcId,sector,row,pad,tb,ADCs[tb],IDTs[tb],0));
	}
      }
    }
  }
  return pixels.size();
}
//________________________________________________________________________________
void StTpcRawData::Print(const Option_t *opt) const {
  Int_t N = ((StTpcRawData *) this)->size();
  for (Int_t i = 0; i < N; i++) ((StTpcDigitalSector* )mSectors[i])->Print(opt);
}
