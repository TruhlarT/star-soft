// @(#)root/gt:$Name:  $:$Id: TQtRootCommandCombo.cxx,v 1.1 2009/08/03 18:03:10 fine Exp $
// Author: Valeri Fine   11/01/2009

/****************************************************************************
** $Id: TQtRootCommandCombo.cxx,v 1.1 2009/08/03 18:03:10 fine Exp $
**
** Copyright (C) 2009 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/
///////////////////////////////////////////////////////////////////////////
//
//  The TQtRootCommandCombo is a regular Qt QComboBox class that can send the text
//  entered by the user to the RootCint processor as soon as the user hits "return" key
//  by emitting the "CommandEntered(const QString &);" signal
//
//  The steering code can enable/disable the ROOT command execution via  
//  SetRootCommandExecute(bool on) method.
//
///////////////////////////////////////////////////////////////////////////

#include "TQtRootCommandCombo.h"
#include "TQtRootSlot.h"
#include <QLineEdit>
using namespace std;
//_____________________________________________________________________________
TQtRootCommandCombo::TQtRootCommandCombo(QWidget *parent) : QComboBox(parent)
, fRootCommandExecute(true)
{
   Init();
}

//_____________________________________________________________________________
void TQtRootCommandCombo::Init()
{
   setEditable (true);
   ConnectTreeSlots();
}

//_____________________________________________________________________________
void TQtRootCommandCombo::ConnectTreeSlots()
{
   // Connect the QLineEditor with the ROOT command interpreter
   connect(this->lineEdit(),SIGNAL(returnPressed ()), this, SLOT( rootCommandExecute()) );
   connect(this->lineEdit(),SIGNAL(returnPressed ()), this->lineEdit(), SLOT( clear()) );

   bool doRoot = fRootCommandExecute;
   fRootCommandExecute = !doRoot;  // top force the signal / slot connection
   SetRootCommandExecute(doRoot);
}

//_____________________________________________________________________________
TQtRootCommandCombo::~TQtRootCommandCombo() {}
//_____________________________________________________________________________
void TQtRootCommandCombo::rootCommandExecute() {    
   // Save and execute the last command if needed
   fLastComboLine = this->lineEdit()->text();
   if ( IsRootCommnadExecute() ) emit CommandEntered(fLastComboLine);
}

//_____________________________________________________________________________
void TQtRootCommandCombo::SetRootCommandExecute(bool on)
{
   // Defiune whwthr obejct shpoudl execure the text as the ROOT command
   // The deafult status is "execute"
   if (on != IsRootCommnadExecute() ) {
      fRootCommandExecute = on;
      if (fRootCommandExecute) {
            connect(this,SIGNAL(CommandEntered(const QString&))
               , TQtRootSlot::CintSlot(),SLOT(  ProcessLine(const QString &)) );
      } else {
           disconnect(this,SIGNAL(CommandEntered(const QString&))
                     , TQtRootSlot::CintSlot(),SLOT( ProcessLine(const QString &)) );
      }
   }
}

