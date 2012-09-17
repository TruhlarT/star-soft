// $Id: St2011pubSpinMaker.cxx,v 1.9 2012/09/17 22:05:50 stevens4 Exp $
//
//*-- Author : Jan Balewski, MIT
// 

#include "St2011WMaker.h"

#include "St2011pubSpinMaker.h"

ClassImp(St2011pubSpinMaker)

//_____________________________________________________________________________
//
  St2011pubSpinMaker::St2011pubSpinMaker(const char *name, const char *etaName):StMaker(name){
  wMK=0;HList=0;
  core=name;
  coreTitle=etaName;

  par_QPTlow=0.010;
  par_QPThighET0=25; 
  par_QPThighET1=50; 
  par_QPThighA=0.08; 
  par_QPThighB=0.0013; 
  par_leptonEta1=-1.; par_leptonEta2=1.;
  par_useNoEEMC=0;
  
  parE_QPTlow=0.4;
  parE_QPThighET0=25; 
  parE_QPThighET1=50; 
  parE_QPThighA=1.8; 
  parE_QPThighB=0.0013;
  parE_leptonEta1=0.7; parE_leptonEta2=2.5;

 }


//_____________________________________________________________________________
//
Int_t 
St2011pubSpinMaker::Init(){
  assert(wMK);
  assert(HList);
  initHistos();
  return StMaker::Init();
}


//_____________________________________________________________________________
//
Int_t 
St2011pubSpinMaker::FinishRun  (int runNo){
  return kStOK;
}

//_____________________________________________________________________________
//
Int_t 
St2011pubSpinMaker::InitRun  (int runNo){

  //j1  sprintf(txt,"bXing= bx48+off=%d",spinDb->BX48offset());
  //j1 hA[3]->GetXaxis()->SetTitle(txt);

  //j1 sprintf(txt,"bXing= bx7+off=%d",spinDb->BX7offset());
  //j1 hA[4]->GetXaxis()->SetTitle(txt);

  LOG_INFO<<Form("::InitRun(%d) done, W-spin sorting  params: exclude |Q/PT| < %.2f OR |Q/PT| above line %.3f*(ET-%.1f)-%6e if ET<%.1f, for AL use leptonEta in[%.1f,%.1f] useNoEEMC=%d", runNo,
		 par_QPTlow,par_QPThighET0, par_QPThighA ,par_QPThighB,par_QPThighET1,par_leptonEta1, par_leptonEta2,par_useNoEEMC
		 )<<endm;	 
  return kStOK;
}

//_____________________________________________________________________________
//
Int_t 
St2011pubSpinMaker::Make(){

  bXingSort();
  bXingSortEndcap();
  return kStOK;
}

