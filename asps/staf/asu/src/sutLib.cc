/*:Copyright 1996, Lawrence Berkeley National Laboratory
*:>---------------------------------------------------------------------
*:FILE:         csuLib.c
*:DESCRIPTION:  SUT - String UTility functions
*:AUTHOR:       cet - Craig E. Tull, cetull@lbl.gov
*:BUGS:         -- STILL IN DEVELOPMENT --
*:HISTORY:      10may96-v001a-cet- combine several files
*:HISTORY:      02may96-v000a-cet- creation
*:<---------------------------------------------------------------------
*/

/*-------------------------------------------- INCLUDES             --*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef AIX
#include <fnmatch.h>
#endif /*AIX*/

#ifdef IRIX
#include <libgen.h>
#endif /*IRIX*/

#ifdef SOLARIS
#include <libgen.h>
#endif /*SOLARIS*/

#ifdef HPUX
#include <unistd.h>
#endif /*HPUX*/

#include "sutLib.h"
#include "asuAlloc.h"

/*-------------------------------------------- MACROS               --*/
#define _PRINTF printf("%s.%d-",__FILE__,__LINE__);fflush(0);printf
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
/*-------------------------------------------- TYPEDEFS             --*/
/*-------------------------------------------- GLOBALS              --*/
/*-------------------------------------------- PROTOTYPES           --*/

/*
*:>---------------------------------------------------------------------
*:ROUTINE:      int sutMatchWild
*:DESCRIPTION:  Matches a wild-card pattern to a string
*:ARGUMENTS:    
*:RETURN VALUE: TRUE or FALSE
*:<---------------------------------------------------------------------
*/
int sutMatchWild(char *pattern,char* string)
{
#ifdef AIX
   int flags=0;		/* I DONT KNOW WHAT THIS SHOULD BE */
   return !fnmatch(pattern,string,flags);
#endif /*AIX*/
#ifdef HPUX
   int flags=0;		/* I DONT KNOW WHAT THIS SHOULD BE */
   return !fnmatch(pattern,string,flags);
#endif /*HPUX*/
#ifdef SOLARIS
   return gmatch(string,pattern);
#endif /*SOLARIS*/
#ifdef IRIX
   return gmatch(string,pattern);
#endif /*IRIX*/
}

/*
*:>---------------------------------------------------------------------
*:ROUTINE:      int sutMatchReg
*:DESCRIPTION:  Matches a regular expression pattern to a string
*:ARGUMENTS:    
*:RETURN VALUE: TRUE or FALSE
*:<---------------------------------------------------------------------
*/
int sutMatchReg(char *pattern,char* string)
{
   int isMatch=FALSE;
   char *rexp=NULL;
   char *ret0[9];		/* HACK - string limit */
   char *newcursor=NULL;
   char *name=NULL;

   rexp = (char*)ASUALLOC(strlen(pattern) +5);
   sprintf(rexp,"(%s)$0",pattern);fflush(0);

   if( 0 == strcmp(ret0[0],string) ){
      isMatch=TRUE;
   }
   else {
      isMatch=FALSE;
   }
   ASUFREE(name);
   ASUFREE(rexp);
   return isMatch;
}

/*
*:>---------------------------------------------------------------------
*:ROUTINE:      int sutMatchPrefix
*:DESCRIPTION:  Matches a prefix string to a string (ignores whitespc)
*:ARGUMENTS:    
*:RETURN VALUE: TRUE or FALSE
*:<---------------------------------------------------------------------
*/
int sutMatchPrefix(char *prefix,char* string)
{
   char *s=NULL; 
   char *p=NULL;

   if( string == strstr(string, prefix) ){
      return TRUE;
   }
   if( 0== sutStripWhitespace(&s,string)
   ||  0== sutStripWhitespace(&p,prefix)
   ){
      ASUFREE(s); ASUFREE(p);
      return FALSE;
   }
   if( string == strstr(s, p) ){
      ASUFREE(s); ASUFREE(p);
      return TRUE;
   }
}

