/*:Copyright 1995, Lawrence Berkeley National Laboratory
**:>--------------------------------------------------------------------
**:FILE:        dioClasses.hh
**:DESCRIPTION: DIO Classes
**:AUTHOR:      cet - Craig E. Tull, cetull@lbl.gov
**:BUGS:        -- STILL IN DEVELOPMENT --
**:HISTORY:     12dec95-v000a-cet- creation
**:<--------------------------------------------------------------------
*/

#ifdef __cplusplus
#ifndef DIOCLASSES_HH
#define DIOCLASSES_HH

//:----------------------------------------------- INCLUDES           --
#include <stream.h>
#include "dstype.h"
#include "dsxdr.h"
#include "asuLib.h"
#include "socLib.h"
#include "dui_types.h"
#include "dui_globals.h"
#include "dio_types.h"

//:=============================================== CLASS              ==
class dioFileStream: public virtual socObject {

public:
//:----------------------------------------------- CTORS & DTOR       --
   dioFileStream(const char * name);
   virtual ~dioFileStream();

//:----------------------------------------------- ATTRIBUTES         --
   virtual DIO_MODE_T mode ();
   virtual DIO_STATE_T state ();

//:----------------------------------------------- PUB FUNCTIONS      --
   virtual STAFCV_T close ();
   virtual STAFCV_T getEvent (const char * path);
   virtual STAFCV_T open (const char * fileName, DIO_MODE_T mode);
   virtual STAFCV_T putEvent (const char * path);

protected:
//:----------------------------------------------- PRIV VARIABLES     --
   DIO_MODE_T myMode;
   DIO_STATE_T myState;

   FILE* myFile;
   XDR myXDR;

//:----------------------------------------------- PRIV FUNCTIONS     --

};

//:=============================================== CLASS              ==
class dioFactory: public virtual socFactory {

public:
//:----------------------------------------------- CTORS & DTOR       --
   dioFactory(const char * name);
   virtual ~dioFactory();

//:----------------------------------------------- ATTRIBUTES         --
//:**NONE**

//:----------------------------------------------- PUB FUNCTIONS      --
   virtual STAFCV_T deleteFileStream (const char * name);
   virtual STAFCV_T findFileStream (const char * name
                , dioFileStream*& fileStream);
   virtual STAFCV_T getFileStream (IDREF_T id
                , dioFileStream*& fileStream);
   virtual STAFCV_T list ();
   virtual STAFCV_T newFileStream (const char * name
                , const char * fileName, DIO_MODE_T mode);

protected:
//:----------------------------------------------- PRIV VARIABLES     --
//:----------------------------------------------- PRIV FUNCTIONS     --

};

//----------------------------------------------------------------------
CORBA_TIE(dioFileStream)
CORBA_TIE(dioFactory)

#endif /*DIOCLASSES_HH*/
#endif /*__cplusplus*/

