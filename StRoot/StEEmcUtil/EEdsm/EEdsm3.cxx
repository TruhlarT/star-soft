#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "EEdsm3.h"


//--------------------------------------------------
//
//--------------------------------------------------
EEdsm3 ::  EEdsm3() {
  clear();
}

//--------------------------------------------------
//--------------------------------------------------
EEdsm3 ::  ~EEdsm3() { }

//--------------------------------------------------
//--------------------------------------------------
void EEdsm3 :: clear() {
  memset(data,0,sizeof(data));
}

//--------------------------------------------------
//--------------------------------------------------
void EEdsm3::setWord(int ch, ushort val){
  assert(ch>=0 && ch<nc);
  data[ch]=val;
}

//--------------------------------------------------
//--------------------------------------------------
ushort EEdsm3::getJPthr() {
  int ch=0;
  ushort val=data[ch]>>7;
  val=val & 3;
  return val;
}

//--------------------------------------------------
//--------------------------------------------------
ushort EEdsm3::getHTthr() {
  int ch=0;
  ushort val=data[ch]>>9;
  val=val & 3;
  return val;
}

//--------------------------------------------------
//--------------------------------------------------
ushort EEdsm3::getEthr() {
  int ch=0;
  ushort val=data[ch]>>11;
  val=val & 1;
  return val;
}
//--------------------------------------------------
//--------------------------------------------------
void EEdsm3 :: print( int k) {
  printf("EEdsm3:: print()  \n");
  printf("\n JPthr=%d  HTthr=%d Ethr=%d\n",getJPthr(), getHTthr(), getEthr());
}
 
// $Log: EEdsm3.cxx,v $
// Revision 1.2  2005/02/01 22:13:40  perev
// Compatibility to redhat
//
// Revision 1.1  2004/11/29 20:12:59  balewski
// first
//
// Revision 1.1  2004/02/17 03:09:17  balewski
// *** empty log message ***
//

