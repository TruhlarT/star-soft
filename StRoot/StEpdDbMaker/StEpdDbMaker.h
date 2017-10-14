
#ifndef STEPDDBMAKER_H
#define STEPDDBMAKER_H

#include "StMaker.h"

// tables in STAR DB - those will be defined via the includes in the
// .cxx code - no need for forwrd declaration here
//struct epdQTMap_st;
//struct epdFEEMap_st;
//struct epdStatus_st;
//struct epdGain_st;

class StEpdDbMaker : public StMaker{
  public:
    StEpdDbMaker(const Char_t *name="epdDb");
    virtual ~StEpdDbMaker();
    //virtual Int_t Init();
    //virtual Int_t Make();
    //virtual Int_t Finish();
    virtual Int_t InitRun( Int_t runNumber );
    //virtual void Clear(const Char_t *opt);

    void setDebug(Int_t debug){mDebug=debug;} // 0:minimal message, >0 more debug messages

    // epdQtMap table
    short GetCrateAdc(short ew, short pp, short tile){return mCrateAdc[ew][pp-1][tile-1];}
    short GetBoardAdc(short ew, short pp, short tile){return mBoardAdc[ew][pp-1][tile-1];}
    short GetChannelAdc(short ew, short pp, short tile){return mChannelAdc[ew][pp-1][tile-1];}
    short GetCrateTac(short ew, short pp, short tile){return mCrateTac[ew][pp-1][tile-1];}
    short GetBoardTac(short ew, short pp, short tile){return mBoardTac[ew][pp-1][tile-1];}
    short GetChannelTac(short ew, short pp, short tile){return mChannelTac[ew][pp-1][tile-1];}

    // epdFeeMap table
    short GetTuffId(short ew, short pp, short tile){return mTuffId[ew][pp-1][tile-1];}
    short GetTuffGroup(short ew, short pp, short tile){return mTuffGroup[ew][pp-1][tile-1];}
    short GetTuffChannel(short ew, short pp, short tile){return mTuffChannel[ew][pp-1][tile-1];}
    short GetReceiverBoard(short ew, short pp, short tile){return mReceiverBoard[ew][pp-1][tile-1];}
    short GetReceiverBoardChannel(short ew, short pp, short tile){return mReceiverBoardChannel[ew][pp-1][tile-1];}
    short GetCamacCrateAddress(short ew, short pp, short tile){return mCamacCrateAddress[ew][pp-1][tile-1];}
    char* GetOneWireId(short ew, short pp, short tile){return mWireOneId[ew][pp-1][tile-1];}

    // epdStatus table
    short GetStatus(short ew, short pp, short tile){return mStatus[ew][pp-1][tile-1];}

    // epdGain table
    float GetVPed(short ew, short pp, short tile){return mVPed[ew][pp-1][tile-1];}
    float GetMip(short ew, short pp, short tile){return mMip[ew][pp-1][tile-1];}
    float GetQtPedestals(short ew, short pp, short tile){return mQtPedestals[ew][pp-1][tile-1];}
    float GetDarkCurrent(short ew, short pp, short tile){return mDarkCurrent[ew][pp-1][tile-1];}
    float GetQtPedestalsSigma(short ew, short pp, short tile){return mQtPedestalsSigma[ew][pp-1][tile-1];}
    float GetOffset(short ew, short pp, short tile){return mOffset[ew][pp-1][tile-1];}

  protected:

  private:
    void ResetArrays();
    Int_t mDebug;

    short mCrateAdc[2][12][31];
    short mBoardAdc[2][12][31];
    short mChannelAdc[2][12][31];
    short mCrateTac[2][12][31];
    short mBoardTac[2][12][31];
    short mChannelTac[2][12][31];

    short mTuffId[2][12][31];
    short mTuffGroup[2][12][31];
    short mTuffChannel[2][12][31];
    short mReceiverBoard[2][12][31];
    short mReceiverBoardChannel[2][12][31];
    short mCamacCrateAddress[2][12][31];
    char mWireOneId[2][12][31][20];

    short mStatus[2][12][31];

    float mVPed[2][12][31];
    float mMip[2][12][31];
    float mQtPedestals[2][12][31];
    float mDarkCurrent[2][12][31];
    float mQtPedestalsSigma[2][12][31];
    float mOffset[2][12][31];

    virtual const Char_t *GetCVS() const {static const Char_t cvs[]="Tag $Name:" __DATE__ " " __TIME__ ; return cvs;}
    ClassDef(StEpdDbMaker,1);
};
#endif
