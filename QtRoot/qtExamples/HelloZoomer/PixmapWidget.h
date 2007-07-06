#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include <qwidget.h>
#include <qstring.h>

class QPixmap;

class PixmapWidget : public QWidget
{
	Q_OBJECT
	
public:
#if QT_VERSION < 0x40000
	PixmapWidget( const QPixmap &pixmap, QWidget *parent=0, Qt::WFlags f= Qt::WStyle_Customize | Qt::WStyle_Splash | Qt::WRepaintNoErase | Qt::WNoAutoErase );
#else
	PixmapWidget( const QPixmap &pixmap, QWidget *parent=0, Qt::WFlags f=0 );
#endif      
	~PixmapWidget();

public slots:
	void setZoomFactor( float );
	void Magnify( );
   void ResetPixmap(const QPixmap &pixmap);
	
signals:
	void zoomFactorChanged( float );
   void Zoommed();

protected:
   void Init();

	void paintEvent( QPaintEvent* );
	void wheelEvent( QWheelEvent* );
   void leaveEvent(QEvent *);

private:
	QPixmap *m_pm;
	float zoomFactor;
   float fTime; // millisecond
   float fSmoothFactor;
   float fZoomStep;
};

#endif // PIXMAPWIDGET_H
