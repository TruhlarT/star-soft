/***************************************************************************
 *
 * $Id: StPidAmpBGNet.cc,v 1.6 2000/07/12 15:38:35 aihong Exp $
 *
 * Author: Aihong Tang & Richard Witt (FORTRAN Version),Kent State U.
 *         Send questions to aihong@cnr.physics.kent.edu
 ***************************************************************************
 *
 * Description:part of StPidAmpMaker package
 *             StPidAmpBGNet is a net type with mass=1, charge=1
 *             it is for dedx~beta*gamma fitting
 ***************************************************************************
 *
 * $Log: StPidAmpBGNet.cc,v $
 * Revision 1.6  2000/07/12 15:38:35  aihong
 * update for real data
 *
 * Revision 1.5  2000/05/01 16:59:25  aihong
 * clean up
 *
 * Revision 1.4  2000/04/14 16:07:30  aihong
 * change BetheBlock to BetheBloch :-)
 *
 * Revision 1.3  2000/04/09 15:40:58  aihong
 * change sliceWidth4Window[1] to 0.03 for mBGNet
 *
 * Revision 1.2  2000/03/22 14:07:59  aihong
 * reduce unnecessary bound checking for faster run
 *
 * Revision 1.1.1.1  2000/03/09 17:48:34  aihong
 * Installation of package
 *
 **************************************************************************/


#include "TCanvas.h"
#include "StMessMgr.h"

#include "StPidAmpMaker/Infrastructure/StPidAmpBGNet.hh"
#include "StPidAmpMaker/Include/StPidAmpConst.hh"
#include <fstream.h>
//-------------------------------
StPidAmpBGNet::StPidAmpBGNet():StPidAmpNet(){


   fillSliceWidth();

  for (int k=0; k<NWindows4BG; k++) NSlice4Window[k]=0;

    redefineWindow();



    mBandGraphLowBetaGamma   =new TGraph();
    mBandGraphMiddleBetaGamma=new TGraph();
    bandGraph()->SetMaximum(0.8e-05);
    mBandGraphLowBetaGamma->SetMaximum(0.8e-05);
    mBandGraphMiddleBetaGamma->SetMaximum(0.8e-05);
}
//-------------------------------
StPidAmpBGNet::StPidAmpBGNet(StPidAmpParticle def, StPidAmpChannelInfo channelInfo):StPidAmpNet(def, channelInfo){

   fillSliceWidth();

  for (int k=0; k<NWindows4BG; k++) NSlice4Window[k]=0;

    redefineWindow();

    mBandGraphLowBetaGamma   =new TGraph();
    mBandGraphMiddleBetaGamma=new TGraph();

    bandGraph()->SetMaximum(0.8e-05);
    mBandGraphLowBetaGamma->SetMaximum(0.8e-05);
    mBandGraphMiddleBetaGamma->SetMaximum(0.8e-05);

    setUp();

}
//----------------------------------
void StPidAmpBGNet::fillBand(){ //fill band graph

  StPidAmpSliceIter iter;
  StPidAmpSlice*    theSlice;


  for( iter=sliceVector()->begin(); iter!=sliceVector()->end(); iter++) {

    theSlice=*iter;

    bool storedSth=((theSlice->slice()->GetMaximum())>0);

    if (((theSlice->sliceInfo()->meanDedx())>0.0)&& storedSth  ){ 
    //no window checking for mBGNet.(already checked when filled).

 bandGraph()->SetPoint(bandGraph()->GetN(), float(fabs(theSlice->meanRig())),float(fabs(theSlice->sliceInfo()->meanDedx()))); 

 if (fabs(theSlice->meanRig())<BandsEnd/(StPidAmpParticle::mPiPlus).mass())    
mBandGraphLowBetaGamma->SetPoint(mBandGraphLowBetaGamma->GetN(), float(fabs(theSlice->meanRig())),float(fabs(theSlice->sliceInfo()->meanDedx()))); 

  if (fabs(theSlice->meanRig())< mNetWindow.thirdWindowEnd())   
mBandGraphMiddleBetaGamma->SetPoint(mBandGraphMiddleBetaGamma->GetN(), float(fabs(theSlice->meanRig())),float(fabs(theSlice->sliceInfo()->meanDedx()))); 


    } 

  }

 }
//----------------------------------
void StPidAmpBGNet::processNet(StPidAmpTrkVector* trks){

//call functions needed to be processed in order.


  if (mFitBand){
     fitSlices();

     fillBand();

     fitBand();    


  } else {
    fitSlices();
    fillBand(); //just for mMultiBGNets 
  }




  drawNetFittings();
  fillNetOut();

}

