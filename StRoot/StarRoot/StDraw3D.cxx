// $Id: StDraw3D.cxx,v 1.8 2008/05/02 17:48:12 fine Exp $
//*-- Author :    Valery Fine(fine@bnl.gov)   27/04/2008
#include "StDraw3D.h"
#include "TCanvas.h"
#include "TPolyMarker3D.h"
#include "TPolyLine3D.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TEnv.h"
#include "StCheckQtEnv.h"
#include "TStyle.h"
#include "TVirtualViewer3D.h"

int StDraw3D::fgDraw_3d_init = 0;

static Color_t colorDefault = Color_t(-1);
static Style_t styDefault   = Style_t(-1);
static Size_t  sizDefault   = Size_t (-1);

Color_t StDraw3D::fgColorDefault = Color_t(-1);
Style_t StDraw3D::fgStyDefault   = Style_t(-1);
Size_t  StDraw3D::fgSizDefault   = Size_t (-1);
Color_t StDraw3D::fgBkColor      = kBlack;

//___________________________________________________
static inline TVirtualViewer3D *InitCoin(TVirtualPad *pad) 
{
   TVirtualViewer3D *viewer = 0;
   // check Coin env and load if present
   TString ivrootDir = gSystem->Getenv("IVROOT");
   if (ivrootDir.IsNull() ) ivrootDir = "$ROOT/5.99.99/Coin2/.$STAR_HOST_SYS";
   ivrootDir +=   "/lib/";
   gSystem->ExpandPathName(ivrootDir);
   static bool CheckCoin = false;
   if (!gSystem->AccessPathName(ivrootDir.Data())) {
      if (     !gSystem->Load(ivrootDir+"libSoQt") 
            && !gSystem->Load(ivrootDir+"libCoin")
            && !gSystem->Load(ivrootDir+"libSmallChange"));
      CheckCoin = true;
   }

   if (CheckCoin && pad && (viewer = TVirtualViewer3D::Viewer3D(pad,"oiv")))
   {
      // Create Open GL viewer
//      TGQt::SetCoinFlag(1);
      viewer->BeginScene();
      viewer->EndScene();
    }
    return viewer;
}

//___________________________________________________
//
//   view_3D
//___________________________________________________
class view_3D  {
   private:
      TObject *fModel;
      TString  fComment;
      TString  fObjectInfo;
      void MakeInfo()
      {
         fObjectInfo="";
         if (fModel) {
            fObjectInfo = Form("( %s *)%p ",fModel->ClassName(),fModel);
         }
         if (!fComment.IsNull()) fObjectInfo += fComment;
      }
   public:
     view_3D(TObject *model = 0, const char *comment="") : fModel(model),fComment(comment)
     { MakeInfo(); }
     ~view_3D(){;}
     TObject *Model() const { return fModel;}
     void SetModel(TObject *model) {fModel = model;             MakeInfo();}
     void SetComment(const char *comment) {fComment  = comment; MakeInfo();}
     void AddComment(const char *comment) {fComment += comment; MakeInfo();}
     const TString &GetObjectInfo() const {
        return fObjectInfo;
     } 
     const char  *GetModelInfo(Int_t x, Int_t y) const {
        const TString &customInfo = GetObjectInfo();
        const char *info = 0;
        if (customInfo.IsNull()) info = fModel->GetObjectInfo(x,y);
        else info = customInfo.Data();
        return info;
     }
};

//___________________________________________________
//
//   poly_line_3D
//___________________________________________________
class poly_line_3D : public TPolyLine3D, public view_3D {
   public:
     poly_line_3D(Int_t n, Float_t *p, Option_t *option="") : TPolyLine3D(n,p){;}
     virtual ~poly_line_3D(){;}
     virtual char  *GetObjectInfo(Int_t x, Int_t y) const
     {
        return (char *)GetModelInfo(x,y);
     }
};

