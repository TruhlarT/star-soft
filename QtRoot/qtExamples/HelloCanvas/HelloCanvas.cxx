/****************************************************************
**
** Minimal ROOT based Qt example
**
****************************************************************/
#include <qapplication.h>

#include "TGraph.h"
#include "TQtWidget.h"
#include "TCanvas.h"
#include <qtooltip.h>
#include <qlabel.h>

int main( int argc, char **argv )
{

    QApplication *app = new QApplication(argc, argv);
    app->connect(app,SIGNAL(lastWindowClosed ()),app,SLOT(quit()));

    TQtWidget *MyWidget= new TQtWidget(0,"MyWidget");
    MyWidget->resize(300,200);

    // Add some tool tip:
    QToolTip::add( MyWidget, "Close this widget to terminate your application");
    
    // Create any other Qt-widget here
    //         . . .

    // Make the the embedded TCanvas to be the current ROOT TCanvas
    MyWidget->GetCanvas()->cd();
    
    // Add some ROOT object to the current TCanvas
    TGraph *mygraph;
    float x[3] = {1,2,3};
    float y[3] = {1.5, 3.0, 4.5};
    mygraph  = new TGraph(3,x,y);
    mygraph->SetMarkerStyle(20);
    mygraph->Draw("AP");

    //Add Qt Label in the top the ROOT TCanvas
    QLabel *label = new QLabel("L",MyWidget);
    label->setBackgroundMode(Qt::NoBackground);
    label->move(40,40);
    label->resize(10,10);

    // Raise the widget on the top
    MyWidget->show();
    MyWidget->Refresh();
    
    // Create the png file
    MyWidget->Save("HelloCanvas.png");
    app->exec();
    printf(" Good bye, ROOT Canvas\n");
    return 0;
}