//----------------------------------
void StPidAmpBGNet::fitBand(){


   double varyRange=0.05;


   TF1 *mBetheBlochFcn = new TF1 ("mBetheBlochFcn",funcBandPt, fabs(mParticleType.start()),fabs(mParticleType.end()),NBandParam);
  
  

   mBetheBlochFcn->SetParLimits(0,(mBandParams[0]-varyRange*fabs(mBandParams[0])),(mBandParams[0]+varyRange*fabs(mBandParams[0])));
   mBetheBlochFcn->SetParLimits(1,(mBandParams[1]-varyRange*fabs(mBandParams[1])),(mBandParams[1]+varyRange*fabs(mBandParams[1])));
   mBetheBlochFcn->SetParLimits(2,(mBandParams[2]-varyRange*fabs(mBandParams[2])),(mBandParams[2]+varyRange*fabs(mBandParams[2])));
          
   mBetheBlochFcn->SetParameter(3,double(mParticleType.charge()));//charge is 1 for mBGNet.
   mBetheBlochFcn->SetParameter(4,double(mParticleType.mass()));//mass is 1 for mBGNet.
   mBetheBlochFcn->SetParameter(5, double(CalibFactor));
   mBetheBlochFcn->SetParameter(6, double(Saturation));
   mBetheBlochFcn->SetParLimits(3, 1,1); //fixed.
   mBetheBlochFcn->SetParLimits(4, 1,1);
   mBetheBlochFcn->SetParLimits(5, 1,1);
   mBetheBlochFcn->SetParLimits(6, 1,1);

   // mBetheBlochFcn->SetParLimits(2,1.2775e-10,0.025e-5);


 if ((bandGraph()->GetN())>0) {

   bandGraph()->Fit("mBetheBlochFcn","R"); //R means use the range in TF1.
   mBandParams.clear();

   for (int i=0; i<NBandParam; i++)
   mBandParams.push_back(mBetheBlochFcn->GetParameter(i));
   

 }



   mBandFitFcn = new TF1 ("mBandsFcn",funcBandPt, BandsBegin,mParticleType.end(),NBandParam);
    for (int i=0; i<NBandParam; i++) 
    mBandFitFcn->SetParameter(i,mBetheBlochFcn->GetParameter(i));
       
   

   delete mBetheBlochFcn;

  
}
//----------------------------------
void StPidAmpBGNet::setUp(){//setUp based on mBandParams always.

       int i=0; int j=0; int k=0; int sz=0;
       double localPathHeight=PathHeight;

  if (sliceVector()->size()>0) sliceVector()->clear();
  if (pathVector()->size()>0) pathVector()->clear();//clear() not only 
                                                   //removes all elements,
                                                  //but also forces the
                                                 // capacity to zero!!

  for (int j=0; j<mNetWindow.NWindows(); j++){
       sz +=int((mNetWindow.length(j+1))/sliceWidth4Window[j]);
  }

   sz +=10;

   sliceVector()->reserve(sz); //reserve capacity

       //set up slices
 
   for (j=0; j<mNetWindow.NWindows(); j++){ 

     if (fabs(mNetWindow.windowBegin(j+1)>500)) 
     localPathHeight=PathHeight/2.0; //for e, we need narrow net


 SliceLoop: if ( ((i+1.0)*sliceWidth4Window[j]+fabs(mNetWindow.windowBegin(j+1)))<fabs(mNetWindow.windowEnd(j+1)) ) {
//window index begin with 1.so j+1

 double midRig=sliceWidth4Window[j]*(double(i)+0.5)+fabs(mNetWindow.windowBegin(j+1));


 double lowBd =dedxAtBandCenter(midRig) - localPathHeight*double(NPaths)/2.0;
 double highBd=dedxAtBandCenter(midRig) + localPathHeight*double(NPaths)/2.0;  


 StPidAmpSlice* ASlice= new StPidAmpSlice(k,midRig,lowBd, highBd,sliceWidth4Window[j], mName, &mParticleType);

 sliceVector()->push_back(ASlice);


 i++; k++;

 goto SliceLoop;
 }   

   NSlice4Window[j]=i;

    i=0;


   }


      for (i=0; i<mNetWindow.NWindows();i++)  NSliceAccum[i]=0;
   
      for (i=1; i<mNetWindow.NWindows();i++)  
      for (j=0; j<i; j++) NSliceAccum[i] +=NSlice4Window[j];
  


       StPidAmpSliceVector tmpCollect=*sliceVector();
       sliceVector()->swap(tmpCollect);
   
       fillNetOut();//for StPidChannelCollection::writeBGBands2Disk() 'sake.
       //cause if drawOpt ="B" only, channel is not processed, 
    //that means netOUt is not filled. but in StPidChannelCollection::writeBGBands2Disk()
       // we still need to read out netOut, so better to fill it during construction.
    

 
}
//----------------------------------
double StPidAmpBGNet::dedxAtBandCenter(double rig){

  //always calculate the dedx at band center by using 
  //parameters in mBandParams.
       double localBandsBegin=BandsBegin;
       double localBandsEnd  =BandsEnd/(StPidAmpParticle::mPiPlus).mass();

     if (mParticleType.id()==-2 || mParticleType.id()==-3 ||mParticleType.id()==-999) localBandsEnd=mParticleType.end();


          TF1 mBandBetheBlochFcn("mBandBetheBlochFcn",funcBandPt, localBandsBegin,localBandsEnd, NBandParam);

       mBandBetheBlochFcn.SetParameter(0,mBandParams[0]);
       mBandBetheBlochFcn.SetParameter(1,mBandParams[1]);
       mBandBetheBlochFcn.SetParameter(2,mBandParams[2]);
        
       mBandBetheBlochFcn.SetParameter(3,double(mParticleType.charge()));
       mBandBetheBlochFcn.SetParameter(4,mParticleType.mass());
       mBandBetheBlochFcn.SetParameter(5, double(CalibFactor));
       mBandBetheBlochFcn.SetParameter(6, double(Saturation));

          return mBandBetheBlochFcn.Eval(fabs(rig),0,0);


}

