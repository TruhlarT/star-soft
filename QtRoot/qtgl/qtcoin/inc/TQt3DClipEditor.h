#ifndef QTROOT_TQtCoin3DClipEditor
#define QTROOT_TQtCoin3DClipEditor
#include <qdockwindow.h> 

class SoClipPlaneManip;
class SoCamera;
class QVButtonGroup;

class TQt3DClipEditor : public QDockWindow {
  Q_OBJECT
  private:

    SoCamera         *fCamera;
    QVButtonGroup    *fCameraGroup;

    SoClipPlaneManip *fPlaneEditor;
    QVButtonGroup    *fPlaneGroup;


  protected:
    void BuildWidget();

  public:
     TQt3DClipEditor ( Place p = InDock, QWidget * parent = 0, const char * name = 0, WFlags f = 0 );
     TQt3DClipEditor ( QWidget * parent, const char * name = 0, WFlags f = 0 );

      virtual ~TQt3DClipEditor();
      void SetClipMan(SoClipPlaneManip *man);
      void SetCamera(SoCamera *cam);
      SoClipPlaneManip *ClipMan() const;
      SoCamera *Camera() const;
   public slots:
      void CameraSelected(int);
      void PlaneSelected(int);
signals:
      void Orientation();
};

#endif
