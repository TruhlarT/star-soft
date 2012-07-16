//
// Pibero Djawotho <pibero@tamu.edu>
// Texas A&M University
// 14 Jan 2011
//

#include <algorithm>
using namespace std;

#include "bits.hh"
#include "Board.hh"
#include "qt32b_fms_2009_a.hh"

void qt32b_fms_2009_a(Board& qt)
{
  qt.output = 0;

  int htadc = 0;
  int htid  = 0;

  for (int dcard = 0; dcard < 4; ++dcard) {
    int sum = 0;
    for (int dch = 7; dch >= 0; --dch) {
      int id  = dcard*8+dch;
      int adc = qt.channels[id];
      sum += adc;
      adc = getbits(adc,5,7);
      if (adc > htadc) {
        htadc = adc;
        htid  = id;
      }
    }
    if (sum & ~0x3ff)
      sum = 0x1f;
    else
      sum = getbits(sum,5,5);
    qt.output |= sum << (dcard*5);
  }

  qt.output |= htadc << 20;
  qt.output |= htid  << 27;
}

void getQtDaughterSum(int qtout, int* sum)
{
  sum[0] = getbits(qtout,0 ,5);
  sum[1] = getbits(qtout,5 ,5);
  sum[2] = getbits(qtout,10,5);
  sum[3] = getbits(qtout,15,5);
}

int getQtHighTowerAdc(int qtout)
{
  return getbits(qtout,20,7);
}

int getQtHighTowerId(int qtout)
{
  return getbits(qtout,27,5);
}

void getQtSumAndHighTower(int* channels, int* A, int* B, int* C, int* D, int& htadc, int& htid)
{
  getQtDaughterSum(channels[3],A);
  getQtDaughterSum(channels[2],B);
  getQtDaughterSum(channels[1],C);
  getQtDaughterSum(channels[0],D);

  int adc[4], id[4];

  transform(channels,channels+4,adc,getQtHighTowerAdc);
  transform(channels,channels+4,id ,getQtHighTowerId );

  int idx = max_element(adc,adc+4) - adc;

  htadc = adc[idx];
  htid  = id [idx];
}

void getQtSumAndHighTower(int* channels, int* I, int* J, int& htadc, int& htid)
{
  getQtDaughterSum(channels[1],I);
  getQtDaughterSum(channels[0],J);

  int adc[2], id[2];

  transform(channels,channels+2,adc,getQtHighTowerAdc);
  transform(channels,channels+2,id ,getQtHighTowerId );

  int idx = max_element(adc,adc+2) - adc;

  htadc = adc[idx];
  htid  = id [idx];
}