//----------------------------------
int StPidAmpBGNet::getSliceIndex(double x){

       int idx=mNetWindow.getWindowIdex(x);
       double fx=fabs(x);


       unsigned i=0;

     if (idx>0) i=int((fx-mNetWindow.windowBegin(idx))/sliceWidth4Window[idx-1]) + NSliceAccum[idx-1];

     else if (idx<=0) i=0;

 if (i>=sliceVector()->size()) i=sliceVector()->size()-1;
 if (i<0) i=0;
        
 return i;

}



//----------------------------------
void StPidAmpBGNet::drawNetFittings(){

  strstream stPath,stBand,stAmp,stReso,stLowBand,stMiddleBand;
  strstream stSlice[NWindows4BG];

 for (int mm=0; mm<NWindows4BG; mm++) 
   stSlice[mm]<<mName.c_str()<<"slicesFittings at window  "<<mNetWindow.windowBegin(mm+1)<<" - "<<mNetWindow.windowEnd(mm+1);

   stPath<<mName.c_str()<<"pathsFittings ";
   stBand<<mName.c_str()<<"bandFitting ";
    stAmp<<mName.c_str()<<"ampFitting ";
   stReso<<mName.c_str()<<"resoFitting ";

  if (mDrawBandFit){//draw band fitting
    TCanvas* theBandCanvas=new TCanvas(stBand.str(),stBand.str(),20,10,800,600);
 
   theBandCanvas->cd(); 
   bandGraph()->Draw("A*");

   if (mParticleType.id()==-999 ||mParticleType.id()==-2 || mParticleType.id()==-3){
     stLowBand<<stBand.str()<<"lowBG Part";
    TCanvas* theLowBandCanvas=new TCanvas(stLowBand.str(),stLowBand.str(),20,10,800,600);
   theLowBandCanvas->cd(); 
  mBandGraphLowBetaGamma->Draw("A*");
  //   bandGraph()->GetFunction("mBandBetheBlochFcn")->Draw("SAME");
if (mBandFitFcn) mBandFitFcn->Draw("SAME");

     stMiddleBand<<stBand.str()<<"MiddleBG Part";
    TCanvas* theMiddleBandCanvas=new TCanvas(stMiddleBand.str(),stMiddleBand.str(),20,10,800,600);
   theMiddleBandCanvas->cd(); 
  mBandGraphMiddleBetaGamma->Draw("A*");
  //   bandGraph()->GetFunction("mBandBetheBlochFcn")->Draw("SAME");
if (mBandFitFcn) mBandFitFcn->Draw("SAME");




   }

  }


  if (mDrawSlicesFit){ //select ~12 slices from clean windows and draw histo.

 for (int NN=0; NN<mNetWindow.NWindows(); NN++)
 drawSlicesInASegment(stSlice[NN],mNetWindow.windowBegin(NN+1),mNetWindow.windowEnd(NN+1));
  }

  }

