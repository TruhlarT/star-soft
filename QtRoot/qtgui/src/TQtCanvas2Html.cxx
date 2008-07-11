#include "TQtCanvas2Html.h"
#include "TUUID.h"

#if QT_VERSION >= 0x40000
//Added by qt3to4:
#  include <QTextStream>
#  include <QFileInfo>
#  include <QFile>
#  include <QPixmap>
#else
#  include <qtextstream.h>
#  include <qfileinfo.h> 
#  include <qfile.h>
#  include <qpixmap.h>
#endif /* QT_VERSION */

#include "TVirtualPad.h"
#include "TQtWidget.h"
#include "TQtZoomPadWidget.h"
#include "TGQt.h"
#include "TSystem.h"
#include "TH1.h"
#include "TList.h"
#include "TIterator.h"
#include "TError.h"
// fgPrefix = "Root_Qt_Canvas";

//______________________________________________________________________________________________
TQtCanvas2Html::TQtCanvas2Html(TVirtualPad *pad,float zoom, const char *folder,  TQtZoomPadWidget *zoomer) 
: TQtPad2Html(pad,true,folder ? QString(folder):QString()),fZoomer(zoomer), fZoomCanvas(0)
, fOwnZoom((zoomer == 0))
{ 
   // Create the clickable HTML map from the input "pad"
   MakePage(zoom);
   ClosePage();
}
//______________________________________________________________________________________________
TQtCanvas2Html::TQtCanvas2Html(TQtWidget *canvas, float zoom, const char *folder, TQtZoomPadWidget *zoomer)
: TQtPad2Html((canvas ? canvas->GetCanvas():0),true,folder ? QString(folder):QString()),fZoomer(zoomer)
, fZoomCanvas(0), fOwnZoom ((zoomer == 0))
{
   // Create the clickable HTML map from the input "canvas widget"

   MakePage(zoom);
   ClosePage();
}
//______________________________________________________________________________________________
TQtCanvas2Html::TQtCanvas2Html(TVirtualPad *pad,  uint width, uint height, const char *folder, TQtZoomPadWidget *zoomer)
: TQtPad2Html(pad,true,folder ? QString(folder):QString()),fZoomer(zoomer), fZoomCanvas(0)
, fOwnZoom((zoomer == 0))
{
   // Create the clickable HTML map from the input "pad"
   //  and define its size if defined by "width" and  "height"  in pixels
   MakePage(1.0,width,height);
   ClosePage();
}
//______________________________________________________________________________________________
TQtCanvas2Html::TQtCanvas2Html(TQtWidget *canvas, uint width, uint height, const char *folder, TQtZoomPadWidget *zoomer)
: TQtPad2Html((canvas ? canvas->GetCanvas():0),true,folder ? QString(folder):QString()),fZoomer(zoomer)
, fZoomCanvas(0), fOwnZoom ((zoomer == 0))
{
   // Create the clickable HTML map from the input "canvas widget" with the 
   //  and define its size if defined by "width" and  "height"  in pixels

   MakePage(1.0,width,height);
   ClosePage();
}

//______________________________________________________________________________________________
void TQtCanvas2Html::MakePage(float zoom,uint width, uint height)
{
   // Open and generate html and png files
   // Make UUID
   TUUID id;
   fUUID = id.AsString();
   fTargetWindow = "Zoom_";
   TVirtualPad *pad = Pad();
   if (pad) fTargetWindow += pad->GetName();
   fTargetWindow.remove(" ");
   fTargetWindow.lower();
   if (!fZoomer) {
      fZoomer =  new TQtZoomPadWidget(pad);
      fZoomer->SetZoomFactor(zoom);
   }
   // Disregard the zoom factor and assign the fixed size
   if (width*height) {
      fZoomer->HideOnLeave(false);
      fZoomer->resize(width,height);
   }
   fZoomCanvas = fZoomer->GetCanvas();
   OpenHeader(pad); 
   WritePad(pad);
   HtmlTag("h3");Eol();
   Html() << "Click any TPad image to get its ";
   HtmlTag("a","href=\"http://root.bnl.gov/QtRoot/htmldoc/TQtZoomPadWidget.html#TQtZoomPadWidget:description\"") << "zoomed"; 
   EndTag("a") << " view with the separate window";
   EndTag("h3");EndTag("DIV"); 
   HtmlTag("DIV", "ALIGN=CENTER"); Eol();
   CreateMapPage(pad);
   QString map = "map";
   map += fTargetWindow;
   MapCanvas(pad,(const char *)map,false);
}
//______________________________________________________________________________________________
TQtCanvas2Html::~TQtCanvas2Html()
{ if (fOwnZoom) delete fZoomer; fZoomer = 0;fOwnZoom=false; }

//______________________________________________________________________________________________
void TQtCanvas2Html::MapTag(const char *name) 
{

   // Creat map html tag

   Html() << "<MAP NAME="; Quote() << name; Quote()<<">";
}

//______________________________________________________________________________________________
void TQtCanvas2Html::CreateRectArea(const QString &name,const QString &title
                                    , int upperLeft_x, int upperLeft_y
                                    , int lowRight_x,  int lowRight_y)
{
    // Create the rectangular html AREA

    Html() << "<AREA HREF="; Quote() << name;  Quote();
    Html() << " ALT=";   Quote() << title;     Quote();
    Html() << " TITLE="; Quote() << title;     Quote();
    Html() << " SHAPE=RECT COORDS=";           Quote();
    Html() <<
        QString("%1,%2,%3,%4").arg(upperLeft_x).arg(upperLeft_y).arg(lowRight_x).arg(lowRight_y);
    Quote() << " target="; Quote() << fTargetWindow << fUUID; Quote();
    Quote() << ">"; Eol();
}

//______________________________________________________________________________________________
int TQtCanvas2Html::CreateMapPage(TVirtualPad *pad) 
{
   // Create html AREA for each TPad from the current TCanvas

   Int_t padCounter = 0;
   if (!pad) pad = gPad;

   // Refresh the pad to make sure its image is up-to-date
   pad->Modified();
   pad->Update();
   if (pad) {
      // Loop over the TPad and look for the sub-pads
      TList *l= pad->GetListOfPrimitives();
      TIter next(l);
      TObject *o = 0;
      QString map = "map";
      map += fTargetWindow;
      MapTag((const char*)map);
      while ( (o=next()) ) {
         if (o->InheritsFrom(TVirtualPad::Class())) {
            TVirtualPad *p = (TVirtualPad *)o;
            fZoomer->SetPad(p,padCounter ==0);
            // Find first pad there
            TVirtualPad  *pp = (TVirtualPad  *)fZoomCanvas->GetListOfPrimitives()->First();
            TQtPad2Html nextPad(pp,(const char *)HtmlFolder());
            QFileInfo info(nextPad.PadHtmlFile());
            CreateRectArea(info.fileName(), nextPad.ImageTitle()
                        , p->UtoAbsPixel(0), p->VtoAbsPixel(1)
                        , p->UtoAbsPixel(0)+p->UtoPixel(1)
                        , p->VtoAbsPixel(1)+p->VtoPixel(0) );
            padCounter++;
         }
      }
      EndTag("MAP");
      Printf("Total pages: %d", padCounter+1);
   } else {
      Warning("TQtCanvas2Html::CreateMapPage"," No TPad has been provided. ");
   }
   return padCounter;
}