/*
*:>---------------------------------------------------------------------
*:ROUTINE:      int sutStripWhitespace
*:DESCRIPTION:  Removes whitespace from a string
*:ARGUMENTS:    
*:RETURN VALUE: Length of resultant string
*:<---------------------------------------------------------------------
*/
int sutStripWhitespace(char **outstring,char* string)
{
   char *whtspc=" 	\0\n";
   size_t plen=0;
   size_t slen=0;
   char *s=string;
   char *o=NULL;
   s += (plen = strspn(s,whtspc));
   slen = strcspn(s,whtspc);
   o = (char*)ASUALLOC(slen +1);
   strncpy(o,s,slen);
   *outstring=o;
   return (int)slen;
}

/*--------------------------------------------------------------------*/
/*- Return the N-th token of a delimited string. -*/
char* strntok(const char * str,const char * del,const int n)
{
   int i;
   char *d,*w;

   d = (char*)str;
   for( i=0;i<n;i++ ){
      d += strspn(d,del);       /* skip del */
      d += strcspn(d,del);      /* skip non-delimiters */
   }
   d += strspn(d,del);          /* skip tokens */
   if( strcspn(d,del) > 0 ){
      w = (char*)ASUCALLOC(1,strcspn(d,del) +1);
      strncpy(w,d,strcspn(d,del));
      return (char*)w;
   }
   return NULL;
}

/*--------------------------------------------------------------------*/
/*- Split a delimited string into an array of components. -*/
int strsplit(const char * str,const char * del,char*** a)
{
   int i,j;
   char *buf;
   char *token;
   char *aa[1024];                      /* LIMIT ON # COMPONENTS */

/* if( !(buf = strpbrk(str,del)) )return 0; // NO DELIMITERS FOUND */
/* will return 1 and entire str array... as strtok */

   buf = (char*)ASUALLOC(strlen(str) +1);
   strcpy(buf,str);
   
   i = 0;
   for (token = strtok(buf, del); token; token = strtok(NULL, del)) {
      /* _PRINTF("Token[%d]: >%s<\n", i, token); */
      aa[i++] = token;
   }
   (*a) = (char**)ASUALLOC(i*sizeof(char**));
   for(j=0;j<i;j++){
      (*a)[j] = (char*)ASUALLOC(strlen(aa[j]) +1);
      strcpy((*a)[j],aa[j]);
   }
   ASUFREE(buf);
   return i;
}

/*--------------------------------------------------------------------*/
/*- Extract components bracketed by open & close del.s in a string. -*/
int strbracket(const char *str, const char * od, const char * cd,
			char*** a)
{
   int i,j;
   char *aa[1024];                      /* LIMIT ON # COMPONENTS */
   char *buf;
   char *optr, *cptr;
   int olen, clen;

   buf = (char*)ASUALLOC(strlen(str) +1);
   strcpy(buf,str);
   olen = strlen(od);			/*length of opening delimiter*/
   clen = strlen(od);			/*length of closing delimiter*/
/*- Find first open bracket. -*/
   i = 0;
   while( (optr=strstr(buf,od)) ){
      buf = optr +1;
      if( (cptr=strstr(buf,cd)) ){
	 aa[i] = (char*)ASUALLOC((cptr-buf) +1);
	 strncpy(aa[i],buf,(cptr-buf));
	 buf = cptr +clen;
	 i++;
      }
      else {
	 buf = NULL;
      }
   }
   (*a) = (char**)ASUALLOC(i*sizeof(char**));
   for(j=0;j<i;j++){
      (*a)[j] = aa[j];
      aa[j] = NULL;
   }
   ASUFREE(buf);
   return i;
}

/*--------------------------------------------------------------------*/
int isInteger(char *c)
{
   int i;
   char *signs="+-";
   if( (!isdigit(c[0])) && (NULL == strchr(signs,c[0])) )return FALSE;
   for(i=1;i<strlen(c);i++)if(!isdigit(c[i]))return FALSE;
   return TRUE;
}

