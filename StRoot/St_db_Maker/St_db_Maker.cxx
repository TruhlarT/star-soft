//*-- Author :    Valery Fine(fine@bnl.gov)   10/08/98 
// $Id: St_db_Maker.cxx,v 1.44 2001/03/07 20:43:46 perev Exp $
// $Log: St_db_Maker.cxx,v $
// Revision 1.44  2001/03/07 20:43:46  perev
// assert for wrong time added
//
// Revision 1.43  2001/02/18 20:09:58  perev
// Distinction between UNIX FS objects and MySql added
//
// Revision 1.42  2001/01/31 17:12:05  fisyak
// Introduce year-2b for STAR 2001
//
// Revision 1.41  2000/11/07 15:02:05  fisyak
// Fix typo
//
// Revision 1.40  2000/11/07 01:48:25  fisyak
// Add one more protection agaist fDataBase==NULL
//
// Revision 1.39  2000/11/02 16:02:20  fisyak
// Jeff request to allow a top level directory (e.g. database) have ID=0 which is ok
//
// Revision 1.38  2000/09/16 02:45:09  didenko
// commit Victor's changes
//
// Revision 1.37  2000/07/14 02:39:21  perev
// SetMaxEntryTime method added
//
// Revision 1.36  2000/06/29 15:58:04  perev
// bug in Init fixed, wrong {}
//
// Revision 1.35  2000/06/26 20:58:41  perev
// multiple DBs
//
// Revision 1.33  2000/06/20 20:39:49  fisyak
// Add debug print out
//
// Revision 1.32  2000/05/20 01:00:43  perev
// SetFlavor() added
//
// Revision 1.31  2000/05/12 15:10:19  fine
// new Table macro introduced
//
// Revision 1.30  2000/05/11 01:27:54  fisyak
// Change y1h from 03/01/2000 to 05/01/2000
//
// Revision 1.29  2000/04/14 14:49:59  perev
// Communication via descriptor struct -> class
//
// Revision 1.28  2000/04/13 02:58:47  perev
// Method Save is added & default CintDB loaded if exists
//
// Revision 1.27  2000/04/07 15:44:42  perev
// Error return when MySQL is not available
//
// Revision 1.26  2000/03/23 14:55:55  fine
// Adjusted to libSTAR and ROOT 2.24
//
// 
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// St_db_Maker class for Makers                                      //
//                                                                      //
// This class is C++ implementation of the Begin_html <a href="http://www.rhic.bnl.gov/afs/rhic/star/doc/www/packages_l/pro/pams/db/sdb/doc/index.html">Simple Database Manager</a> End_html    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
#define MYSQLON 1999

#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <time.h>
#include "TError.h"
#include "TBrowser.h"
#include "TDatime.h"
#include "TRegexp.h"
#include "TInterpreter.h"
#include "TFile.h"
#include "TSystem.h"
#include "St_db_Maker.h"
#include "TDataSetIter.h"
#include "TFileSet.h"
#include "St_XDFFile.h"
#include "StTree.h"
#include "TTableDescriptor.h"
#include "TTable.h"

#include "StDbBroker/StDbBroker.h"

static Int_t AliasDate(const char *alias);
static Int_t AliasTime(const char *alias);
static time_t mkgmtime(struct tm *gt);
static time_t mkgmt(int date,int time);

static const char *aliases[]={
"sd97",   "sd98",   "year_1a","year_1b","year_1c",
"es99",   "er99",   "dc99"   ,"year_1d","year_1e",
"year_1h","year_2a", "year_2b", 0};   

static const int   dates[]=  {
19970101, 19980101, 19990101, 19990501, 19991001,
19990615, 19990616, 19991206, 19991101, 19991201,
20000501, 20010610, 20010501, 0};
static const int   times[]=  {
       0,        0,        0,        0,        0,
       0,   120000,    80000,        0,        0,
       0,        0,        0,        0};

enum eDBMAKER {kUNIXOBJ = 0x2000};

