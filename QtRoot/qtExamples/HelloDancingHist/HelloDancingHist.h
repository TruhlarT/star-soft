// @(#)root/qt:$Id: HelloDancingHist.h,v 1.1 2009/11/19 19:23:07 fine Exp $
// Author: Valeri Fine   16/08/2009
/****************************************************************************
**
** Copyright (C) 2009 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

#ifndef QTROOT_HISTROTATION_H
#define QTROOT_HISTROTATION_H

#include <QFrame>

class TEmbeddedPad;
class TH1F;
class TH2F;
class TProfile;

class HelloDancingHist : public QFrame
{
    Q_OBJECT
public:
    HelloDancingHist( int s = 10, QWidget *parent = 0, const char *name = 0 );
    virtual ~HelloDancingHist();

public slots:
    void	nextGeneration();

protected:
    virtual void paintEvent( QPaintEvent * );
    void updateHistograms();

private:
    TEmbeddedPad   *fPads[3];
    TH1F           *fHpx;
    TH2F           *fHpxpy;
    TProfile       *fHprof;
          
};


#endif // QTROOT_HISTROTATION_H
