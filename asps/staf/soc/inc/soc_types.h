/*:Copyright 1995, Lawrence Berkeley Laboratory
*:>---------------------------------------------------------------------
*:FILE:         soc_types.h
*:DESCRIPTION:  Variable types for SOC
*:AUTHOR:       cet - Craig E. Tull, cetull@lbl.gov
*:BUGS:         -- STILL IN DEVELOPMENT --
*:HISTORY:      14nov95-v000b-cet- rename from SOC.h
*:HISTORY:      26jul95-v000a-cet- creation
*:<---------------------------------------------------------------------
*/
#ifndef SOC_TYPES_H
#define SOC_TYPES_H

/*-------------------------------------------- INCLUDES             --*/
#include "soc_macros.h"

/*-------------------------------------------- CORBA                --*/
#ifdef CORBA
#include "soc_i.hh"
#endif

/*-------------------------------------------- TYPEDEFS             --*/
#ifndef CORBA

#include "stafCorba.h"

typedef long IDREF_T;			/* reference ID */

typedef long SOC_PTR_T;			/* pointer type */

#ifndef CHAR_SEQ_T
TYPEDEF_SEQUENCE(char,CHAR_SEQ_T);
TYPEDEF_SEQUENCE(unsigned char,OCTET_SEQ_T);
TYPEDEF_SEQUENCE(short,SHORT_SEQ_T);
TYPEDEF_SEQUENCE(unsigned short,USHORT_SEQ_T);
TYPEDEF_SEQUENCE(long,LONG_SEQ_T);
TYPEDEF_SEQUENCE(unsigned long,ULONG_SEQ_T);
TYPEDEF_SEQUENCE(float,FLOAT_SEQ_T);
TYPEDEF_SEQUENCE(double,DOUBLE_SEQ_T);
TYPEDEF_SEQUENCE(char*,STRING_SEQ_T);
#endif /*CHAR_SEQ_T*/

#endif

/*-------------------------------------------- GLOBALS              --*/
/*-------------------------------------------- PROTOTYPES           --*/
extern CC_P int soc_init();
extern CC_P int soc_start();
extern CC_P int soc_stop();
extern CC_P void soc_def_();

extern CC_P void kam_soc_bind_();
extern CC_P void kam_soc_release_();
extern CC_P void kam_soc_count_();
extern CC_P void kam_soc_deleteid_();
extern CC_P void kam_soc_deleteobject_();
extern CC_P void kam_soc_findobject_();
extern CC_P void kam_soc_idobject_();
extern CC_P void kam_soc_list_();
extern CC_P void kam_soc_newobject_();
extern CC_P void kam_socobject_name_();
extern CC_P void kam_socobject_type_();
extern CC_P int kam_soc_bind();
extern CC_P int kam_soc_release();
extern CC_P int kam_soc_count();
extern CC_P int kam_soc_deleteid();
extern CC_P int kam_soc_deleteobject();
extern CC_P int kam_soc_findobject();
extern CC_P int kam_soc_idobject();
extern CC_P int kam_soc_list();
extern CC_P int kam_soc_newobject();
extern CC_P int kam_socobject_name();
extern CC_P int kam_socobject_type();

#endif /* SOC_TYPES_H */