/////////////////////////////////////////////////////////////////////////
//                                          
//  Class St_dbConfig wraps the STAF table dbConfig 
//  It has been generated by automatic. Please don't change it "by hand" 
//                                          
/////////////////////////////////////////////////////////////////////////  
                                            
TableClassImpl(St_dbConfig,dbConfig_st)

//_________________________ class St_Validity ____________________________________
class St_ValiSet : public TDataSet{
public:
   TDatime fTimeMin;
   TDatime fTimeMax;
   TDataSet *fDat;
   Int_t  fMod;
   St_ValiSet(const char *name,TDataSet *parent);
   virtual ~St_ValiSet(){};
   virtual void ls(Int_t lev=1);
           void Modified(int m=1){fMod=m;}
          Int_t IsModified(){return fMod;}
};

//_____________________________________________________________________________
St_ValiSet::St_ValiSet(const char *name,TDataSet *parent): TDataSet(name,parent)
{
  SetTitle(".Val");
  fTimeMin.Set(kMaxTime,0);
  fTimeMax.Set(kMinTime,0);
  fDat =0;
  Modified(0);
}

//_____________________________________________________________________________
void St_ValiSet::ls(Int_t lev)
{
  printf("  %s.Validity = %s ",GetName(),fTimeMin.AsString());
  printf(" <-> %s\n",     fTimeMax.AsString());
  if (fDat) printf("  Contains DataSet %s\n",fDat->GetName());
  TDataSet::ls(lev);
}

//__________________________ class St_db_Maker  ____________________________
ClassImp(St_db_Maker)
//_____________________________________________________________________________
St_db_Maker::St_db_Maker(const char *name
, const char *dir0
, const char *dir1
, const char *dir2
, const char *dir3
)
:StMaker(name)
{

   fDirs[0] = dir0;
   fDirs[1] = dir1;
   fDirs[2] = dir2;
   fDirs[3] = dir3;
   fDirs[4] = "";

   fDBBroker = 0;

   fHierarchy = 0;
   fIsDBTime = 0;
     
   fDataBase = 0;
   fUpdateMode = 0;
   fMaxEntryTime = 0;
}
//_____________________________________________________________________________
St_db_Maker::~St_db_Maker(){
}
//_____________________________________________________________________________
Int_t St_db_Maker::Init()
{
   TDataSet *fileset;
   TString dir;

   fDataBase=0;
   for (int idir=0; !fDirs[idir].IsNull(); idir++) {//loop over dirs

     dir = fDirs[idir];
     gSystem->ExpandPathName(dir);
     if (strncmp("MySQL:",  (const char*)dir,6)==0){
       fileset = OpenMySQL(((const char*)dir)+6);
       if (!fileset) return kStErr;
       fileset->Pass(PrepareDB,0);
     } else {

// 		recreate a memory resided data-structure
       fileset = new TFileSet(dir,gSystem->BaseName(dir));
       if (!fileset->First()) {delete fileset; fileset = 0; continue;}
       fileset->Purge(); 
       fileset->Sort(); 
       fileset->Pass(PrepareDB,&dir);
       fileset->Purge(); 
     }
     if (fDataBase) {
       assert(strcmp(fDataBase->GetName(),fileset->GetName())==0);
       fDataBase->Update(fileset); delete fileset;
       } else          {fDataBase = fileset; }
   }

   if (fDataBase) {
     AddData(fDataBase);
     SetOutputAll(fDataBase,2); //  
     
     if (Debug()>1) fDataBase->ls("*");
   }
   OnOff();
   return 0;
}
//_____________________________________________________________________________
Int_t St_db_Maker::Make()
{

  TDatime td = GetDateTime();
  assert(td.GetDate() < 20330101);
  fUpdateMode = 1;
  UpdateDB(fDataBase);  
  fUpdateMode = 0;
  return kStOK;
}

