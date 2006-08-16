// Author: Bertrand Bellenot   22/08/02

/*************************************************************************
 * Copyright (C) 1995-2002, Bertrand Bellenot.                           *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see the LICENSE file.                         *
 *************************************************************************/

/*************************************************************************
 *   Modified by Valeri Fine to use Qt GUI labrary                       *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// GButtonFrame                                                         // 
//                                                                      //
// This File contains the declaration of the GButtonFrame-class for     //
// the RootShower application                                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef GBUTTONFRAME_H
#define GBUTTONFRAME_H

#include <qvbuttongroup.h>

class QPushButton;
class RootShower;

class GButtonFrame: public QVButtonGroup {
Q_OBJECT
private:

    QPushButton *fNextEventButton;
    QPushButton *fShowTrackButton;
    QPushButton *fStopSimButton;

public:    
    // enum 
    enum EState {
        kAllActive,
        kNoneActive
    };
    // Constructor & destructor
    GButtonFrame(QWidget* p);
    virtual ~GButtonFrame();
    void SetState(EState state);
signals:
    void NextEvent();
    void SelectEvent();
    void Interrupt();
};


#endif // GBUTTONFRAME_H
