#include "Board.hh"
#include "bits.hh"
#include "fms_fm101_2015_a.hh"
#include "fms_fm001_2015_a.hh"
#include <stdio.h>

#include "registerHack.hh"

void fms_fm101_2015_a(Board& fm101)
{
  //const int R0 = fm101.registers[0]; // FMSsmall-cluster-th0
  //const int R1 = fm101.registers[1]; // FMSsmall-cluster-th1
  //const int R2 = fm101.registers[2]; // FMSsmall-layer1-mode: 0=data taking, 1=debug
  //Hack until we know details of registers
  int BSThr1=Sm_BSThr1; 
  int BSThr2=Sm_BSThr2; 
  int BSThr3=Sm_BSThr3; 

  //input
  int* in = (int*)fm101.channels;
  int T=in[1];
  int B=in[0];

  //Make 1 more BS sum
  int DD=getFM001_D23(T) + getFM001_D23(B);

  //Compare to threshold and OR
  int BS3 = getFM001_BS3(T) | getFM001_BS3(B) | (DD>BSThr3);
  int BS2 = getFM001_BS2(T) | getFM001_BS2(B) | (DD>BSThr2);
  int BS1DD=(DD>BSThr1);

  //BS1 bits
  int BS1T=getFM001_BS1A(T);
  int BS1M=getFM001_BS1BCD(T) | getFM001_BS1BCD(B) | BS1DD;
  int BS1B=getFM001_BS1A(B);

  //Jp sums
  int JpT=getFM001_JpAB(T)+getFM001_JpCD(T);
  int JpM=getFM001_JpCD(T)+getFM001_JpCD(B);
  int JpB=getFM001_JpAB(B)+getFM001_JpCD(B);
  if(JpT>0xff) JpT=0xff;
  if(JpM>0xff) JpM=0xff;
  if(JpB>0xff) JpB=0xff;
  
  fm101.output =  BS3 | BS2   << 1
    | BS1T << 2 | BS1M <<  3 | BS1B <<4 
    | JpT  << 5 | JpM  << 13 | JpB  <<21;
  
  printf("%s out=%08x BS3=%1d BS2=%1d BS1T/M/B=%1d %1d %1d JpT/M/B %3d %3d %3d\n",
	 fm101.name,fm101.output,
	 BS3,BS2,BS1T,BS1M,BS1B,JpT,JpM,JpB);
}

int getFM101_BS3(int out)  {return getbits(out, 0, 1);}
int getFM101_BS2(int out)  {return getbits(out, 1, 1);}
int getFM101_BS1T(int out) {return getbits(out, 2, 1);}
int getFM101_BS1M(int out) {return getbits(out, 3, 1);}
int getFM101_BS1B(int out) {return getbits(out, 4, 1);}
int getFM101_JpT(int out) {return getbits(out, 5, 8);}
int getFM101_JpM(int out) {return getbits(out,13, 8);}
int getFM101_JpB(int out) {return getbits(out,21, 8);}
