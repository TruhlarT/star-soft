#ifndef QGLViewer_Histogram
#define QGLViewer_Histogram

#include <TQtWidget.h>

class TH1;

class Histogram : public TQtWidget 
{
Q_OBJECT
public :
  Histogram(QWidget *parent = 0);
  void create(const char *title,int nbins, double xlow, double xup);
  void create(const char *title,int nxbins, double xlow, double xup
                               ,int nybins, double ylow, double yup);

public slots:
  void init();
  void animate(bool);
  void fill(float x);
  void fill(float x, float y);

private :
  TH1  * histogram_;
};

#endif
