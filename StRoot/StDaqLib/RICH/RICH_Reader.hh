 /***************************************************************************
 * $id: Rich Event Reader
 * Author: Jon Gans and M.J. LeVine
 ***************************************************************************
 * Description: common definitions for RICH (dummy placeholder)
 *      
 *
 *   change log
 * 02-Jul-99 MJL add navigation code to get to RICHP bank
 * 08-Jul-99 MJL completely change definition - RICH_Reader is independent 
 *               class which is handed a pointer at the constructor invocation
 * 22-Nov-99 MJL fixed bug in array size  unsigned short RichMatrix[][]
 ***************************************************************************
 * $Log: Opens Event From File, Fills Struct 
 *
 **************************************************************************/
#ifndef RICH_READER_HH
#define RICH_READER_HH

#include "StDaqLib/GENERIC/EventReader.hh"
#include "StDaqLib/GENERIC/RecHeaderFormats.hh"
#include "StDaqLib/GENERIC/swaps.hh"

#define RICH_CRAM_BANKS 8   /* data banks lowest level */
#define TIC_NUM_CRAMS   4
#define MAX_NUM_CRAMS   8
#define MAX_CHANNEL_NUM 575  
  
struct offlen {
  unsigned int off;
  unsigned int len;		
} ;	

struct Bank_RICP: public Bank
{
  struct offlen CramPTR[2*MAX_NUM_CRAMS] ; /* number of CRAM blocks */
  struct offlen Reserved[2];
  
} ;

struct RICCRAMP: public Bank 
{ 
  struct offlen banks[RICH_CRAM_BANKS];
};


struct RICDATAD: public Bank{
  
  unsigned int chanADC[1];  // This is the first word of the Channel/ADC array
                 // there are many more following it, specified by the
                 // total amount of words, including this first one is
                 // RICDATAD->header.BankLenth - sizeof(RICHDATAD->header)/4
};


class RICH_Reader{
  void ProcessEvent(const Bank_RICP * RichPTR);

public:

RICH_Reader(EventReader *er, Bank_RICP *pRICP);

~RICH_Reader(){}; 

unsigned short GetADCFromCoord(int x,int y);
unsigned short GetADCFromCramChannel(int cramBlock,int channelNum);
unsigned int GetEventNumber();

const char * GetBankType();

int IsByteSwapped();

protected:

// copy of EventReader pointer
EventReader *ercpy;

// Bank Pointers
struct Bank_RICP *pBankRICP;

struct RichDATA{
  char * BankType; // Will be filled with a 9 char array (8 letters + NULL)
  unsigned int ByteSwapped ; // Should be 0x04030302
  unsigned int EventNumber;
  unsigned short RichMatrix[ MAX_CHANNEL_NUM / 6 + 1] [ TIC_NUM_CRAMS * 6] ; // Matrix of ADC's in Physical Positions
} jon;                                                                        // in tic, each row is 96 channels
                                                                              // and it takes 6 rows to fit each cramBank

};

RICH_Reader *getRICHReader(EventReader *er);

#endif