//_____________________________________________________________________________
TDatime St_db_Maker::Time(const char *filename)
{
  int lfilename,lname,idate,itime;

  TDatime time; time.Set(kMaxTime,0);

  lfilename = strlen(filename);
  lname = strcspn(filename,".");
  if (lname+2>lfilename) return time;
  idate = ::AliasDate(filename+lname+1);
  itime = ::AliasTime(filename+lname+1);

  if (idate) { time.Set(idate,itime);return time;}

  if (lname+18 <= lfilename    &&
      filename[lname+0 ]=='.'  && 
      filename[lname+9 ]=='.'  && 
      filename[lname+16]=='.'  ) {// file name format:  <name>.YYYYMMDD.hhmmss.<ext>
       idate  = atoi(filename+lname+ 1); 
       itime  = atoi(filename+lname+10);
   } else {			   // file name format:  <name>.<ext>
       idate = kMinTime;
       itime = 0;
   }
   time.Set(idate,itime); return time;

}

int St_db_Maker::Kind(const char *filename)
{
   int lfilename;
   
   lfilename = strlen(filename);
   if (!strcmp(filename+lfilename-4,".xdf" )) return 1;
   if (!strcmp(filename+lfilename-2,".C"   )) return 2;
   if (!strcmp(filename+lfilename-2,".c"   )) return 2;
   if (!strcmp(filename+lfilename-5,".root")) return 3;
   return 0;
}
//_____________________________________________________________________________
TDataSet *St_db_Maker::OpenMySQL(const char *dbname)
{
   int nrows,irow,jrow;
   dbConfig_st *thy,*ihy,*jhy;
   TDataSet *top,*node,*ds;
   
   fDBBroker  = new StDbBroker();
   if (fMaxEntryTime) fDBBroker->SetProdTime(fMaxEntryTime);

//   if (fDBBroker->IsZombie()) {
//     Warning("OpenDB","***Can not open MySQL DB %s ***");
//     return 0;
//   }

   if (*GetFlavor()) {
      if (GetDebug()) 
         printf("<St_db_Maker::OpenMySQL> Flavor %s is set\n",GetFlavor());
      fDBBroker->SetFlavor(GetFlavor());
   }

   TString ts(dbname); ts+="_hierarchy";
   fHierarchy = new St_dbConfig((char*)ts.Data());    
   assert(fHierarchy);
   thy = fDBBroker->InitConfig(dbname,nrows);
   if (!thy || !nrows){
     Warning("OpenMySQL","***Can not open MySQL DB %s ***",dbname);
     return 0;}


   fHierarchy->Adopt(nrows,thy);
   if (GetDebug()>1)  fHierarchy->Print(0,nrows);  

   top = new TDataSet(thy->parname);
   top->SetTitle("directory");

   TDataSet **dss = new TDataSet*[nrows];
   memset(dss,0,nrows*sizeof(void*));

//		First pass: directories only
   for (irow=0,ihy=thy; irow <nrows ; irow++,ihy++)
   {
     if (strcmp(ihy->tabtype,".node")==0) {// new node
       ds = new TDataSet(ihy->tabname);
       ds->SetTitle("directory");
     } else {				// new table
       const char *ty = ihy->tabtype;
       if (ty[0]=='.') ty++; 
       ds = TTable::New(ihy->tabname,ty,0,0);
       if (!ds) {
         Warning("OpenMySQL","Unknown table %s/%s.%s",ihy->parname,ihy->tabname,ihy->tabtype); continue;}
     }
     if (ds) ds->SetUniqueID(ihy->tabID);   
     dss[irow] = ds;   
   }

//		Second pass: set relations
   for (irow=0,ihy=thy; irow <nrows ; irow++,ihy++)
   {
     ds = dss[irow]; if (!ds) 			continue;
     if (strcmp(ihy->parname,top->GetName())==0) top->Add(ds);
     if(ds->GetParent()) 			continue;
     for (jrow=0,jhy=thy; jrow <nrows ; jrow++,jhy++)
     {    
       if (jrow==irow)				continue;
       if (ihy->parID != jhy->tabID)		continue;
       if (strcmp(".node"     ,jhy->tabtype))	continue;
       if (strcmp(ihy->parname,jhy->tabname))	continue;
       node = dss[jrow]; if (!node)		continue;
       node->Add(ds); break;
     }/*end j for*/ 
     if (ds->GetParent()) 			continue;
     delete ds; dss[irow]=0;
     Error("OpenMySQL","WRONG parent %s/%s\n",ihy->parname,ihy->tabname);
   }/*end i for*/
   delete [] dss;
//   top->ls(99);
   return top;   
}


