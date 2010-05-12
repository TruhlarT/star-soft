#ifndef STAR_TQROOTCOMMNANDCOMBO
#define STAR_TQROOTCOMMNANDCOMBO
// @(#)root/gt:$Name:  $:$Id: TQtRootCommandCombo.h,v 1.2 2010/05/12 23:12:07 fine Exp $
// Author: Valeri Fine   11/01/2009

/****************************************************************************
** $Id: TQtRootCommandCombo.h,v 1.2 2010/05/12 23:12:07 fine Exp $
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
#include <QComboBox>

class QString;

class TQtRootCommandCombo : public QComboBox 
{
      Q_OBJECT
   private:
      QString fLastComboLine;
      bool   fRootCommandExecute;
      bool   fAutoadd;
   protected:
      void ConnectTreeSlots();
      void Init();
      void InitFromHistory();

   public:
      TQtRootCommandCombo(QWidget *parent = 0);
      virtual ~TQtRootCommandCombo();
      const QString &ComboLine() const { return fLastComboLine;}
      void SetRootCommandExecute(bool on=true);
      bool IsRootCommnadExecute() const { return fRootCommandExecute;}
      bool autoAdd() const { return fAutoadd;}
   public slots:
      void rootCommandExecute();
      void setAutoadd(bool on=true) { fAutoadd = on; }
   signals:
      void CommandEntered(const QString &);

};
#endif