//_____________________________________________________________________________
//
void 
St2011pubSpinMaker::bXingSort(){
  //has access to whole W-algo-maker data via pointer 'wMK'
  
  hA[0]->Fill("inp",1.);
 
  if((wMK->wEve->l2bitRnd || wMK->wEve->l2bitET)==0) return;
  if(wMK->wEve->vertex.size()<=0) return; 
  //......... require: L2BW-trig (ET or rnd) & vertex is reasonable .......
  
  int bx48=wMK->wEve->bx48;
  int bx7=wMK->wEve->bx7;
  int bxStar48=wMK->wEve->bxStar48;
  int bxStar7=wMK->wEve->bxStar7;

  if(bxStar48!=bxStar7) {
   printf("BAD bx7=%d bx48=%d del=%d\n",bx7,bx48,bxStar48-bxStar7);
   hA[0]->Fill("badBx48",1.);
   return; // both counters must be in sync
  }

  //remove events tagged as Zs
  if(wMK->wEve->zTag) return;
  hA[0]->Fill("noZ",1.);

  hA[1]->Fill(bx48);
  hA[2]->Fill(bx7);

  hA[3]->Fill(bxStar48);
  hA[4]->Fill(bxStar7);

  int spin4=wMK->wEve->spin4;
  hA[5]->Fill(bxStar7,spin4);

  float par_maxDsmThr=58;
  float par_myET=25; // monitoring cut
  if( wMK->wEve->l2bitRnd) { // lumi monitor BHT3-random    
    // avoid too much energy - can be W-events (1/milion :)
    if(wMK-> wEve->bemc.maxHtDsm<par_maxDsmThr)  { 
      hA[6]->Fill(spin4);  hA[0]->Fill("BG1",1.);}
    //removed veto of random bits here in previous version JS
  }
  
  if( wMK->wEve->l2bitET==0) return; 
  //..... it is guaranteed ..... L2W-ET>13 did fired  ......
  
  
  // search for  Ws ............
  for(uint iv=0;iv<wMK->wEve->vertex.size();iv++) {
    WeveVertex &V=wMK->wEve->vertex[iv];

    if(iv>0) continue; //temp skip not-highest-rank vertex JS

    for(uint it=0;it<V.eleTrack.size();it++) {
      WeveEleTrack &T=V.eleTrack[it];
      if(T.pointTower.id<=0) continue; //skip endcap towers

      /* Collect QCD background for lumi monitors */
      float frac24=T.cluster.ET/(T.cl4x4.ET);
      if(iv==0 && it==0 && frac24<wMK->par_clustFrac24) {
	hA[31]->Fill(T.cluster.ET);
	if( T.cluster.ET <20. ) { hA[7]->Fill(spin4);  hA[0]->Fill("BG2",1.);}
      }

      int iQ=0; // plus
      float p_Q=T.prMuTrack->charge();
      if( p_Q<0 ) iQ=1;// minus
      float ET=T.cluster.ET;
      
      if(T.isMatch2Cl==false) continue;
      assert(T.cluster.nTower>0); // internal logical error
      assert(T.nearTotET>0); // internal logical error
      
      // high-pT QCD condition here
      if( T.cluster.ET/T.nearTotET < wMK->par_nearTotEtFrac && T.sPtBalance < wMK->par_ptBalance) //not isolated && doesn't pass sPtBal
	{
	  hA[22+iQ]->Fill(spin4,ET);
	  if(T.prMuTrack->eta()>par_leptonEta1 && T.prMuTrack->eta()<par_leptonEta2 && ET>25 && ET<50) //kinematic conditions
	    hA[20+iQ]->Fill(spin4);
	}
      
      //put final W cut here
      bool isW= T.cluster.ET /T.nearTotET> wMK->par_nearTotEtFrac;  // near cone
      if(par_useNoEEMC) 
	isW=isW && T.sPtBalance_noEEMC>wMK->par_ptBalance; // awayET
      else
	isW=isW && T.sPtBalance>wMK->par_ptBalance; // awayET
    
      if(!isW) { // AL(QCD)
	if(ET>15 &&ET<20 ) hA[16+iQ]->Fill(spin4);
	continue;
      }

      hA[0]->Fill("Wcut",1.);
  
      // allows spin specific cuts on eta
      if(T.prMuTrack->eta()<par_leptonEta1) continue;
      if(T.prMuTrack->eta()>par_leptonEta2) continue;
      hA[0]->Fill("eta",1.);

      //::::::::::::::::::::::::::::::::::::::::::::::::
      //:::::accepted W events for x-section :::::::::::
      //::::::::::::::::::::::::::::::::::::::::::::::::

      if(ET>par_myET) hA[0]->Fill("W25",1.);
      float q2pt=T.prMuTrack->charge()/T.prMuTrack->pt();
      if(ET>par_myET) hA[8]->Fill(q2pt);
      hA[9]->Fill(ET,q2pt);
      
      // apply cut on reco charge
      if( fabs(q2pt)< par_QPTlow) continue;
      if(ET>par_myET) hA[0]->Fill("Qlow",1.);

      if(par_QPTlow>0) { // abaility to skip all Q/PT cuts
	if( fabs(q2pt)< par_QPTlow) continue;
	float highCut=par_QPThighA - (ET-par_QPThighET0)*par_QPThighB;
	// printf("fff ET=%f q2pr=%f highCut=%f passed=%d\n",ET, q2pt,highCut,fabs(q2pt)<highCut);
	if( ET>par_myET && ET<par_QPThighET1 && fabs(q2pt)>highCut) continue;
      }

      if(ET>par_myET) {
	hA[0]->Fill("Qhigh",1.);
	if(p_Q>0) hA[0]->Fill("Q +",1.);
	else  hA[0]->Fill("Q -",1.);
      }

     
      hA[10+iQ]->Fill(ET);
      if(ET>25 &&ET<50 ) {
	hA[12+iQ]->Fill(spin4);
	hA[29+iQ]->Fill(T.prMuTrack->eta()); 
      }
      if(ET>32 &&ET<44 ) hA[14+iQ]->Fill(spin4);
     
      hA[18+iQ]->Fill(spin4,ET);	 
     
    } // end of loop over tracks
  }// end of loop ove vertices

}