//_____________________________________________________________________________
TDataSet *St_db_Maker::UpdateDB(TDataSet* ds)
{ 
  if(!ds) return 0;
#ifdef __CC5__
  ds->Pass(&UpdateDB,this);
#else
  ds->Pass(UpdateDB,this);
#endif
  return ds;
}
//_____________________________________________________________________________
int St_db_Maker::UpdateTable(UInt_t parId, TTable* dat, TDatime val[2] )
{

  assert(fDBBroker);assert(dat);
  fDBBroker->SetDateTime(GetDateTime().GetDate(),GetDateTime().GetTime());
  TTableDescriptor *rowTL = ((TTable*)dat)->GetRowDescriptors();
#if 0
  int nElements = rowTL->GetNRows();

  tableDescriptor_st *elem= rowTL->GetTable();

  assert(sizeof(StDbBroker::Descriptor)==sizeof(tableDescriptor_st));

  StDbBroker::Descriptor *descriptor = (StDbBroker::Descriptor *)elem;
  fDBBroker->SetDictionary(nElements,descriptor);
#else
  fDBBroker->SetDictionary(rowTL);
#endif
  fDBBroker->SetTableName (dat->GetName());
  fDBBroker->SetStructName(dat->GetTitle());
  fDBBroker->SetStructSize(dat->GetRowSize());

// 		if descriptor filled, no need for newdat
  void *dbstruct = fDBBroker->Use(dat->GetUniqueID(),parId);
  if (!dbstruct) {
    Warning("UpdateTable","Table %s.%s Not FOUND",dat->GetName(),dat->GetTitle());
    return 1;
  }

  int nRows = fDBBroker->GetNRows();
//		Adopt DB data in the new TTable
  dat->Adopt(nRows,dbstruct);
//  dat->Print(0,1);
  val[0].Set(fDBBroker->GetBeginDate(),fDBBroker->GetBeginTime());
  val[1].Set(fDBBroker->GetEndDate  (),fDBBroker->GetEndTime  ());

//  printf("BegVal=%s\n",val[0].AsString());
//  printf("EndVal=%s\n",val[1].AsString());
  return 0;

}

 //_____________________________________________________________________________
