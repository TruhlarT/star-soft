//:Copyright 1995, Lawrence Berkeley National Laboratory
//:>--------------------------------------------------------------------
//:FILE:	spx_init.C
//:DESCRIPTION:	Functions  to initialize SPX 
//:AUTHOR:	cet - Craig E. Tull, cetull@lbl.gov
//:BUGS:	-- STILL IN DEVELOPMENT --
//:HISTORY:	21nov95-v000a-cet- creation
//:<--------------------------------------------------------------------

#include "asuLib.h"
#include "emlLib.h"
#include "spxLib.h"

spxManager *spx;

//:>--------------------------------------------------------------------
//:ROUTINE:	int spx_init()
//:DESCRIPTION:	Initialize SPX
//:ARGUMENTS:	-- NONE --
//:RETURN VALUE:-- NONE --
//:<--------------------------------------------------------------------
int spx_init()
{
   EML_MESSAGE(SPX: Initializing.);

/*- Define the SPX KUIP commands. -*/
   spx_def_();

   return TRUE;
}

//:>--------------------------------------------------------------------
//:ROUTINE:	int spx_start()
//:DESCRIPTION:	Start SPX
//:ARGUMENTS:	-- NONE --
//:RETURN VALUE:-- NONE --
//:<--------------------------------------------------------------------
int spx_start()
{
   EML_MESSAGE(SPX: Starting.);

/*- Create the SPX Manager. -*/
   spx = new spxManager("spx");

   return TRUE;
}

//:>--------------------------------------------------------------------
//:ROUTINE:	int spx_stop()
//:DESCRIPTION:	Stop SPX
//:ARGUMENTS:	-- NONE --
//:RETURN VALUE:-- NONE --
//:<--------------------------------------------------------------------
int spx_stop()
{
   EML_MESSAGE(SPX: Stopping.);

/*- Delete the SPX Manager.
   delete spx;
unecessary -- soc will do it. -*/

   return TRUE;
}