//_____________________________________________________________________________
//
void 
St2011pubSpinMaker::bXingSortEndcap(){
  //has access to whole W-algo-maker data via pointer 'wMK'
  
  hE[0]->Fill("inp",1.);
 
  if((wMK->wEve->l2EbitRnd || wMK->wEve->l2EbitET)==0) return;
  if(wMK->wEve->vertex.size()<=0) return; 
  //......... require: L2EW-trig (ET or rnd) & vertex is reasonable .......
  
  int bx48=wMK->wEve->bx48;
  int bx7=wMK->wEve->bx7;
  int bxStar48=wMK->wEve->bxStar48;
  int bxStar7=wMK->wEve->bxStar7;

  if(bxStar48!=bxStar7) {
   printf("BAD bx7=%d bx48=%d del=%d\n",bx7,bx48,bxStar48-bxStar7);
   hE[0]->Fill("badBx48",1.);
   return; // both counters must be in sync
  }

  //remove events tagged as Zs
  if(wMK->wEve->zTag) return;
  hE[0]->Fill("noZ",1.);

  hE[1]->Fill(bx48);
  hE[2]->Fill(bx7);

  hE[3]->Fill(bxStar48);
  hE[4]->Fill(bxStar7);

  int spin4=wMK->wEve->spin4;
  hE[5]->Fill(bxStar7,spin4);

  float par_maxDsmThr=58;
  float par_myET=25; // monitoring cut
  if( wMK->wEve->l2EbitRnd) { // lumi monitor BHT3-random    
    // avoid too much energy - can be W-events (1/milion :)
    if(wMK-> wEve->etow.maxHtDsm<par_maxDsmThr)  { 
      hE[6]->Fill(spin4);  hE[0]->Fill("BG1",1.);}
  }
  
  if( wMK->wEve->l2EbitET==0) return; 
  //..... it is guaranteed ..... L2EW-ET>11? did fired  ......
  
  
  // search for  Ws ............
  for(uint iv=0;iv<wMK->wEve->vertex.size();iv++) {
    WeveVertex &V=wMK->wEve->vertex[iv];

    if(iv>0 || V.rank<=0) continue; //temp skip not-highest-rank vertex JS

    for(uint it=0;it<V.eleTrack.size();it++) {
      WeveEleTrack &T=V.eleTrack[it];
      if(T.pointTower.id>=0) continue; //skip barrel towers

      /* Collect QCD background for lumi monitors */
      float frac24=T.cluster.ET/(T.cl4x4.ET);
      if(iv==0 && it==0 && frac24<wMK->par_clustFrac24) {
	hE[31]->Fill(T.cluster.ET);
	if( T.cluster.ET <20. ) { hE[7]->Fill(spin4);  hE[0]->Fill("BG2",1.);}
      }

      if(T.isMatch2Cl==false) continue;
      assert(T.cluster.nTower>0); // internal logical error
      assert(T.nearTotET>0); // internal logical error

      int iQ=0; // plus
      float p_Q=T.prMuTrack->charge();
      if( p_Q<0 ) iQ=1;// minus
      float ET=T.cluster.ET;
      
      //put final W cut here
      bool isW= T.cluster.ET/T.nearTotET > wMK->parE_nearTotEtFrac; // near cone
      isW=isW && ((T.esmdEsum7[0]+T.esmdEsum7[1])/(T.esmdE[0]+T.esmdE[1]) > wMK->parE_smdRatio); // smdRatio
      isW=isW && T.sPtBalance2>wMK->parE_ptBalance; // awayET
    
      if(!isW) { // !!!! This is not all QCD for the endcap !!!!
	if(ET>15 && ET<20 ) hE[16+iQ]->Fill(spin4);
	continue;
      }

      hE[0]->Fill("Wcut",1.);
 
      // allows spin specific cuts on eta
      if(T.prMuTrack->eta()<parE_leptonEta1) continue;
      if(T.prMuTrack->eta()>parE_leptonEta2) continue;
      hE[0]->Fill("eta",1.);

      //::::::::::::::::::::::::::::::::::::::::::::::::
      //:::::accepted W events for x-section :::::::::::
      //::::::::::::::::::::::::::::::::::::::::::::::::

      if(ET>par_myET) hE[0]->Fill("W25",1.);
      float q2pt=T.prMuTrack->charge()/T.prMuTrack->pt();
      if(ET>par_myET) hE[8]->Fill(q2pt);
      hE[9]->Fill(ET,q2pt);

      // new charge rejection Q*ET/PT
      float hypCorr = q2pt*(T.cluster.ET);
      if(parE_QPTlow>0) { // abaility to skip all Q/PT cuts
	if( fabs(hypCorr) < parE_QPTlow) continue;
	if(ET>par_myET) hE[0]->Fill("Qlow",1.);
	if( fabs(hypCorr) > parE_QPThighA) continue;
      }

      if(ET>par_myET) {
	hE[0]->Fill("Qhigh",1.);
	if(p_Q>0) hE[0]->Fill("Q +",1.);
	else  hE[0]->Fill("Q -",1.);
      }
     
      hE[10+iQ]->Fill(ET);
      if(ET>25 &&ET<50 ) {
	hE[12+iQ]->Fill(spin4);
	hE[29+iQ]->Fill(T.prMuTrack->eta()); 
      }
      if(ET>32 &&ET<44 ) hE[14+iQ]->Fill(spin4);
     
      hE[18+iQ]->Fill(spin4,ET);	 
     
    } // end of loop over tracks
  }// end of loop ove vertices

}

