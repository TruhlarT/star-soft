class StMaker;
void rmMaker(const StMaker *top, const char *key);

void runFtsReco( const char* infile="event/sitrver0_10track_1.0pt.event.root",
		 const char* geom="sitrver0",
		 int flag=0)
{

  TString GEOM = geom;

  gROOT->LoadMacro("./bfc.C");

  TString opt;
  //  int fr=1,to=99999;
  int fr=1,to=100;
  int ierr = 0;
  int KNN = 0;

  opt = "in readall ";
  opt += geom; 

  // force by timestamp, consarn it
  //if ( GEOM=="ftsref0" )     opt += " sdt20201210.000007 ";
  if ( GEOM=="ftsref1" )     opt += " sdt20201210.000002 ";
  if ( GEOM=="ftsref2" )     opt += " sdt20201210.000003 ";
  if ( GEOM=="ftsref3" )     opt += " sdt20201210.000004 ";
  if ( GEOM=="ftsref4" )     opt += " sdt20201210.000005 ";
  if ( GEOM=="ftsref5" )     opt += " sdt20201210.000006 ";
  if ( GEOM=="ftsref6" )     opt += " sdt20201210.000007 ";
  if ( GEOM=="ftsref7" )     opt += " sdt20201210.000008 ";
  if ( GEOM=="ftsref8" )     opt += " sdt20201210.000009 ";
  if ( GEOM=="ftsref9" )     opt += " sdt20201210.000010 ";
  if ( GEOM=="ftsref6x")     opt += " sdt20201210.000011 ";
  if ( GEOM=="ftsref6a")     opt += " sdt20201210.000012 ";
  if ( GEOM=="ftsref6y")     opt += " sdt20201210.000013 ";
  if ( GEOM=="ftsref6b")     opt += " sdt20201210.000014 ";
  if ( GEOM=="ftsref6c")     opt += " sdt20201210.000015 ";
  if ( GEOM=="ftsref10")     opt += " sdt20201220.000099 ";
  if ( GEOM=="sitrver0")     opt += " sdt20201220.000100 ";

  opt += " AgML usexgeom FieldOn MakeEvent Stv ";
  opt += "Idst,BAna,l0,Tree,logger,genvtx,tpcDB,bbcSim,emcY2,evout,";
  opt += "-dstout,IdTruth,big,MiniMcMk ";
  opt += " min2trkVtx vfmce mcevent ";
  //  opt += " hitreuseon";

  bfc(-1,opt,infile);


  // chain->SetAttr(".call","SetDebug(1)","St_db_Maker::");
  // chain->SetAttr("makePulls",1,"StiMaker::");
  //  chain->SetAttr("activeFts",1,"Stv");
  chain->SetAttr("activefts",1,"Stv");
  chain->SetAttr("refit",1,"StvMaker::");

  StMaker::lsMakers(chain);

  // StvDebug::SetDebug(11);

  chain->Init();
  //StarMagField::setConstBz(false);

  if (KNN) chain->SetAttr("seedFinders","kn","Stv");

  chain->EventLoop(fr,to);
}

void rmMaker(const StMaker *top, const char *key)
{
  TRegexp rex(key);
  for (int del=1;del;) {
    TDataSetIter   iter((TDataSet*)top,20);
    del=0;
    for(const TDataSet *mk=top;mk;mk = iter.Next()) {
      if(strncmp(".maker",mk->GetTitle(),6)!=0) continue;
      TString ts(mk->ClassName()); ts+="::";
      ts+=mk->GetName();
      if (ts.Index(rex)<0) continue;
      printf("***  Remove %s  *** \n",ts.Data());
      delete mk; del = 1; break;
    }
  }

  printf("***  Maker  %s Not Found ***\n",ts.Data());

}