//----------------------------------
void StPidAmpBGNet::bookSlicesInASegment(double theSliceWidth, double theSegBegin,double theSegEnd, double& continuationPoint, int& continuationIdx){

 if (theSegBegin>theSegEnd)  {

 continuationPoint=theSegBegin;
 continuationIdx=sliceVector()->size()-1;
 return;
 }

 int i=0;

 segSliceLoop: if ( ((i+1.0)*theSliceWidth+fabs(theSegBegin))<fabs(theSegEnd ) ) {

 double midRig=theSliceWidth*(double(i)+0.5)+fabs(theSegBegin);
 double lowBd=dedxAtBandCenter(midRig)- PathHeight*double(NPaths)/2.0;
 double highBd=dedxAtBandCenter(midRig)+ PathHeight*double(NPaths)/2.0;  


 StPidAmpSlice* ASlice= new StPidAmpSlice(i,midRig,lowBd, highBd, theSliceWidth, mName,&mParticleType);

 sliceVector()->push_back(ASlice);

 i++;

 goto segSliceLoop;

 }

 if (sliceVector()->size()>0){   

StPidAmpSlice* backSlice=sliceVector()->back();

 continuationPoint=backSlice->rightEdge();
 continuationIdx=sliceVector()->size()-1;

 }

}

//----------------------------------
void StPidAmpBGNet::fillNetOut(){
  unsigned    i;
  double bgForMinimumPions=2.87;

  TArrayD bandArray;
  TArrayD ampArray;
  TArrayD linrArray;


  if (mBandParams.size()) {
  bandArray.Set(mBandParams.size());
  for (i=0; i<mBandParams.size(); i++) bandArray.AddAt(mBandParams[i],i);
  }

  if (mAmpParams.size()){
  ampArray.Set( mAmpParams.size());
  for (i=0; i<mAmpParams.size();  i++)  ampArray.AddAt( mAmpParams[i],i);
  }

  if (mResoParams.size()){
  linrArray.Set(mResoParams.size());
  for (i=0; i<mResoParams.size(); i++) linrArray.AddAt(mResoParams[i],i);
  }

  if (mParticleType.id()==-999)
  mNetOut.SetCalibConst( ((*sliceVector())[getSliceIndex(bgForMinimumPions)])->sliceInfo()->meanDedx() );

  mNetOut.SetGeantID(mParticleType.id());
  mNetOut.SetBandParArray(bandArray);
  mNetOut.SetAmpParArray(ampArray);
  mNetOut.SetResoParArray(linrArray);
  mNetOut.SetName((mParticleType.name()).c_str());
  mNetOut.SetTitle((mParticleType.name()).c_str());


}

//----------------------------------
void StPidAmpBGNet::redefineWindow(){

    int i,j; double tempWindowEnd;

    StPidAmpWindow tempWindow;
 
    if (mNetWindow.NWindows()<=NWindows4BG){

    for (i=0; i<(mNetWindow.NWindows()+1);i++)  NSliceAccum[i]=0;



    for (i=0; i<mNetWindow.NWindows();i++){
 
 
  NSlice4Window[i]=int(mNetWindow.length(i+1)/sliceWidth4Window[i]);
  tempWindowEnd=(mNetWindow.cutVector())[i].lowEdge()+NSlice4Window[i]*sliceWidth4Window[i];
    
   tempWindow.addWindow((mNetWindow.cutVector())[i].lowEdge(),tempWindowEnd);

    }

      for (i=1; i<mNetWindow.NWindows();i++)  
      for (j=0; j<i; j++) NSliceAccum[i] +=NSlice4Window[j];
  


     mNetWindow=tempWindow;

    }else{

      gMessMgr->Error()<<"mNetWindow.NWindows()>NWindows4BG "<<endm;
    }


        
}
//----------------------------------
void StPidAmpBGNet::fillSliceWidth(){

  if (mParticleType.id()==-999){
    sliceWidth4Window[0]=SliceWidth;
    sliceWidth4Window[1]=0.03;
    sliceWidth4Window[2]=1.2;
    sliceWidth4Window[3]=2.0;
  }

  else if (mParticleType.id()==-2 || mParticleType.id()==-3) {
      
    sliceWidth4Window[0]=1.2;
    sliceWidth4Window[1]=2.0;
    sliceWidth4Window[2]=1.2; // for e, sliceWidth4Window[2/3] is useless
    sliceWidth4Window[3]=2.0; //but I sill fill it here.
  }


      
  else if (mParticleType.id()==-11 ||
           mParticleType.id()==-12 ||
           mParticleType.id()==-14 ||
           mParticleType.id()==-15 ){


    sliceWidth4Window[0]=SliceWidth;
    sliceWidth4Window[1]=0.05; //no use 
    sliceWidth4Window[2]=1.2;  //no use 
    sliceWidth4Window[3]=2.0;  //no use 
  }

   else if ( mParticleType.id()==-8  ||
             mParticleType.id()==-9  ){

    sliceWidth4Window[0]=SliceWidth;
    sliceWidth4Window[1]=0.05;
    sliceWidth4Window[2]=1.2; //no use 
    sliceWidth4Window[3]=2.0; //no use 
  }

}
