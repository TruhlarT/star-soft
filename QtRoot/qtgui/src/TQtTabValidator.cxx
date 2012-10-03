#include "TQtTabValidator.h"
#include "TTabCom.h"
#include <string>
#include <sstream>
/****************************************************************************
** $Id: TQtTabValidator.cxx,v 1.6 2012/10/03 17:48:56 perev Exp $
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
#if ROOT_VERSION_CODE < ROOT_VERSION(5,26,0)
   fgTabCom->Hook(buffer, &pos);
#else
//VP   std::stringstream sstr;
//VP  fgTabCom->Hook(buffer, &pos, sstr);
   fgTabCom->Hook(buffer, &pos);
#endif
   input = buffer;
   return QValidator::Acceptable; // Intermediate;
}