EDataSetPass St_db_Maker::UpdateDB(TDataSet* ds,void *user )
{
  TDataSet *left,*par;
  St_ValiSet *val;
  TDatime valsCINT[2],valsSQL[2];
   
  if (strcmp(".Val",ds->GetTitle()))		return kContinue;
//
//	It is our place.
  val = (St_ValiSet*)ds;    
  St_db_Maker *mk = (St_db_Maker*)user;    
  if (mk->fUpdateMode && !val->IsModified()) 	return kPrune;

  TDatime currenTime = mk->GetDateTime();
  UInt_t uevent = currenTime.Get();

// 		Check validity
    if (val->fTimeMin.Get() <= uevent 
     && val->fTimeMax.Get() >  uevent) 		return kPrune;

//	Start loop
  


  val->fTimeMin.Set(kMaxTime,0);
  val->fTimeMax.Set(kMinTime,0);

  par = ds->GetParent();
  par->Remove(val->fDat);

  int kase = 0;
  if (mk->fDBBroker && val->fDat && par->GetUniqueID() < kUNIXOBJ) {	// Try to load from MySQL
    int ierr = mk->UpdateTable(par->GetUniqueID(),(TTable*)val->fDat, valsSQL );
    if (!ierr) kase = 1;
  }
  
  left = mk->FindLeft(val,valsCINT);
  if (left) kase+=2;
  TDataSet *newGuy=0;
SWITCH:  switch (kase) {
  
    case 0:   break;  
    
    case 1:   val->fTimeMin = valsSQL[0];  val->fTimeMax = valsSQL[1]; 
              ds->GetParent()->AddFirst(val->fDat);
              kase=4; goto SWITCH;

    case 2:   newGuy = mk->LoadTable(left);
              if (!val->fDat) { val->fDat = newGuy;}
              else            { val->fDat->Update(newGuy); delete newGuy;}
              val->fTimeMin = valsCINT[0];  val->fTimeMax = valsCINT[1];
              ds->GetParent()->AddFirst(val->fDat);
              kase=4; goto SWITCH;
  
    case 3:   if (valsCINT[0].Get()>=valsSQL[0].Get()) {
                kase = 2; 
                if (valsCINT[1].Get()>valsSQL[1].Get()) valsCINT[1] = valsSQL[1];   
              } else {
                kase = 1;               
                if (valsSQL[1].Get()>valsCINT[1].Get()) valsSQL[1] = valsCINT[1];   
              }
              goto SWITCH;

    case 4:   assert((val->fTimeMin.Get()<= uevent) && (val->fTimeMax.Get()>uevent));
              break;

    default:  assert(0);
  }
  val->Modified(1);  
  return kPrune;  
}
//_____________________________________________________________________________
TDataSet *St_db_Maker::FindLeft(St_ValiSet *val, TDatime vals[2])
{

//	Start loop
  UInt_t uevent = GetDateTime().Get();
  
  vals[0].Set(kMinTime,0);
  vals[1].Set(kMaxTime,0);
  UInt_t utmp,udifleft=(UInt_t)(-1),udifrite=(UInt_t)(-1); 
  TDataSet *left=0,*rite=0,*set=0; 
  TListIter next(val->GetList());
  while ((set = (TDataSet*)next())) {
    const char *filename = set->GetName();
    UInt_t ucur = St_db_Maker::Time(filename).Get();
    if (uevent < ucur) 
    { utmp = ucur - uevent;
      if (utmp <= udifrite) { udifrite=utmp; rite=set;}
    }else{
      utmp = uevent - ucur;
      if (utmp <= udifleft) { udifleft=utmp; left=set;}
    }
  }// end while


  if (left) vals[0] = St_db_Maker::Time(left->GetName());
  if (rite) vals[1] = St_db_Maker::Time(rite->GetName());
  return left;
}


//_____________________________________________________________________________
TDataSet *St_db_Maker::LoadTable(TDataSet* left)
{
  TFile *tf =0;
  TObject *to =0;
  TString command;  
  TDataSet *newdat = 0;
  TString dbfile = left->GetTitle()+5;


  TDataSet *ds = left->GetParent();
  ds = ds->GetParent();
  dbfile += strchr(strstr(ds->Path(),"/.data/")+7,'/');
  dbfile += "/"; dbfile += left->GetName();
  gSystem->ExpandPathName(dbfile);
  
  int kind = Kind(left->GetName());
  switch (kind) {
  
    case 1: // .xdf file
    newdat = St_XDFFile::GetXdFile(dbfile);assert (newdat);
    if (GetDebug()) printf("Load XdfFile:   %s\n",(const char*)dbfile);
    break;

    case 2: // .C file

      command = ".L "; command += dbfile;
      if (GetDebug()) printf("LoadTable: %s\n",(const char*)command);
      gInterpreter->ProcessLine(command);
      newdat = (TDataSet *) gInterpreter->Calc("CreateTable()");
      command.ReplaceAll(".L ",".U "); 
      gInterpreter->ProcessLine(command);

      break;

    case 3: // .root file
    
      tf = new TFile(dbfile);
      to = StIO::Read (tf, "*");
      delete tf;
      if (!to) break;
      if (GetDebug()) printf("Load TFile:   %s\n",(const char*)dbfile);
      if (strcmp(to->ClassName(),"StIOEvent")==0) to = ((StIOEvent*)to)->fObj;
      if (!to) break;
      if (to->InheritsFrom(TDataSet::Class())) 	{
        newdat = (TDataSet*)to; 
      } else 					{ 
	newdat = new TObjectSet(to->GetName());
	newdat->SetObject(to);
      }
    break;
    
    default: assert(0);
  }
  if (newdat) newdat->SetUniqueID(kUNIXOBJ+kind);

  return newdat;
}

