/****************************************************************
**
** Minimal ROOT based Qt example
**
****************************************************************/
#include <qapplication.h>

#include "TGraph.h"
#include "TEmbeddedPad.h"
#include <qtooltip.h>
#include <qframe.h>
#include <qpixmap.h>
#include <qlayout.h>

int main( int argc, char **argv )
{

    QApplication *app = new QApplication(argc, argv);
    app->connect(app,SIGNAL(lastWindowClosed ()),app,SLOT(quit()));
    QFrame *frame = new QFrame();
    frame->resize(600,600);
    QGridLayout *layout = new QGridLayout(frame,3,3);

    int x,y,w,h;
    frame->rect().rect(&x,&y,&w,&h);
    QPixmap graphPixmap;

    TEmbeddedPad *pad = new TEmbeddedPad("Graph","Embedded",w/3,h/3);
    pad->cd();
    // Add some ROOT object to the current TEmbeddedPad
    TGraph *mygraph;
    float xg[3] = {1,2,3};
    float yg[3] = {1.5, 3.0, 4.5};
    mygraph  = new TGraph(3,xg,yg);
    mygraph->SetMarkerStyle(20);
    mygraph->Draw("AP");
    pad->Modified(); pad->Update();
    // 
    float angle = 0;
    int row,col;
    for (int i = 0; i < 4; i++) {
       switch (i) {
          case 0: row = 0, col = 1; angle =  0; break;
          case 1: row = 1, col = 2; angle = 90; break;
          case 2: row = 2, col = 1; angle = 180; break;
          case 3: row = 1, col = 0; angle = 270; break;
       };
       QWidget *w = new QWidget(frame);
       layout->addWidget(w,row,col);
       w->setPaletteBackgroundPixmap (*(QPixmap*)pad->GetHandleRotate((ULong_t)&graphPixmap,angle));
    }
    // Add some tool tip:
    QToolTip::add( frame, "Close this widget to terminate your application");
    // Raise the widget on the top
    frame->show();
    
    // Create the png file
    QPixmap::grabWidget(frame).save("RotatePad.png","PNG");
    app->exec();
    printf(" Good bye, Rotate Pad\n");
    return 0;
}
