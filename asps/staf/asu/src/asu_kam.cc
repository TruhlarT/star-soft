/*:Copyright 1995, Lawrence Berkeley National Laboratory
*:>---------------------------------------------------------------------
*:FILE:         asu_kam.c
*:DESCRIPTION:  C KUIP Action Modules for ASU
*:AUTHOR:       cet - Craig E. Tull, cetull@lbl.gov
*:BUGS:         -- STILL IN DEVELOPMENT --
*:HISTORY:      12feb96-v000a-cet- creation
*:<---------------------------------------------------------------------
*/
#undef CORBA

/*-------------------------------------------- INCLUDES             --*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "kuip.h"

#include "asuAlloc.h"
#include "asuLib.h"	/* Analysis Service Utilities */
#include "emlLib.h"	/* Error Messaging & Logging */

/*-------------------------------------------- TYPEDEFS             --*/
/*-------------------------------------------- GLOBALS              --*/
/*-------------------------------------------- PROTOTYPES           --*/

/*
*:>---------------------------------------------------------------------
*:ROUTINE:      void kam_asu_hello_
*:DESCRIPTION:  KUIP Action Module to ...
*:ARGUMENTS:    -- NONE --
*:RETURN VALUE: -- NONE --
*:* ASU/HELLO [ MESSAGE ]
*:<---------------------------------------------------------------------
*/
void kam_asu_hello_(){kam_asu_hello();}
int kam_asu_hello()
{
   long npars = ku_npar();      /* number of KUIP parameters */
   char*  msg = ku_gets();	/* message */

   printf("ASU:\tHello, %s \n",msg);
   EML_SUCCESS(NORMAL_SUCCESSFUL_COMPLETION);
}

/*
*:>---------------------------------------------------------------------
*:ROUTINE:      void kam_asu_time_
*:DESCRIPTION:  KUIP Action Module to ...
*:ARGUMENTS:    -- NONE --
*:RETURN VALUE: -- NONE --
*:* ASU/TIME
*:<---------------------------------------------------------------------
*/
void kam_asu_time_(){kam_asu_time();}
int kam_asu_time()
{
   long npars = ku_npar();      /* number of KUIP parameters */
   time_t it,*pt=&it;

   *pt = time(0);
   printf("ASU:\tTime = %s \n",ctime(pt));
   EML_SUCCESS(NORMAL_SUCCESSFUL_COMPLETION);
}

/*
*:>---------------------------------------------------------------------
*:ROUTINE:      void kam_asuallocstats_
*:DESCRIPTION:  KUIP Action Module to ...
*:ARGUMENTS:    -- NONE --
*:RETURN VALUE: -- NONE --
*:* ASU/TIME
*:<---------------------------------------------------------------------
*/
void kam_asuallocstats_(){kam_asuallocstats();}
int kam_asuallocstats()
{
   asuAllocStats();
   EML_SUCCESS(NORMAL_SUCCESSFUL_COMPLETION);
}