//_____________________________________________________________________________
EDataSetPass St_db_Maker::PrepareDB(TDataSet* ds, void *user)
{
  TDataSet *set;
  St_ValiSet *pseudo;
  const char *dsname,*filename,*dot;     
  char psname[100];
  int ldsname,lpsname;
  
  TList *list = ds->GetList();
  if (!list) return kContinue;
  if (strcmp("directory",ds->GetTitle())) return kPrune;
  dsname = ds->GetName(); ;
  if (!strcmp("CVS",dsname)) { delete ds; return kPrune;}
  ldsname= strlen(dsname);

  TString newTitle = "file ";
  if (user) newTitle += *((TString*)user);

//	Start loop
  pseudo = 0; psname[0]='.'; psname[1]=0;
  TListIter next(list);
  while ((set = (TDataSet*)next())) {
    filename = set->GetName();
    int isSql =(set->InheritsFrom(TTable::Class())!=0);
    if (isSql) {			// Sql object
      lpsname = strlen(filename); 
    } else {				// Cint object
      if (strncmp("file",set->GetTitle(),4))	continue;  
      if (!(dot = strchr(filename,'.'))) 	continue;
      if (!Kind(filename)){ delete set;		continue;}
      set->SetTitle(newTitle);
      lpsname = dot - filename;
    }
    if (strncmp(filename,psname+1,lpsname)) {// make new pseudo directory
      psname[1]=0; strncat(psname,filename,lpsname);
      pseudo = new St_ValiSet(psname,ds); strcat(psname,".");
    }

    if (isSql) { 	// save SQL  object
      pseudo->fDat=set; set->Shunt(0);
    } else     {	// save Cint object 
      set->Shunt(pseudo);
    }   
  }
  return kContinue;
}
//_____________________________________________________________________________
TDatime St_db_Maker::GetDateTime()
{ 
  if (!fIsDBTime) return StMaker::GetDateTime();
  return fDBTime;
}
//_____________________________________________________________________________
void St_db_Maker::SetDateTime(Int_t idat,Int_t itim)
{ 
  fIsDBTime=0; if (idat==0) return;
  fIsDBTime=1; fDBTime.Set(idat,itim);
}
//_____________________________________________________________________________
void   St_db_Maker::SetDateTime(const char *alias)
{ 
  fIsDBTime=1;
  int idat = AliasDate(alias);// <name>.YYYYMMDD.hhmmss.<ext>
  int itim = AliasTime(alias);
  assert(idat);
  fDBTime.Set(idat,itim);
}
//_____________________________________________________________________________
void   St_db_Maker::SetOn(const char *path)
{ AddAlias("On" ,path,".onoff"); OnOff();}
//_____________________________________________________________________________
Int_t  St_db_Maker::Save(const char *path) 
{
  ofstream out;
  int nakt=0,i,l;
  TDataSet *top,*ds;
  TTable   *tb;
  TString ts,dir;  
  TDatime val[2];
  char cbuf[20];
  top = GetDataBase(path);
  if (!top) return 1;
  TDataSetIter nextDS(top,999);
  while((ds = nextDS())) {
    if (!ds->InheritsFrom(TTable::Class()))continue;    
    ts = ds->Path();
    i = ts.Index(".data/"); assert(i>0); ts.Replace(0  ,i+6,"");
    if (ts.Index(".")>=0)		continue;
    l = ts.Length();
    for (i=0;i<l;i++) {
      if (ts[i]!='/') continue;
      dir.Replace(0,999,ts,i);
      gSystem->MakeDirectory(dir);
    }
    tb = (TTable*)ds;
    i = GetValidity(tb,val); assert(!i);
    sprintf(cbuf,".%08d.%06d.C",val[0].GetDate(),val[0].GetTime());
    ts += cbuf;
    out.open((const char*)ts);       
    tb->SavePrimitive(out,"");
    out.close();
    nakt++;
  }
  return (!nakt);
}
//_____________________________________________________________________________
Int_t  St_db_Maker::GetValidity(const TTable *tb, TDatime *val) const
{
   if (!tb) 				return 1;
   assert(val);
   const TDataSet *par = tb->GetParent();
   if (!par)				return 2;
   TString ts = tb->GetName();
   ts.Replace(0,0,".");
   const St_ValiSet *vs =  (St_ValiSet*)par->Find(ts);
   if (!vs) 				return 3;
   val[0] = vs->fTimeMin;
   val[1] = vs->fTimeMax;
   return 0;
}
//_____________________________________________________________________________
void   St_db_Maker::SetOff(const char *path)
{ AddAlias("Off",path,".onoff"); OnOff();}
//_____________________________________________________________________________
void St_db_Maker::OnOff()
{
  int Off,len;
  if (!fDataBase) return;
  TDataSet *onoff = Find(".onoff");
  if (!onoff) return;
  
  TString tsBase,tsDir,tsTit;
  TDataSet *ono;  
  TDataSetIter onoffNext(onoff);
  while((ono=onoffNext())) {// loop onoffs
    Off = (strcmp("Off",ono->GetName())==0);
    tsDir  = gSystem->DirName(ono->GetTitle());
    tsBase = gSystem->BaseName(ono->GetTitle());
    TRegexp rex(tsBase,1);
    TDataSet *dsDir = GetDataSet(tsDir);
    if (!dsDir) continue;
    if (GetMaker(dsDir) != this) continue;
    TDataSetIter nextVal(dsDir);
    TDataSet *val;
    while ((val=nextVal())) {//loop over val's  
      const char *name = val->GetName();
      if(name[0]!='.') 				continue;
      tsTit = val->GetTitle();
      int ival = tsTit.Index(".Val");
      if (ival<0) 				continue;		
      if (Off != (ival==0))			continue;
      if (rex.Index(name+1,&len)!=0)		continue;
      if ( Off) tsTit.Replace(0,0,".Off");
      if (!Off) tsTit.Replace(0,4,""    );
      val->SetTitle(tsTit);
      printf("<%s::Set%s>   %s/%s\n"
      ,ClassName(),ono->GetName(),(const char*)tsDir,val->GetName()+1);
    }//end loop over val's 
  }// end loop onoffs
}
//_____________________________________________________________________________
void St_db_Maker::SetMaxEntryTime(Int_t idate,Int_t itime)
{
  fMaxEntryTime = mkgmt(idate,itime);
}
//_____________________________________________________________________________
static Int_t AliasDate(const char *alias)

