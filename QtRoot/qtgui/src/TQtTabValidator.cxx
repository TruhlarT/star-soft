#include "TQtTabValidator.h"
#include "TTabCom.h"
#include <string>
#include <sstream>
/****************************************************************************
** $Id: TQtTabValidator.cxx,v 1.4 2012/06/11 14:20:57 fisyak Exp $
**
** Copyright (C) 2003 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

TTabCom *TQtTabValidator::fgTabCom = 0;
//_________________________________________________________________________________________________________
void TQtTabValidator::Clear()  
{
   if (fgTabCom) fgTabCom->ClearAll();
}
//_________________________________________________________________________________________________________
QValidator::State TQtTabValidator::validate(QString &input, int &pos) const {
   if (!fgTabCom) fgTabCom = new TTabCom();
   char buffer[2048];
   qstrcpy(buffer,(const char *)input);
   // printf("%d %s \n",pos,buffer); 
   std::stringstream sstr;
   fgTabCom->Hook(buffer, &pos, sstr);
   input = buffer;
   return QValidator::Acceptable; // Intermediate;
}
