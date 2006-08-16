// Author: Bertrand Bellenot   22/08/02

/*************************************************************************
 * Copyright (C) 1995-2002, Bertrand Bellenot.                           *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see the LICENSE file.                         *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Definition of a dialog box used to access the main shower parameters //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <qtabdialog.h>

class QTable;
class QListBox;
class QVButtonGroup;
class RootShower;

class SettingsDialog : public QTabDialog {
Q_OBJECT
private:

    QTable        *fDimensionTable;
    QTable        *fParticleTable;
    QListBox      *fListBox;
    QVButtonGroup *fF1;

public:
    SettingsDialog(RootShower *p, unsigned int w, unsigned int h);                         
    virtual ~SettingsDialog();

public slots:
    virtual void ProcessMessage();
    virtual void HelpCB();
};

#endif
