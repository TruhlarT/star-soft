// Conver Zebra file into ROOT format

TH2F *h12 = 0;
TH2F *h31 = 0;
TH2F *h23 = 0;

TH2F *hYX[3] = { 0, 0, 0};


//
// Want to see the correlation between hits in sensor 1 vs 2, 2 vs 3 and 3 vs 1.
// This will inform whether we can develop a faster seed finding algorithm which
// takes advantage of this apriori knowledge about the 
//


void runFtsSiSim(const char* _file= "geant/sitrver0_10track_1.0pt.fzd", 
unsigned int nEvent=10) 
{

  TString _geom = "sitrver0";

  TString _chain = Form("fzin %s eefs geantout event evout geantout ReverseField agml usexgeom bigbig debug ",_geom.Data());
 
   gROOT->LoadMacro("bfc.C");
   bfc(-1, _chain, _file );

   // gSystem->Load ( "libStFtsFastSimulatorMaker.so");
   gSystem->Load ( "libStFtsFastSimulatorMaker.so");

   StFtsSiFastSimulatorMaker* sisim = new StFtsSiFastSimulatorMaker;

   sisim->setPointHits();

   chain->AddAfter("0Event", sisim );
   chain->Init();

   //chain->EventLoop(nEvent); 

  for ( int i=0;i<nEvent;i++ )
  {

     chain->Clear();
     if ( kStOK != chain->Make() ) break;
#if 0
     new TBrowser();
     break;
#endif

     StEvent* event = (StEvent*) chain->GetDataSet("StEvent");
     if ( 0==event ) {
        cout << "No event found" << endl;
     }
     StRnDHitCollection* rndCollection = event->rndHitCollection();
     if (0==rndCollection ) {
        cout << "No collection found" << endl;
	continue;
     }
     const StSPtrVecRnDHit& hits = rndCollection->hits();
     cout<<"nnhhiittss== "<<hits.size()<<endl;
     for ( unsigned int ihit = 0; ihit<hits.size(); ihit++ )
     {
        StRnDHit* hit = hits[ihit];
        if ( 0==hit ) {
           cout << "No hit found" << endl;
        }

        cout << "disk=" <<hit->layer() << " "; hit->Print();
      }
    }

}
