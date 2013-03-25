#include "TQtTabValidator.h"
#include "TTabCom.h"
#include <string>
#include <sstream>
/****************************************************************************
** $Id: TQtTabValidator.cxx,v 1.8 2013/03/25 23:02:11 perev Exp $
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
#if ROOT_VERSION_CODE < ROOT_VERSION(5,34,3)
   fgTabCom->Hook(buffer, &pos);
#else
   std::stringstream sstr;
   fgTabCom->Hook(buffer, &pos, sstr);
#endif
   input = buffer;
   return QValidator::Acceptable; // Intermediate;
}