//___________________________________________________
//
//   poly_marker_3D
//___________________________________________________
class poly_marker_3D : public TPolyMarker3D, public view_3D {
   public:
     poly_marker_3D(Int_t n, Float_t *p, Option_t *option="") : TPolyMarker3D(n,p){;}
     virtual ~poly_marker_3D(){;}
     virtual char  *GetObjectInfo(Int_t x, Int_t y) const
     {
        return (char*)GetModelInfo(x,y);
     }
};
//___________________________________________________
StDraw3D::StDraw3D(TVirtualPad *pad): fPad(pad),fViewer(0),fView(0)
{
   static const Style_t UHitSty = 4; static const Size_t UHitSiz = 0.35; static const Color_t UHitCol=kBlue;
   static const Style_t NHitSty = 1; static const Size_t NHitSiz = 1.00; static const Color_t NHitCol=kGreen;
   static const Style_t TrakSty = 1; static const Size_t TrakSiz = 1.00; static const Color_t TrakCol=kRed;
   static const Style_t VertSty = 5; static const Size_t VertSiz = 3.50; static const Color_t VertCol=kYellow;
   AddStyle(kVtx,         VertCol,VertSty,VertSiz);
   AddStyle(kPrimaryTrack,TrakCol,TrakSty,TrakSiz);
   AddStyle(kGlobalTrack, TrakCol,TrakSty,TrakSiz);
   AddStyle(kUsedHit,     UHitCol,UHitSty,UHitSiz);
   AddStyle(kUnusedHit,   NHitCol,NHitSty,NHitSiz);

   if (!fPad) {
      fPad = new TCanvas("STAR","Event Viewer", 400,400);
      fPad->SetFillColor(fBkColor);
      fPad->Modified();
      fPad->Update();
   }
}
  
//___________________________________________________
StDraw3D::~StDraw3D()
{
    Clear();
    delete fPad; 
    fPad = 0;
}

//___________________________________________________
void  StDraw3D::Clear(Option_t *opt)
{
   // Clear the view
   if (fPad) {
      fPad->Clear(opt);
      fPad->Modified();
      fPad->Update();
   }
}

//___________________________________________________
TObject *StDraw3D::Draw(TObject *o)
{
   // Draw the 3d object 
   // and set the new background color if needed
   if (o) {
      if (!fgDraw_3d_init) Draw3DInit();
      TVirtualPad *sav = 0;
      if (fPad) fPad->cd();
      else      sav = gPad;
      o->Draw();
      if (!fPad) fPad = gPad;
      else  if (sav) sav->cd();
      if (!fViewer) fViewer = InitCoin(fPad);
   }
   return o;
}
//___________________________________________________
void StDraw3D::SetBkColor(Color_t newBkColor)
{
   // Set the canvas background color;
   fBkColor = newBkColor;
   if (fPad->GetFillColor() != fBkColor)
       fPad->SetFillColor(fBkColor);
}
//___________________________________________________
const StDraw3DStyle &StDraw3D::AddStyle(EDraw3DStyle type,Color_t col,Style_t sty,Size_t siz)
{
   fStyles.insert(std::pair<EDraw3DStyle,StDraw3DStyle>(type,StDraw3DStyle(type,col,sty,siz)));
   return Style(type);
}

//___________________________________________________
const StDraw3DStyle &StDraw3D::Style(EDraw3DStyle type)
{
    return fStyles[type];
}