{

  int n = strcspn(alias," ."); if (n<4) return 0;
  int i;
  for (i=0;aliases[i] && strncmp(alias,aliases[i],n);i++) {} 
  return dates[i];
}
//_____________________________________________________________________________
static Int_t AliasTime(const char *alias)

{

  int n = strcspn(alias," ."); if (n<4) return 0;
  int i;
  for (i=0;aliases[i] && strncmp(alias,aliases[i],n);i++) {} 
  return times[i];
}
//_____________________________________________________________________________
static time_t mkgmtime(struct tm *gt)
{
  time_t ut,ug;
  struct tm *gtt;
  gt->tm_isdst=-1;
  ut =mktime(gt);
  gtt = gmtime(&ut);
  gtt->tm_isdst=-1;
  ug = mktime(gtt);
  ug = ut + (ut-ug);
  return ug;
}  
//_____________________________________________________________________________
static time_t mkgmt(int date,int time)
{
  struct tm gt;
  if (date < 19000000) date +=19000000;
  if (date < 19500000) date += 1000000;
  gt.tm_year= ((date/10000)-1900);        
  gt.tm_mon = ((date/100)%100) - 1; 
  gt.tm_mday= ((date    )%100);
  gt.tm_hour=  time/10000;
  gt.tm_min = (time/100 )%100;
  gt.tm_sec = (time     )%100;
  return mkgmtime(&gt);
}