// $Log: St2011pubSpinMaker.cxx,v $
// Revision 1.9  2012/09/17 22:05:50  stevens4
// exclude not-highest rank vertex until jet issue is resolved
//
// Revision 1.8  2012/09/17 03:29:30  stevens4
// Updates to Endcap algo and Q*ET/PT charge separation
//
// Revision 1.7  2012/08/31 20:10:52  stevens4
// switch to second EEMC background using both isolation and sPt-Bal (for mirror symmetry (also adjust eta binning)
//
// Revision 1.6  2012/08/28 14:28:27  stevens4
// add histos for barrel and endcap algos
//
// Revision 1.5  2012/08/21 21:28:22  stevens4
// Add spin sorting for endcap Ws
//
// Revision 1.4  2012/08/07 21:06:38  stevens4
// update to tree analysis to produce independent histos in a TDirectory for each eta-bin
//
// Revision 1.3  2012/07/12 20:49:21  balewski
// added spin info(star: bx48, bx7, spin4) and maxHtDSM & BTOW to Wtree
// removed dependence of spinSortingMaker from muDst
// Now Wtree can be spin-sorted w/o DB
// rdMu.C & readWtree.C macros modified
// tested so far on real data run 11
// lot of misc. code shuffling
//
// Revision 1.2  2012/06/18 18:28:01  stevens4
// Updates for Run 9+11+12 AL analysis
//
// Revision 1.1  2011/02/10 20:33:25  balewski
// start
//