//___________________________________________________
int StDraw3D::Draw3DInit(){
   // check the correct env and load the plugins
   if (fgDraw_3d_init) return 1;
   fgDraw_3d_init = 1;
   if (!StCheckQtEnv::SetQtEnv(false)) {
      // define the background image
      const char *backShape = "$STAR/StRoot/macros/graphics/StarTPC.iv";
      printf(" Setting the background shape to be 	%s\n", backShape);
      gEnv->SetValue("Gui.InventorBackgroundShape",backShape);
   }
   return 1;
}
//___________________________________________________
TObject *StDraw3D::Points(int n, const float *xyz, Color_t col,Style_t sty,Size_t siz)
{
   if (!fgDraw_3d_init) Draw3DInit();
   poly_marker_3D *plMk  = new poly_marker_3D(n,(Float_t*)xyz);
   if (col != colorDefault) plMk->SetMarkerColor(col);
   if (sty != styDefault)   plMk->SetMarkerStyle(sty);
   if (siz != sizDefault)   plMk->SetMarkerSize(siz);
   fView = plMk;
   return Draw(plMk);
}
//___________________________________________________
TObject *StDraw3D::Points(int n, const float *xyz, EDraw3DStyle sty)
{
  const StDraw3DStyle &style =  Style(sty);
  return Points(n, xyz, style.Col(),style.Sty(),style.Siz());
}
//___________________________________________________
TObject *StDraw3D::Point(float x, float y, float z, Color_t col,Style_t sty,Size_t siz)
{
   if (!fgDraw_3d_init) Draw3DInit();
   float xyz[]={x,y,z};
   return Points(1,xyz,col,sty,siz);
}

//___________________________________________________
TObject *StDraw3D::Point(float x, float y, float z, EDraw3DStyle sty)
{
   const StDraw3DStyle &style =  Style(sty);
   return Point(x,y, z, style.Col(),style.Sty(),style.Siz());
}

//___________________________________________________
TObject *StDraw3D::Draw3D(int n,  const float *xyz)
{
   if (!fgDraw_3d_init) Draw3DInit();
   return Points(n,xyz,kVtx);
}

//___________________________________________________
TObject *StDraw3D::Line(int n,  const float *xyz, Color_t col,Style_t sty,Size_t siz)
{
   if (!fgDraw_3d_init) Draw3DInit();
   poly_line_3D *plLine  = new poly_line_3D(n,(Float_t*)xyz);
   if (col != colorDefault) plLine->SetLineColor(col);
   if (sty != styDefault)   plLine->SetLineStyle(sty);
   if (siz != sizDefault)   plLine->SetLineWidth(Width_t(siz));
   fView = plLine;
   return Draw(plLine);
}

//___________________________________________________
TObject *StDraw3D::Line(int n,  const float *xyz,EDraw3DStyle sty)
{
   const StDraw3DStyle &style =  Style(sty);
   return Line(n,xyz,  style.Col(),style.Sty(),style.Siz() );
}

//___________________________________________________
void StDraw3D::SetModel(TObject *model)
{
   // add the "model" reference to the current view
   if (fView) fView->SetModel(model);
}

//___________________________________________________
void StDraw3D::SetComment(const char *cmnt)
{
   // set the "model" comment for the current view
   if (fView) fView->SetComment(cmnt);
}

//___________________________________________________
void StDraw3D::AddComment(const char *cmnt)
{
   // add the "model" comment for the current view
   if (fView) fView->AddComment(cmnt);
}

//___________________________________________________
void StDraw3D::Draw3DTest(){
   if (!fgDraw_3d_init) Draw3DInit();
   float xyz[] = { 189.195,       27.951,       123.966
                 ,187.195,       28.6187,       122.89
                 ,181.195       ,30.6788       ,119.556
                 ,179.195       ,31.3387       ,118.454
                 ,177.195       ,32.0065       ,117.328
                 ,175.195       ,32.6132       ,116.26
                 ,173.195       ,33.2385       ,115.146
                 ,171.195       ,33.8552       ,114.016
                 ,169.195       ,34.3924       ,112.964
         };

   int sizeXYZ = sizeof(xyz)/sizeof(float)/3;
   const float *fff = (const float *)&xyz[0];
   fprintf(stderr," %d %p\n", sizeXYZ,fff);
   Draw3D(sizeXYZ,fff);
   SetComment("The hits from the TPC sector");
   Line(sizeXYZ,fff,kPrimaryTrack);
   SetComment("The recontstructed track");
}
