
# line 9 "../src/idl.y"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#ifndef sun
#include <strings.h>
#else
#include <string.h>
#endif
#include <stdlib.h>
#define FORTRANCOMMENTSIZE 277
/* #define STUFF_FOR_64_BITS */
#define P printf(
#define PP printf(
#define EE fprintf(stderr,
#define RETURN if(!gC) DoComment(__LINE__,yytext); else return
#define RETURN2 if(!gC) DoComment(__LINE__,yytext)
#define F fprintf(stderr,
#define FF fprintf(ff,
#define FH fprintf(gFpH,
#define FINC fprintf(gFpInc,
#define SZ 170 /* line size in input file */
#define ISIZE 83 /* size of identifiers (eg interface names, prototype names */
#define PROTOTYPES 4 /* max prototypes in interface def */
#define INCDIR 37	/* max -I on command line */
#define INCDIRS 80	/* max size of path spec in a -I */
#define ERROR_FORMAT "STAR idl compiler.\
  Error on line %d of your idl file:\n%s\n%s\n"
#define ERR_FORMAT2 "Error on line %d of your idl file: unused character: %s\n"
#define OUTFILE 43
#define NOUTFILE 80
#define ARGS 90 /* max args per prototype */
#define INC 40
#define INIT  0
#define CALL 15
#define ERR Err(__LINE__)
#define IO_IN  0
#define IO_OUT 15
#define BLANK 30
#define IO_INOUT 3
#define EXE 70
#define INFILE  70   /* Max # of input files, including recursive includes */
#define INFILES 170  /*  Max size of any input, including path */
#define COL 300
#define COMMENTS 1000
#define OLC 82
#define SINGL (int)yytext[0]
#define TSIZE 21 /* big enuf for "unsigned short" */
#define CVSVERSION 100
#define MODULETAB 80 /* max number of in/out/inout table for a module */
#define INPUTTAB 80 /* max number of included tables for a module idl file */
#define MODULETABSIZE 40
#define INPUTTABSIZE 40
int gHaveIncludedPamIdl, gHaveSeen_STAFCV_T, gHaveSeen_amiModule;
int gFtc,gJj,gIi,gLN=1,gNPamNames=0,gNArgName[PROTOTYPES],gNProto=0;
int gC=7,gNColTypes=0,gNColNames=0,gNIncFile=0,gNTblName=0;

int gNmoduleTable,gNinputTable;
char gModuleTable[MODULETAB][MODULETABSIZE+1];
char gInputTable[INPUTTAB][INPUTTABSIZE+1];

char gIncDir[INCDIR][INCDIRS];
char gOrigInputFile[81];
int gNincDir,gNOutFile=0,gNoMoreComments=0;
int  gOptionH,gOptiont,gOptioni,gOptionM,gOptionstatic,gOptiondynamic;
int  gOptionf;
char gOlc[COL][OLC],gOutFile[NOUTFILE][OUTFILE+2];
char gInFile[INFILE][INFILES+1];
int gNInFile=0;
char gPass[100],gComments[COMMENTS];
char gOptioniTempFile[40],gExeName[EXE+2];
char gInFileName[INFILES+2];
char gInFileNameNoPath[INFILES+2];
char gColName[COL][ISIZE+2];
char gTable[ISIZE+2];
char gIo[PROTOTYPES][ARGS];
char gIncFile[INC][ISIZE+2];
char gL2[SZ+2],gL1[SZ+2];
char gPam[ISIZE+2],gMkCc;
char gPamUp[ISIZE+2];
char gPn[PROTOTYPES][ISIZE+2];
char gArgName[PROTOTYPES][ARGS][ISIZE+2];
char gColType[COL][TSIZE+2];
char gDataType[PROTOTYPES][ARGS][TSIZE+2];
char *gCvsVersionRaw="$Id: idl-yacc.c,v 1.1 1998/03/16 03:02:17 fisyak Exp $";
char gCvsVersion[CVSVERSION+1];
char gFncType[PROTOTYPES][TSIZE+2];
FILE *gFpH,*gFpInc,*gFile;
FILE *yyin; /* declaration for yyin made by lex is removed in Makefile */
/*********************************************************** prototypes */
void TemplateFBegin(char *fn,FILE *ff);
void Ose(void);
void Pam(void);
void TemplateFMiddle(FILE *ff);
void TemplateFEnd(FILE *ff);
void TemplateCBegin(FILE *ff);
void TemplateCMiddle(char *pamname,FILE *ff);
void TemplateCEnd(FILE *ff);
void Init(void);
void OpenAllTblOutput(void);
void HandleOneInputFile(char *inFile);
void Tbl(void);
void Usage(void);

# line 112 "../src/idl.y"
typedef union
#ifdef __cplusplus
	YYSTYPE
#endif
 { char *str; } YYSTYPE;
# define INTER 257
# define CORBA 258
# define ICALL 259
# define STRUC 260
# define PROTO 261
# define IDENT 262
# define NUMBE 263
# define INOUT 264
# define STRIN 265
# define INCLU 266
# define ARRAY 267
# define STAFC 268

#ifdef __STDC__
#include <stdlib.h>
#include <string.h>
#else
#include <malloc.h>
#include <memory.h>
#endif

#include <values.h>

#ifdef __cplusplus

#ifndef yyerror
	void yyerror(const char *);
#endif

#ifndef yylex
#ifdef __EXTERN_C__
	extern "C" { int yylex(void); }
#else
	int yylex(void);
#endif
#endif
	int yyparse(void);

#endif
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
YYSTYPE yylval;
YYSTYPE yyval;
typedef int yytabelem;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#if YYMAXDEPTH > 0
int yy_yys[YYMAXDEPTH], *yys = yy_yys;
YYSTYPE yy_yyv[YYMAXDEPTH], *yyv = yy_yyv;
#else	/* user does initial allocation */
int *yys;
YYSTYPE *yyv;
#endif
static int yymaxdepth = YYMAXDEPTH;
# define YYERRCODE 256

# line 143 "../src/idl.y"
 /************************************************************* functions */
void ToUpper(char *out,const char *in);
char *StrippedInFileName(int uppercase) {
  char *cc,tmp[100];
  strcpy(gPass,gInFileNameNoPath);
  cc=strstr(gPass,".idl"); if(cc) cc[0]=0;
  if(uppercase) { ToUpper(tmp,gPass); strcpy(gPass,tmp); }
  return gPass;
}
void DoComment(int codeLineNum,char *xx) {
  char *cc;
  if(xx[0]=='/'&&xx[1]=='/') cc=xx+2; else cc=xx;
  if(gNoMoreComments) return;
  if(strlen(cc)+strlen(gComments)>COMMENTS-13) {
    strcat(gComments,"\nCOMMENTS TRUNCATED"); gNoMoreComments=7;
  }
  strcat(gComments,cc);
}
void Fose(void) {
  fprintf(stderr,"ooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n");
}
void Idl2Fortran(char *out,const char *in) {
       if(!strcmp(in,"long"))   strcpy(out,"INTEGER*4");
  else if(!strcmp(in,"unsigned long"))   strcpy(out,"INTEGER*4");
  else if(!strcmp(in,"short"))  strcpy(out,"INTEGER*2");
  else if(!strcmp(in,"unsigned short"))  strcpy(out,"INTEGER*2");
  else if(!strcmp(in,"float"))  strcpy(out,"REAL*4");
  else if(!strcmp(in,"double")) strcpy(out,"REAL*8");
  else if(!strcmp(in,"octet")) strcpy(out,"LOGICAL*1");
  else if(!strcmp(in,"char")) strcpy(out,"CHARACTER*");
  else strcpy(out,in);
}
void ToLower(char *out,const char *in) {
  int off,ii; char cc;
  for(ii=strlen(in);ii>=0;ii--) {
    cc=in[ii]; if(cc>='A'&&cc<='Z') off='m'-'M'; else off=0; out[ii]=cc+off;
  }
}
void ToUpper(char *out,const char *in) {
  int off,ii; char cc;
  for(ii=strlen(in);ii>=0;ii--) {
    cc=in[ii]; if(cc>='a'&&cc<='z') off='A'-'a'; else off=0; out[ii]=cc+off;
  }
}
void OutputCommentsFromIdlFile(int fortranOrC,FILE *ff) {
  char *cc,buf[COMMENTS];
  if(*gComments==0) return;
  if(fortranOrC==1) {                                           /* FORTRAN */
    FF"C COMMENTS FROM IDL FILE:\n"); strcpy(buf,gComments);
    cc=strtok(buf,"\n");
    while(cc) { FF"C %s\n",cc); cc=strtok(NULL,"\n"); }
  }
  if(fortranOrC==2) {                                                 /* C */
    FF"/* COMMENTS FROM IDL FILE:\n");
    FF"%s ",gComments);
    FF"*/\n");
  }
}
void StandardBlurb(int fortranOrC,char *mode,FILE *ff) {
  if(strcmp(mode,"w")) return;
  switch(fortranOrC) {
    case 0: break;
    case 1: FF"C %s.inc\n",gTable); break;
    case 2: FF"/* %s.h */\n",gTable); break;
    default: Err(__LINE__);
  }
  if(fortranOrC==1) {
    FF"C This file was made by the idl compiler \"stic\". Do not edit.\n");
    FF"C Instead, edit the source idl file and then re-run the compiler.\n");
    FF"C For help, type contact Craig Tull or Herb Ward.\n");
  } else if(fortranOrC==2) {
    FF"/* This file was made by the idl compiler \"stic\". Do not edit.\n");
    FF"** Instead, edit the source idl file and then re-run the compiler.\n");
    FF"** For help, type contact Craig Tull or Herb Ward. */\n");
  } else ERR;
  OutputCommentsFromIdlFile(fortranOrC,ff);
}
ColType(char *xx) {
  if(gNColTypes>=COL) {
    F"You are specifying too many columns in the idl file.  Max=%d.\n",COL);
    exit(2);
  }
  if(!strcmp(xx,"int")) {
    EE"Fatal error: \"int\" is not a valid IDL data type.\n"); exit(2);
  }
  strncpy(gColType[gNColTypes],xx,TSIZE); /* big enuf for "unsigned short" */
  gNColTypes++;
}
Col(char *xx) {
  if(gNColNames>=COL) {
    F"You are specifying too many columns in the idl file.  Max=%d.\n",COL);
    exit(2);
  }
  strncpy(gColName[gNColNames],xx,ISIZE);
  gNColNames++;
  if(gNColTypes<gNColNames) {
    strcpy(gColType[gNColTypes],gColType[gNColTypes-1]); gNColTypes++;
  }
  if(gNColNames!=gNColTypes) Err(__LINE__);
}
TblName(char *xx) {
  if(strlen(xx)>INPUTTABSIZE) ERR;
  if(gNinputTable>=INPUTTAB) ERR;
  strcpy(gInputTable[gNinputTable++],xx);
  if(++gNTblName>1) { F"Only one table per idl file.\n"); exit(2); }
  strncpy(gTable,xx,ISIZE);
}
Err(int xx) {
  F"ooooooooooooooooooooooooooooooooooooooooooooooooooooo\n");
  F">>>>> STIC FATAL ERROR line %d of %s.  ward@physics.utexas.edu.\n",xx,
  __FILE__);
  exit(2);
}
void IdlToCOrCpp(char *out,char *in) {
#ifdef STUFF_FOR_64_BITS
       if(!strcmp(in,"long"))            strcpy(out,"IDL_LONG");
  else if(!strcmp(in,"unsigned long"))   strcpy(out,"IDL_ULONG");
  else if(!strcmp(in,"short"))           strcpy(out,"IDL_SHORT");
  else if(!strcmp(in,"unsigned short"))  strcpy(out,"IDL_USHORT");
  else if(!strcmp(in,"float"))           strcpy(out,"IDL_FLOAT");
  else if(!strcmp(in,"double"))          strcpy(out,"IDL_DOUBLE");
  else if(!strcmp(in,"octet"))           strcpy(out,"IDL_OCTET");
  else if(!strcmp(in,"char"))            strcpy(out,"IDL_CHAR");
#else
  if(!strcmp(in,"octet")) strcpy(out,"unsigned char");
  else strcpy(out,in);
#endif
}
char *Up(const char *x) {
  ToUpper(gPass,x); return gPass;
}
void DotHFileTbl(void) {
  char colType[111]; int ii;
  if(gOptionM) Err(__LINE__);
  FH"#ifndef %s_H\n",Up(gTable));
  FH"#define %s_H\n",Up(gTable));
  /* 960529a FH"#include \"table_header.h\"\n"); */
  FH"#define %s_SPEC \\\n",Up(gTable));
  FH"\"struct %s { \\\n",gTable);
  for(ii=0;ii<gNColNames;ii++) {
    FH"\t%s %s; \\\n",gColType[ii],gColName[ii]);
  }
  FH"};\"\n");
  FH"typedef struct %s_st {\n",gTable);
  for(ii=0;ii<gNColNames;ii++) {
    IdlToCOrCpp(colType,gColType[ii]);
    FH"\t%s %s; %s\n",colType,gColName[ii],gOlc[ii]);
  }
  FH"} %s_ST;\n",Up(gTable));
  FH"#endif /* %s_H */\n",Up(gTable));
}
void ReverseIndices(char *x) { /* FORTRAN indices are backwards */
  int dims[15];
  int ii, jj;
  char *a, *sx, buf[30];

  sx = x;
  for (ii = 0; ii < 15; ii++) {
    a = strstr(x, "("); 
    if (!a) break;
    dims[ii] = atoi(a+1);
    x = strstr(a, ")");
  }
  a = strstr(sx, "(");
  if( !a ) return;
  a[0] = 0;
  strcat(sx,"(");
  for (jj = ii; jj > 0; jj--) {
    sprintf(buf, " %d ", dims[jj-1]); strcat(sx, buf);
    if(jj>1) strcat(sx,", ");
  }
  strcat(sx,")");
}
void BracksToParens(char *out,char *xx) {
  int ii;
  strcpy(out,xx);
  for(ii=strlen(out)-1;ii>=0;ii--) {
    if(out[ii]=='[') out[ii]='(';
    if(out[ii]==']') out[ii]=')';
  }
  ReverseIndices(out);
}
void ChangeCommentFromCToFortran(char *out,char *in) {
  char *cc;
  if(strlen(in)>FORTRANCOMMENTSIZE) ERR;
  strcpy(out,in);
  cc=strstr(out,"/*");
  while(cc) { cc[0]='!'; cc[1]=' '; cc=strstr(out,"/*"); }
  cc=strstr(out,"*/");
  while(cc) { cc[0]='0'; cc[1]=' '; cc=strstr(out,"*/"); }
}
void DotIncFileTbl(void) {
  char buf2[111],*cc,buf[111],fortran[77],uppercase[111],blank[BLANK];
  char fortranComment[FORTRANCOMMENTSIZE+1];
  int col,ii,nn,totLen,here;
  ToUpper(uppercase,gTable);
  FINC"#ifndef %s_INC\n",uppercase);
  FINC"#define %s_INC\n",uppercase);
  FINC"#endif\n");
  /* 960529b  FINC"#include \"table_header.inc\"\n"); */
  FINC"\tSTRUCTURE /%s_ST/\n",uppercase);
  for(col=0;col<gNColNames;col++) {
    Idl2Fortran(fortran,gColType[col]);
    if(strcmp(gColType[col],"char")) {
      BracksToParens(buf,gColName[col]);
    } else {
      strcpy(buf,gColName[col]); cc=strstr(buf,"[");
      if(cc) {
        if(!strstr(cc,"]")) { F"Crummy stuff: %s.\n",gColName[col]); exit(2); }
        nn=atoi(cc+1); cc[0]=0; sprintf(buf2,"%s%d",fortran,nn);
      } else sprintf(buf2,"%s1",fortran);
      strcpy(fortran,buf2);
    }
    ChangeCommentFromCToFortran(fortranComment,gOlc[col]);
    FINC"\t%9s %s %s\n",fortran,buf,fortranComment);
  }
  FINC"\tEND STRUCTURE\n");

  /* new as of 960429 ----------------------------*/
  FINC"C\n");
  FINC"      CHARACTER*(*) %s_SPEC\n",Up(gTable));
  FINC"      PARAMETER    (%s_SPEC=\n",Up(gTable));
  for(ii=BLANK-1;ii>=0;ii--) blank[ii]=' '; blank[BLANK-1]=0;
  totLen=strlen(gTable)+7;
  here=BLANK-totLen; if(here>=0&&here<BLANK) blank[here]=0; else blank[0]=0;
  FINC"     + ' struct %s {' %s //\n",gTable,blank);
  for(col=0;col<gNColNames;col++) {
    for(ii=BLANK-1;ii>=0;ii--) blank[ii]=' '; blank[BLANK-1]=0;
    totLen=strlen(gColType[col])+strlen(gColName[col]);
    here=BLANK-totLen; if(here>=0&&here<BLANK) blank[here]=0; else blank[0]=0;
    FINC"     + ' %s %s;' %s //\n",gColType[col],gColName[col],blank);
  }
  FINC"     + ' };')\n");
  FINC"C\n");
}
void Tbl(void) {
  if(gOptiont) {
    Ose(); PP"You have used option -t with a table-type idl file.\n");
    PP"This does not make sense.  The option -t means 'templates\n");
    PP"only', and there is no such thing as a template derived from a\n");
    PP"table-type idl file.\n");
    PP"FATAL ERROR   FATAL ERROR   FATAL ERROR   FATAL ERROR   \n");
    exit(2);
  }
  OpenAllTblOutput();
  if(gOptionM) return;
  DotHFileTbl(); DotIncFileTbl();
}
DumpGlobalsPam(void) {
  int ii,jj; char buf[5];
  P"The name of the PAM is %s, %d include files, %d prototypes.\n","xyz",
  gNIncFile,gNProto);
  for(ii=0;ii<gNIncFile;ii++) {
    P"Include file %d: %s.\n",ii+1,gIncFile[ii]);
  }
  for(ii=0;ii<gNProto;ii++) {
    P"Prototype %d: fncName=%s, %d args.\n",ii+1,gPn[ii],gNArgName[ii]);
    P"  Args:\n");
    for(jj=0;jj<gNArgName[ii];jj++) {
      if(gIo[ii][jj]==IO_IN) strcpy(buf,"in");
      else if(gIo[ii][jj]==IO_OUT) strcpy(buf,"out");
      else if(gIo[ii][jj]==IO_INOUT) strcpy(buf,"inout");
      else Err(__LINE__);
      P"    %s %s %s\n",buf,gDataType[ii][jj],gArgName[ii][jj]);
    }
  }
  exit(2);
}
void ModeFromFn(char *fn,char *mode) {
  int ii;
  for(ii=gNOutFile-1;ii>=0;ii--) { if(!strcmp(fn,gOutFile[ii])) break; }
  if(ii<0) {
    if(gNOutFile>=NOUTFILE) Err(__LINE__);
    strncpy(gOutFile[gNOutFile++],fn,OUTFILE); strcpy(mode,"w");
  } else {
    strcpy(mode,"a");
  }
}
void ExtendOutList(char *fn) {
  char junk[12];
  ModeFromFn(fn,junk);
}
void StripOffIdl(char *in,char *out) {
  char *cc,buf[123],*xx; int ii;
  strcpy(buf,in);
  for(ii=strlen(buf);ii>=0;ii--) if(buf[ii]=='/') break; xx=buf+ii+1;
  cc=strstr(xx,".idl"); if(cc==NULL) Usage(); cc[0]=0; strcpy(out,xx);
}
FILE *OpenOnePamOutput(char *x) {
  char mode[3],fn[111],buf[111]; int fortranOrC;
  if(strstr(x,".h")) fortranOrC=2;
  else if(strstr(x,".inc")) fortranOrC=1; else ERR;
  StripOffIdl(gInFileNameNoPath,buf);
  sprintf(fn,"%s%s",buf,x);
  ModeFromFn(fn,mode);
  if(gOptionM) return NULL;
  gFile=fopen(fn,mode); /* gOptionf OK */
  if(!strcmp(mode,"w")) PP"  out: %s\n",fn);
  StandardBlurb(fortranOrC,mode,gFile);
  if(gFile==NULL) { F"Can't write %s.\n",fn); exit(2); }
  return gFile;
}
void PrintTheArgs(FILE *ff,int ii) {
  int jj; char ast[2],comma[12],headerName[111],tableType[111],up[111];
  for(jj=0;jj<gNArgName[ii];jj++) {
    if(gIo[ii][jj]==IO_IN) *ast=0;
    else if(gIo[ii][jj]==IO_OUT) strcpy(ast,"*");
    else if(gIo[ii][jj]==IO_INOUT) strcpy(ast,"*");
    else Err(__LINE__);
    if(jj==gNArgName[ii]-1) strcpy(comma,""); else strcpy(comma,",");
    sprintf(headerName,"*%s_h",gArgName[ii][jj]);
    ToUpper(up,gDataType[ii][jj]);
    sprintf(tableType,"%s_ST",up);
    FF"  TABLE_HEAD_ST  %16s, %16s    *%s_d %s\n",
    headerName,tableType,gArgName[ii][jj],comma);
  }
  FF");\n");
}
void Eose(void) {
  EE"----------------------------------------------------------------\n");
}
void Ose(void) {
  if(gOptionM) return;
  PP"----------------------------------------------------------------\n");
}
void PamOutputDotHFile(void) {
  char dt[22],ast[2],comma[12],fName[60],headerName[111];
  char didPam=0,*cc,tmp2[99],tableType[111],tmp[99];
  int ii,jj,initOrCall;
  FILE *ff;
  /* Q14 */
  ff=OpenOnePamOutput(".h"); if(gOptionM) return;
  FF"/* %s.h */\n",StrippedInFileName(0));
  FF"#ifndef %s_H\n",StrippedInFileName(7));
  FF"#define %s_H\n",StrippedInFileName(7));
  FF"/*----------------------------------------------- INCLUDES   --*/\n");
  for(ii=0;ii<gNIncFile;ii++){
    strcpy(tmp,gIncFile[ii]);
    cc=strstr(tmp,".idl"); if(cc!=NULL) *cc=0; /* don't del, modifies tmp */
    if(!strcmp(tmp,"\"asu")) ToUpper(tmp2,tmp); else strcpy(tmp2,tmp);
    if(strcmp(tmp2,"\"ASU")) {
      FF"#include %s.h\"\n",tmp2);
      /* BBB PP"tmp2=%s.\n",tmp2); Sleep(1); */
      if(!strcmp(tmp2,"\"PAM")) didPam=7;
    } else {
      P"\n\n"); Ose(); 
      P"%cWARNING: Please ",7);
      P"remove '#include ASU.idl' from the input file.\n\n"); sleep(6);
    }
  }
  if(!didPam) FF"#include \"%s.h\"\n","PAM"); /* 960529c */
  FF"/*----------------------------------------------- MACROS     --*/\n");
  if(gNProto!=1) Err(__LINE__);
  if(gNArgName[gNProto-1]<0) Err(__LINE__);
  FF"#define %s_RANK %d\n",gPamUp,gNArgName[gNProto-1]);
  FF"/*----------------------------------------------- FORTRAN NAMES  --*/\n");
  FF"#ifdef F77_NAME\n#define %s_ F77_NAME(%s,%s)\n#endif\n",gPam,gPam,gPamUp);
  FF"#ifndef type_of_call\n#define type_of_call\n#endif\n");
  FF"/*----------------------------------------------- TYPEDEFS   --*/\n");
  FF"typedef STAFCV_T (type_of_call *%s_FT)\n(\n",gPamUp);
  if(gNProto!=1) Err(__LINE__); /* PrintTheArgs needs protection from arg2=0 
    if gNProto!=1. */
  PrintTheArgs(ff,0);	/* comment 917a, if gNProto!=1, may need arg2!=0 */
  for(ii=0;ii<gNProto;ii++) { /* gNProto always = 1 (2??) */
    if(!strcmp(gPn[ii],"initialize")) {
      sprintf(fName,"%s_initialize",gPam); initOrCall=INIT;
    } else if(!strcmp(gPn[ii],"call")) {
      sprintf(fName,"%s_",gPam); initOrCall=CALL;
    } else {
      Err(__LINE__);
    }
    FF"/*----------------------------------------------- PROTOTYPES --*/\n");
    FF"extern CC_P STAFCV_T type_of_call %s (\n",fName); /* pam.h */
    if(initOrCall==INIT&&0) { /* 960215 disabled, not in CET's examples */
      for(jj=0;jj<gNArgName[ii];jj++) {
        if(gIo[ii][jj]==IO_IN) *ast=0;
        else if(gIo[ii][jj]==IO_OUT) strcpy(ast,"*");
        else if(gIo[ii][jj]==IO_INOUT) strcpy(ast,"*");
        else Err(__LINE__);
        if(jj==gNArgName[ii]-1) strcpy(comma,"\n);"); else strcpy(comma,",");
        if(!strcmp(gDataType[ii][jj],"string")) {
          strcpy(dt,"char"); strcpy(ast,"*");
        } else strcpy(dt,gDataType[ii][jj]);
        FF"  %15s %1s %s %s\n",dt,ast,gArgName[ii][jj],comma);
      }
    } else if(initOrCall==CALL) {
      PrintTheArgs(ff,ii);
    } else Err(__LINE__);
  }
  FF"#ifdef __cplusplus\n");
  /* Q01 */
/*
  FF"extern CC_P const char * %s_version();\n",gPam);
*/
  FF"extern CC_P STAFCV_T %s_load_ami(amiBroker *broker);\n",gPam); /* pam.h */
  FF"#endif /* __cplusplus */\n");
  FF"#endif /* %s_H */\n",StrippedInFileName(7));
  fclose(ff);
}
void StarFortranComment(int initOrCall,FILE *ff) {
  int type,lookfor,jj; char *label,headerName[111];
  if(initOrCall==CALL) {
    for(type=0;type<3;type++) {
      switch(type) {
        case 0: lookfor=IO_IN; label="IN"; break;
        case 1: lookfor=IO_INOUT; label="INOUT"; break;
        case 2: lookfor=IO_OUT; label="OUT"; break;
      }
      FF"CC:       %5s:\n",label);
      for(jj=0;jj<gNArgName[0];jj++) {
        if(gIo[0][jj]!=lookfor) continue;
        sprintf(headerName,"%s_h",gArgName[0][jj]);
        FF"CC:  %15s     - description here\n",gArgName[0][jj]);
        FF"CC:  %15s     - Header Structure for %s\n",headerName,
        gArgName[0][jj]);
      }
    }
  }
}
void PamTemplateFortran(void) {
  char headerName[111],tableType[111],fn[100]; FILE *ff; int ii,jj,initOrCall;
  int continuation; char comma[17],fName[111];
  /* Q02 */
  sprintf(fn,"%s.F.template",StrippedInFileName(0));
  if(gOptionM) { ExtendOutList(fn); return; }
  if(gOptionf) return; ff=fopen(fn,"w"); /* PamTemplateFortran() */
  if(ff==NULL) { F"Can't write %s.\n",fn); exit(2); }

  TemplateFBegin(fn,ff);
  FF"      INTEGER*4 FUNCTION %s(\n",gPamUp);
  for(ii=0;ii<gNProto;ii++) {
    if(!strcmp(gPn[ii],"initialize")) initOrCall=INIT;
    else if(!strcmp(gPn[ii],"call")) initOrCall=CALL;
    else Err(__LINE__);
    if(initOrCall==CALL) {
      for(jj=0;jj<gNArgName[ii];jj++) {
        if(jj==gNArgName[ii]-1) strcpy(comma,") "); else strcpy(comma,",");
        sprintf(headerName,"%s_h",gArgName[ii][jj]);
        continuation=jj+1; if(continuation>9) continuation=9;
        FF"     %d   %17s, %17s %s\n",
        continuation,headerName,gArgName[ii][jj],comma);
      }
    }
  }
  FF"      IMPLICIT NONE\n");
  /* Q03 */
  FF"#include \"%s.inc\"\n",StrippedInFileName(0));
  TemplateFMiddle(ff);
  if(gNProto!=1) ERR; StarFortranComment(initOrCall,ff);
  TemplateFEnd(ff);
  fclose(ff); F"  out: %s\n",fn);
}
void PamCC(void) {
  char headerName[111],tableType[111],fn[100]; FILE *ff; int ii,jj,initOrCall;
  char sh[89],st[89],comma[17],fName[111],withAsterisk[79];
  if(!gMkCc) return;
  /* Q04 */
  sprintf(fn,"%s_i.cc",StrippedInFileName(0));
  if(gOptionM) { ExtendOutList(fn); return; }
  if(gOptionf) return; ff=fopen(fn,"w");  /* PamCC() */
  if(ff==NULL) { F"Can't write %s.\n",fn); exit(2); }
  FF"/*------------------------------------------------------------------\n");
  /* Q05 */
  FF"FILE:         %s_i.cc\n",StrippedInFileName(0));
  FF"DESCRIPTION:  Interface functions for %s\n",gPam);
  FF"AUTHOR:       cet - Craig E. Tull, cetull@lbl.gov\n");
  FF"BUGS:         Should be automatically generated\n");
  FF"HISTORY:      putDateHere-v000a-hpl- Creation.\n");
  FF"*/\n");
  FF"/*------------------------------------------- INCLUDES            */\n");
  FF"#include <stdio.h>\n");
  FF"#include <stdlib.h>\n");
  FF"#include <string.h>\n");
  /* FF"#include \"ASU.h\"\n"); 960529d */
  /* FF"#include \"AMI.h\"\n"); 960529e */
  /* Q06 */
  FF"#include \"%s.h\"\n",StrippedInFileName(0));
  FF"/*------------------------------------------ TYPEDEFS             */\n");
  FF"/*------------------------------------------ GLOBALS              */\n");
  FF"/*------------------------------------------ PROTOTYPES           */\n");
  FF"/*\n");
  FF"*:>----------------------------------------------------------------\n");
  /* Q07 */
  FF"*:ROUTINE:      STAFCV_T %s_load_ami()\n",gPam);
  /* Q08 */
  FF"*:DESCRIPTION:  Initialize %s\n",gPam);
  FF"*:ARGUMENTS:    amiBroker *broker       - broker for AMI object\n");
  FF"*:RETURN VALUE: TRUE or FALSE\n");
  FF"*:<----------------------------------------------------------------\n");
  FF"*/\n");
  /* Q09 */
/*
  FF"const char *%s_version() {\n",gPam);
  FF"  const char *v=\"@(#) $%s$\";\n","Id:");
  FF"  return v;\n");
  FF"}\n");
*/
  FF"STAFCV_T %s_load_ami(amiBroker *broker)\n{\n",gPam);
  FF"%s_FT %s_call = %s_;\n",gPamUp,gPam,gPam); /* pam_i.cc */
  /* FF"  printf(\"%s_load_ami: Starting ####\");\n",gPam); 960606 */
  /* FF"  printf(\"####################\\n\");\n"); 960606 */
  FF"  STRING_SEQ_T specs;\n");
  FF"  specs._length = specs._maximum = %s_RANK;\n",gPamUp);
  FF"  specs._buffer = new char*[%s_RANK];\n",gPamUp);
  FF"\n");
  for(ii=0;ii<gNArgName[gNProto-1];ii++) {
    FF"  specs._buffer[%d] = new char[strlen(%s_SPEC)+1];\n",ii,
    Up(gDataType[gNProto-1][ii]));
    FF"  strcpy(specs._buffer[%d],%s_SPEC);\n",ii,
    Up(gDataType[gNProto-1][ii]));
  }
  FF"\n");
  FF"  broker->newInvoker(\"%s\",%s_RANK\n",gPam,gPamUp);


  FF"               ,(FNC_PTR_T)%s_call ,specs             );\n",gPam);
/*
  FF"               ,(FNC_PTR_T)%s_call ,specs,%s_version());\n",gPam,gPam);
*/


  FF"  for( int i=0;i<specs._maximum;i++ ){\n");
  FF"     delete specs._buffer[i];\n");
  FF"  }\n");
  FF"  delete[] specs._buffer;\n");
  /* FF"  printf(\"%s_load_ami: Normal conclusion ##\");\n",gPam); 960606 */
  FF"  printf(\"%s module loaded\\n\");\n",gPam);
  /* FF"  printf(\"\\n\");\n"); 960606 */
  FF"  return TRUE;\n");
  FF"}\n");
  fclose(ff); F"  out: %s\n",fn);
}
void PamTemplateC(void) {
  int type,lookfor;
  char headerName[111],tableType[111],fn[100]; FILE *ff; int ii,jj,initOrCall;
  char *label,sh[89],st[89],comma[17],fName[111],withAsterisk[79];
  /* Q10 */
  sprintf(fn,"%s.c.template",StrippedInFileName(0));
  if(gOptionM) { ExtendOutList(fn); return; }
  if(gOptionf) return; ff=fopen(fn,"w"); /* PamTemplateC() */
  if(ff==NULL) { F"Can't write %s.\n",fn); exit(2); }
  TemplateCBegin(ff);
  /* Q11 */
  FF"#include \"%s.h\"\n\n",StrippedInFileName(0));
  /* Q12 */
  FF"long %s_(\n",gPam);
  for(ii=0;ii<gNProto;ii++) {
    if(!strcmp(gPn[ii],"initialize")) initOrCall=INIT;
    else if(!strcmp(gPn[ii],"call")) initOrCall=CALL;
    else Err(__LINE__);
    if(initOrCall==CALL) {
      for(jj=0;jj<gNArgName[ii];jj++) {
        if(jj==gNArgName[ii]-1) strcpy(comma,")\n{"); else strcpy(comma,",");
        sprintf(headerName,"*%s_h",gArgName[ii][jj]);
        sprintf(tableType,"%s_ST",Up(gDataType[ii][jj]));
        if(jj==0) { strcpy(sh,headerName); strcpy(st,gArgName[ii][jj]); }
        sprintf(withAsterisk,"*%s",gArgName[ii][jj]);
        FF"  TABLE_HEAD_ST %17s, %17s %17s %s\n",
        headerName,tableType,withAsterisk,comma);
      }
    }
  }
  TemplateCMiddle(gInFileNameNoPath,ff);
  for(ii=0;ii<gNProto;ii++) {
    if(!strcmp(gPn[ii],"initialize")) initOrCall=INIT;
    else if(!strcmp(gPn[ii],"call")) initOrCall=CALL;
    else Err(__LINE__);
    if(initOrCall==CALL) {
      for(type=0;type<3;type++) {
        switch(type) {
          case 0: lookfor=IO_IN; label="IN"; break;
          case 1: lookfor=IO_INOUT; label="INOUT"; break;
          case 2: lookfor=IO_OUT; label="OUT"; break;
        }
        FF"**:    %5s:\n",label);
        for(jj=0;jj<gNArgName[ii];jj++) {
          if(gIo[0][jj]!=lookfor) continue;
          FF"**:  %17s    - PLEASE FILL IN DESCRIPTION HERE\n",
          gArgName[ii][jj]);
          FF"**:  %16s_h   - header Structure for %s\n",
          gArgName[ii][jj], gArgName[ii][jj]);
        }
      }
    }
  }
  TemplateCEnd(ff);
  fclose(ff); F"  out: %s\n",fn);
}
void GenerateStaticLenght(const char *in,char *out) {
  strcpy(out,in); strcat(out,"_h.maxlen");
}
void PamOutputDotIncFile(void) {
  char *cc,theType[111],tmp[99],ooo[99]; int doup,initOrCall,ii,jj;
  char havePam=0,tableType[100],headerName[100],buf[83];
  FILE *ff;
  /* Q13 */
  ff=OpenOnePamOutput(".inc"); if(gOptionM) return;
  FF"C   %s.inc\n",StrippedInFileName(0));
  FF"#ifndef %s_INC\n",StrippedInFileName(7));
  FF"#define %s_INC\n",StrippedInFileName(7));
  FF"#endif\n");
  for(ii=0;ii<gNIncFile;ii++) {
    if(!strcmp(gIncFile[ii],"\"PAM.idl\"")) havePam=7;
  }
  if(!havePam) FF"#include \"%s.inc\"\n","PAM"); /* 960529f */
  for(ii=0;ii<gNIncFile;ii++) {
    strcpy(tmp,gIncFile[ii]); doup=0;
    cc=strstr(tmp,".idl"); if(cc!=NULL) *cc=0; /* dont del, modifies tmp */
    if(doup) ToUpper(ooo,tmp); else strcpy(ooo,tmp);
    if(strcmp(ooo,"ASU")&&strcmp(ooo,"asu")) FF"#include %s.inc\"\n",ooo);
  }
  if(gNProto!=1) Err(__LINE__);
  if(gNArgName[gNProto-1]<0) Err(__LINE__);
  FF"      INTEGER*4 %s_RANK\n",gPamUp);
  FF"      PARAMETER (%s_RANK=%d)\n",gPamUp,gNArgName[gNProto-1]);
  for(ii=0;ii<gNProto;ii++) {	/* moved from .F file 960215 */
    if(!strcmp(gPn[ii],"initialize")) initOrCall=INIT;
    else if(!strcmp(gPn[ii],"call")) initOrCall=CALL;
    else Err(__LINE__);
    if(initOrCall==CALL) {
      for(jj=0;jj<gNArgName[ii];jj++) {
        sprintf(headerName,"%s_h",gArgName[ii][jj]);
        sprintf(tableType,"/%s_ST/",Up(gDataType[ii][jj]));
        FF"      RECORD %20s %23s\n","/TABLE_HEAD_ST/",headerName);
        if(gOptionstatic) {
          GenerateStaticLenght(gArgName[ii][jj],buf);
          FF"      RECORD %20s %20s(%s)\n",tableType,gArgName[ii][jj],buf);
        } else if(gOptiondynamic) {
          sprintf(buf,"%s_d",gArgName[ii][jj]);
          FF"      RECORD %20s %20s(*)\n",tableType,buf);
          FF"      POINTER (%s,%s)\n",gArgName[ii][jj],buf);
        } else {
          FF"      RECORD %20s %20s(*)\n",tableType,gArgName[ii][jj]);
        }
      }
    }
  }
  fclose(ff);
}
#define MARGIN 2
void Banner(char *xx) { /* makes a big obnoxious banner from input x */
  int ii,line,len; char x[100];
  sprintf(x," %s ",xx);
  len=strlen(x);
  PP"%c",7);
  if(len+2*MARGIN>80) {
    PP"%s\n",x);
  } else {
    for(line=0;line<7;line++) {
      for(ii=MARGIN-1;ii>=0;ii--) PP"X");
      switch(line) {
        case 0: case 1: case 5: case 6: for(ii=len-1;ii>=0;ii--) PP"X"); break;
        case 2: case 4: for(ii=len-1;ii>=0;ii--) PP" "); break;
        case 3: PP"%s",x);
      }
      for(ii=MARGIN-1;ii>=0;ii--) PP"X");
      PP"\n");
    }
  }
  sleep(5);
}
void CheckForPamIdl(void) {
  if(gHaveIncludedPamIdl) return;
  if(gHaveSeen_STAFCV_T) {
    Ose();
    printf("XX\n");
    printf("XX Fatal error.\n");
    printf("XX (semantic): Identifier 'STAFCV_T' undefined.\n");
    printf("XX #include \"PAM.idl\" as 1st include.\n");
    printf("XX\n");
    exit(2);
  }
  if(gHaveSeen_amiModule) {
    Ose();
    printf("XX\n");
    printf("XX Fatal error.\n");
    printf("XX (semantic): Identifier 'amiModule' undefined.\n");
    printf("XX #include \"PAM.idl\" as 1st include.\n");
    printf("XX\n");
    exit(2);
  }
}
void CheckThatAllTablesHaveBeenIncluded(void) {
  int i,j; char ok,junk[10];
  for(i=0;i<gNmoduleTable;i++) {
    ok=0;
    for(j=0;j<gNinputTable;j++) {
      if(!strcmp(gModuleTable[i],gInputTable[j])) { ok=7; break; }
    }
    if(!ok) {
      Ose();
      PP"%cWARNING FROM STIC:  you did not include an IDL file ",7);
      PP"for table\n");
      PP"type '%s', which is mentioned in %s.\n",
      gModuleTable[i],gOrigInputFile); 
      PP"Press return to continue.   "); gets(junk);
    }
  }
}
void Pam(void) {
                               CheckForPamIdl();
                               /*DumpGlobalsPam();*/
  if( !gOptiont              ) PamOutputDotIncFile();
  if( !gOptiont              ) PamOutputDotHFile();
                               /*PamOutputDotHHFile();*/
  if(              !gOptionH ) PamTemplateC();
  if( !gOptiont && !gOptionH ) PamCC();
  if(              !gOptionH ) PamTemplateFortran();
 }
IncludeFileName(char *io) {
  if(gNIncFile>=INC) { F"Too many include files, max=%d.\n",INC); exit(2); }
  strncpy(gIncFile[gNIncFile++],io,ISIZE);
}
InOut(char *io) {  /* STEP 1 */
  int whichProto; whichProto=gNProto-1;
  if(gNProto<1) Err(__LINE__);
  if(gNArgName[whichProto]>=ARGS) {
    F"No more than %d arguments per prototype.\n",ARGS); exit(2);
  }
  if(!strcmp(io,"in")) gIo[whichProto][gNArgName[whichProto]]=IO_IN;
  else if(!strcmp(io,"out")) gIo[whichProto][gNArgName[whichProto]]=IO_OUT;
  else if(!strcmp(io,"inout")) gIo[whichProto][gNArgName[whichProto]]=IO_INOUT;
  else Err(__LINE__);
}
ArgType(char *theName) {  /* STEP 2 */
  int whichProto; whichProto=gNProto-1;
  if(strlen(theName)>MODULETABSIZE) ERR;
  if(gNmoduleTable>=MODULETAB) ERR;
  strcpy(gModuleTable[gNmoduleTable++],theName);
  if(gNProto<1) Err(__LINE__);
  if(gNArgName[whichProto]>=ARGS) {
    F"No more than %d arguments per prototype.\n",ARGS); exit(2);
  }
  strncpy(gDataType[whichProto][gNArgName[whichProto]],theName,TSIZE);
}
ArgName(char *theName) {  /* STEP 3 */
  int whichProto; whichProto=gNProto-1;
  if(gNProto<1) Err(__LINE__);
  if(gNArgName[whichProto]>=ARGS) {
    F"No more than %d arguments per prototype.\n",ARGS); exit(2);
  }
  strncpy(gArgName[whichProto][gNArgName[whichProto]++],theName,ISIZE);
}
/*--------------------------------------------  961113
void CheckForEqualityWithInputName(void) {
  char xxx[123],yyy[123];
  StripOffIdl(gInFileNameNoPath,xxx);
  if(strcmp(xxx,gPam)) {
    Ose();
    EE"Fatal error in file %s:\n",gInFileName);
    EE"The name of the interface (%s) does not\n",gPam);
    EE"match the file name (%s).\n",gInFileNameNoPath);
    EE"Either rename the file %s.idl, or\n",gPam);
    EE"change the name of the interface in the file to %s.\n",xxx);
    EE"Eg: interface %s : ...\n",xxx);
    exit(2);
  }
}
----------------------------------------------------*/
PamName(char *theName) {
  gNPamNames++;
  if(gNPamNames>1) { F"Only one interface definition per file.\n"); exit(2); }
  strncpy(gPam,yylval.str,ISIZE);
  /* 961113 CheckForEqualityWithInputName(); */
  ToUpper(gPamUp,gPam);
}
FncType(char *theName) {
  if(gNProto>=PROTOTYPES) {
     F"Too many prototype names (max %d).\n",PROTOTYPES); exit(2);
  }
  strncpy(gFncType[gNProto],theName,TSIZE);
}
PrototypeName(char *theName) {
  if(gNProto>=PROTOTYPES) {
     F"Too many prototype names (max %d).\n",PROTOTYPES); exit(2);
  }
  strncpy(gPn[gNProto++],theName,ISIZE);
}
void Init(void) {
  int ii,jj;

  gNoMoreComments=0; *gComments=0;

  gLN=1; gNPamNames=0; gNProto=0; gC=7; gNColTypes=0;
  gNColNames=0; gNIncFile=0; gNTblName=0;

  for(ii=PROTOTYPES-1;ii>=0;ii--) gNArgName[ii]=0;

  gTable[0]='\0'; gL2[0]='\0'; gL1[0]='\0'; gPam[0]='\0';
  gPamUp[0]='\0';

  for(ii=COL-1;ii>=0;ii--) gColName[ii][0]='\0';
  for(ii=PROTOTYPES-1;ii>=0;ii--) gIo[ii][0]='\0';
  for(ii=INC-1;ii>=0;ii--) gIncFile[ii][0]='\0';
  for(ii=PROTOTYPES-1;ii>=0;ii--) gPn[ii][0]='\0';
  for(ii=COL-1;ii>=0;ii--) gColType[ii][0]='\0';
  for(ii=PROTOTYPES-1;ii>=0;ii--) gFncType[ii][0]='\0';


  for(ii=PROTOTYPES-1;ii>=0;ii--) {
    for(jj=ARGS-1;jj>=0;jj--) {
       gArgName[ii][jj][0]='\0';
      gDataType[ii][jj][0]='\0';
    }
  }
}
void Help(void) {
 char junk[88];
 P"For help is using STIC with STAF, write CETull@lbl.gov or\n");
 P"ward@physics.utexas.edu\n");
 Usage();
}
void Usage(void) {
  F"Usage: %s [-h?Mivft] [-Iincdir] [-static|-dynamic] [xxx.idl]\n",
  gExeName);
  F"All options are optional.\n");
  F"\n");
  F"You can type multiple options on the command line with a single\n");
  F"dash (eg, %s -ti xxx.idl).\n",gExeName);
  F"This does not imply that all option combinations are sensible.\n");
  F"\n");
  F"You don't need an input idl file for options h and v.\n");
  F"\n");
  F"-? Prints this usage message and then immediately quit.\n");
  F"-dynamic Dynamic tables.\n");
  F"-f Produce only header files (.h and .inc).\n");
  F"-h Prints this usage message and then immediately quit.\n");
  F"-H Produce only the header   files.\n");
  F"-i Ignore case (upper converted to lower).\n");
  F"-I Mechanism for specifying list of include directories.\n");
  F"-M Write string to stdout for use in a Makefile, no other output.\n");
  F"-static  Static tables.\n");
  F"-t Produce only the template files.\n");
  F"-v Write version info to stdout, no other output is produced.\n");
  exit(2);
}
void OpenAllTblOutput(void) {
  char mode[3],*xx,*cc,fn[111],zz[111]; int ii;
  strcpy(zz,gInFileName);
  for(ii=strlen(zz);ii>=0;ii--) if(zz[ii]=='/') break; xx=zz+ii+1;
  cc=strstr(xx,".idl"); if(cc==NULL) Usage(); cc[0]=0;

  sprintf(fn,"%s.inc",xx); ModeFromFn(fn,mode);
  if(gOptionM) {
    ExtendOutList(fn);
  } else {
    gFpInc=fopen(fn,mode); /* gOptionf OK */
    if(gFpInc==NULL) { F"Can't write %s.\n",fn); exit(2); }
    if(!gOptionM&&!strcmp(mode,"w")) P"  out: %s\n",fn);
    StandardBlurb(1,mode,gFpInc);
  }

  sprintf(fn,"%s.h",xx); ModeFromFn(fn,mode);
  if(gOptionM) {
    ExtendOutList(fn);
  } else {
    gFpH=fopen(fn,mode); /* gOptionf OK */
    if(gFpH==NULL) { F"Can't write %s.\n",fn); exit(2); }
    if(!gOptionM&&!strcmp(mode,"w")) P"  out: %s\n",fn); 
    StandardBlurb(2,mode,gFpH);
  }
}
int FirstCharsSame(const char *x,const char *y) {
  int len1,ii,len2;
  len1=strlen(x); len2=strlen(y);
  if(len2<len1) len1=len2;
  for(ii=len1-1;ii>=0;ii--) { if(x[ii]!=y[ii]) return 0; }
  return 7;
}
void SetYyinFilePtr(char *xx) {
  FILE *ff; char line[203]; int qq,ii;
  yyin=fopen(xx,"r");
  if(yyin==NULL) {
    F"I can't read %s.  Check existence and permissions.\n",xx); exit(2);
  }
  if(gOptioni) {
    ff=fopen(gOptioniTempFile,"w"); /* gOptionf OK */
    if(!ff) { PP"Fatal error: can't write %s.\n",gOptioniTempFile); exit(2); }
    while(fgets(line,200,yyin)) {
      qq=0;
      for(ii=0;line[ii];ii++) {
        if(line[ii]=='\"') qq++; if(qq%2==1) continue;
        if(FirstCharsSame(line+ii,"STAFCV_T")) { ii+=8; continue; }
        if(line[ii]>='A'&&line[ii]<='Z') line[ii]+='a'-'A';
      }
      fprintf(ff,"%s",line);
    } fclose(ff); fclose(yyin);
    yyin=fopen(gOptioniTempFile,"r");
  }
}
void DoOneLineComment(char *x) {
  int ii;
  if(gNColNames>0&&gNColNames<=COL&&gFtc>=0&&gFtc<COL) {
    for(ii=gFtc;ii<gNColNames;ii++) {
      if(strlen(x)>=OLC) Err(__LINE__);
      if(ii==gFtc) strcpy(gOlc[ii],x); else strcpy(gOlc[ii],"/* ditto */");
    }
  }
}
void CheckSelfConsistencyOfOptions(void) {
  if(gOptionstatic&&gOptiondynamic) {
    Ose(); P"Don't use both -dynamic and -static on command line.\n"); exit(2);
  }
}
void TooManyIncs(void) {
  EE"You have too many \"-I\"s on the command line.  Max=%d.\n",INCDIR);
}
void PrintVersionAndExit(void) {
  printf("%s\n",gCvsVersion); exit(0);
}
void TypeIncDirs(FILE *xx) {
  int ii;
  fprintf(xx,"------------------------\n");
  for(ii=0;ii<gNincDir;ii++) fprintf(xx,"%s/\n",gIncDir[ii]);
  fprintf(xx,"------------------------\n");
 }
void DumpOptionsAndExit(void) {
  PP"%20s %d\n","gOptionM",gOptionM);
  PP"%20s %d\n","gOptionf",gOptionf);
  PP"%20s %d\n","gOptiondynamic",gOptiondynamic);
  PP"%20s %d\n","gOptioni",gOptioni);
  PP"%20s %s\n","gOptioniTempFile",gOptioniTempFile);
  PP"%20s %d\n","gOptionstatic",gOptionstatic);
  PP"%20s %d\n","gOptionH",gOptionH);
  PP"%20s %d\n","gOptiont",gOptiont);
  exit(2);
}
void ReadOptions(int nnn,char *aaa[]) {
  int jj,filenameCount=0,ii; char die=0;
  gOptionstatic=0; gOptiondynamic=0; gOptionM=0; gOptioni=0; gOptionH=0;
  gOptiont=0; gOptionf=0;
  gNincDir=0; strcpy(gIncDir[gNincDir++],".");
  for(ii=1;ii<nnn;ii++) {
    if(aaa[ii][0]=='-') {
           if(!strcmp(aaa[ii]+1,"dynamic")) gOptiondynamic=7;
      else if(!strcmp(aaa[ii]+1,"static"))  gOptionstatic=7;
      else if(aaa[ii][1]=='I') {
        if(gNincDir>INCDIR) TooManyIncs();
        strcpy(gIncDir[gNincDir++],aaa[ii]+2);
      } else {  /* single-letter options may be combined (eg, -it) */
        for(jj=1;aaa[ii][jj];jj++) {
               if(aaa[ii][jj]=='H') gOptionH=7;
          else if(aaa[ii][jj]=='t') gOptiont=7;
          else if(aaa[ii][jj]=='M') gOptionM=7;
          else if(aaa[ii][jj]=='f') gOptionf=7;
          else if(aaa[ii][jj]=='i') gOptioni=7;
          else if(aaa[ii][jj]=='h') Usage();
          else if(aaa[ii][jj]=='?') Usage();
          else if(aaa[ii][jj]=='v') PrintVersionAndExit();
          else {
            Ose(); PP"Unknown option: %s\n",aaa[ii]); Usage();
          }
        }
      }
    } else {      /* command line arg aaa[ii] is the input file name */
      for(jj=strlen(aaa[ii])-1;jj>=0;jj--) if(aaa[ii][jj]=='/') break;
      strncpy(gInFileNameNoPath,aaa[ii]+jj+1,INFILES);
      strcpy(gOrigInputFile,aaa[ii]+jj+1);
      strncpy(      gInFileName,aaa[ii],     INFILES);
      PP"Input file %s\n",gInFileNameNoPath);
      filenameCount++;
    }
  }
  if(filenameCount>1) P"You specified too many input files.\n");
  if(filenameCount<1) P"You did not specify an input file.\n");
  if(die||filenameCount!=1) Usage();
  CheckSelfConsistencyOfOptions();
  /* DumpOptionsAndExit(); */
}
void Init2(void) {
  int ii;
  for(ii=COL-1;ii>=0;ii--) gOlc[ii][0]=0;
}
#define INCFILES 50 /* max length of included idl file's name */
void NoFindIncFile(char *incFile,const char *curFile) {
  Eose(); EE"Fatal error in STIC.  Could not find\n");
  EE"%s, ",incFile);
  EE"which was included in idl file %s.\n",curFile);
  EE"I searched the following directories:\n");
  TypeIncDirs(stderr);
  EE"To add to this list of directories, use my -I option.\n");
  Eose();
  exit(2);
}
void PreParseScanOfFile(void) {
  char line[302];
  while(fgets(line,300,yyin)) {
    if(strstr(line,"PAM.idl"))   gHaveIncludedPamIdl=7;
    if(strstr(line,"amiModule")) gHaveSeen_amiModule=7;
    if(strstr(line,"STAFCV_T"))  gHaveSeen_STAFCV_T=7;
  }
}
void RecursiveProcessingOfIncludeFiles(const char *curFile) {
  char save,line[225],*incFile,incFileFullPath[225]; int ii,quote;
  char cheapFix[20];
  FILE *incFileFp,*curFileFp;
  curFileFp=fopen(curFile,"r");
  if(!curFileFp) { EE"No can read %s.\n",curFile); exit(2); }
  while(fgets(line,222,curFileFp)) {
    save=line[10]; line[10]=0; strncpy(cheapFix,line,15); cheapFix[9]=0;
    if(!strcmp(cheapFix,"#include ")) {
      line[10]=save; for(ii=0;line[ii];ii++) if(line[ii]=='\"') break;
      if(line[ii]!='\"') { PP"Did not find quotes %s\n",line); exit(2); }
      quote=ii; strtok(line+quote+1,"\""); incFile=line+quote+1;
      if(strstr(incFile,".idl")) {
        if(!gOptionM) PP"Processing %23s included in %23s\n",incFile,curFile);
        for(ii=0;ii<gNincDir;ii++) {
          sprintf(incFileFullPath,"%s/%s",gIncDir[ii],incFile);
          incFileFp=fopen(incFileFullPath,"r");
          if(incFileFp) {
            fclose(incFileFp); HandleOneInputFile(incFileFullPath); break;
          }
        } if(ii>=gNincDir) NoFindIncFile(incFile,curFile);
      }
    }
  } fclose(curFileFp);
}
void HandleOneInputFile(char *inFile) { /* maybe inFile=gInFileName */
  char buffer[INFILES+2]; int ii;
  strcpy(buffer,inFile); strcpy(gInFileName,buffer);
  for(ii=strlen(gInFileName)-1;ii>=0;ii--) if(gInFileName[ii]=='/') break;
  strcpy(gInFileNameNoPath,gInFileName+ii+1);
  gFpInc=NULL; gFpH=NULL;

  /* This function not called for PAM.idl unless it is in include path. */
  if(strstr(inFile,"PAM.idl")) { gHaveIncludedPamIdl=7; return; }

  SetYyinFilePtr(gInFileName); PreParseScanOfFile(); fclose(yyin);
  SetYyinFilePtr(gInFileName); Init2(); yyparse();   fclose(yyin);
  if(gNInFile>=INFILE) Err(__LINE__);
  if(strlen(inFile)>INFILES) Err(__LINE__);
  strcpy(gInFile[gNInFile++],inFile);
  if(gOptionM) {
    if(gFpInc) Err(__LINE__);
    if(gFpH) Err(__LINE__);
  } else { 
    fclose(gFpInc); fclose(gFpH); 
  }
  RecursiveProcessingOfIncludeFiles(buffer);
  if(!gOptionM) PP"----- finished with %s\n",buffer);
} /* save inFile buffer gInFileName */
void FixVersionInfo(void) {
  int ii;
  if(strlen(gCvsVersionRaw)>CVSVERSION) ERR;
  strcpy(gCvsVersion,gCvsVersionRaw);
  for(ii=0;gCvsVersion[ii];ii++) if(gCvsVersion[ii]=='$') gCvsVersion[ii]=' ';
}
int main(int nnn,char *aaa[]) {
  int i;
  gNmoduleTable=0; gNinputTable=0; FixVersionInfo();
  gHaveSeen_STAFCV_T=0; gHaveSeen_amiModule=0; gHaveIncludedPamIdl=0;
  strncpy(gExeName,aaa[0],EXE); gNOutFile=0;
  sprintf(gOptioniTempFile,"/tmp/stic.option.i.%d",getpid());
  if(nnn<2) Usage();
  ReadOptions(nnn,aaa);
  if(!gOptionM) P"For help, type \"%s help\".\n",gExeName);
  if(!strcmp(gInFileName,"help")) Help();
  HandleOneInputFile(gInFileName);
  CheckThatAllTablesHaveBeenIncluded();
  if(gOptionM) {
    for(i=0;i<gNOutFile;i++) {
      if(strstr(gOutFile[i],"template")) continue;
      PP"%s",gOutFile[i]); if(i<gNOutFile-1) PP" ");
    }
    PP":\t");
    for(i=0;i<gNInFile;i++) { PP"%s",gInFile[i]); if(i<gNInFile-1) PP" "); }
    PP"\n");
  }
  exit(0);
}
yyerror(char *s) {
}
Error(void) {
  fprintf(stderr,"oooooooooooooooooooooooooooooooooooooooooo\n");
  fprintf(stderr,ERROR_FORMAT,gLN,gL1,gL2);
  for(gIi=strlen(gL2)-1;gIi>=0;gIi--) if(gL2[gIi]==' ') break; gJj=gIi+1;
  for(gIi=0;gIi<strlen(gL2);gIi++) {
    if(gIi<gJj) {
      if(gL2[gIi]!='\t') fprintf(stderr," ");  else fprintf(stderr,"\t");
    }
    else fprintf(stderr,"-");
  }
  fprintf(stderr,"\n");
  fprintf(stderr,"oooooooooooooooooooooooooooooooooooooooooo\n"); exit(2);
}
#define LS strcat(gL2,yytext);
#include "idl-lex.c"
/*
ttd char* types in xx_TBL.idl files, and perhaps also in xx_PAM.idl files.
*/
/* Mnemonicity table.
gLN	line count for error messages
idlFile		sum total
INCLU	#include
INTER	interface keyword "interface"
CORBA	"long", "float", etc., for fnct ret prototypes only
protos		body of idl interface definition, composed of proto's
proto		Eg, "long initialized(in int data_spec,out string cluster);".
args		Eg, "in int data_spec,out string cluster".
arg		Eg, "in int data_spec".
INOUT		"in" or "out".
IDENT	variable or prototype name (a, a2, Alpha, etc.)
NUMBE		12, 15 etc
pam		physics anal. mod.
error		yacc keyword, see yacc doc.
*/
static const yytabelem yyexca[] ={
-1, 0,
	0, 3,
	257, 3,
	260, 3,
	266, 3,
	-2, 0,
-1, 1,
	0, -1,
	-2, 0,
-1, 2,
	0, 1,
	-2, 24,
	};
# define YYNPROD 41
# define YYLAST 228
static const yytabelem yyact[]={

    42,    29,    40,     9,    52,    60,    17,    41,    24,    59,
    62,    22,    11,    15,    13,     8,    38,     3,    19,    28,
    18,    50,    48,    56,    46,    36,    33,    57,    43,    23,
    61,    58,    54,    53,    47,    37,    49,    31,    30,    16,
    10,    14,     7,    45,    44,    39,    34,    26,    25,    21,
    12,     6,     5,     4,     2,     1,     0,     0,    35,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    20,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    27,     0,    32,    32,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    55 };
static const yytabelem yypact[]={

  -239,-10000000,  -245,-10000000,-10000000,-10000000,-10000000,  -254,  -248,  -249,
-10000000,  -259,  -103,-10000000,   -40,-10000000,-10000000,-10000000,-10000000,  -251,
-10000000,  -117,  -104,  -124,   -33,-10000000,-10000000,-10000000,-10000000,   -34,
-10000000,  -243,-10000000,-10000000,  -260,  -125,-10000000,   -12,-10000000,-10000000,
-10000000,-10000000,   -35,-10000000,   -23,   -23,-10000000,   -37,-10000000,-10000000,
-10000000,-10000000,   -36,   -17,  -253,-10000000,-10000000,-10000000,  -252,-10000000,
-10000000,-10000000,-10000000 };
static const yytabelem yypgo[]={

     0,    55,    54,    53,    52,    51,    50,    49,    48,    47,
    46,    45,    44,    22,    43,    42,    41,    29,    40,    39,
    38,    37,    35,    34,    33,    32,    31,    30 };
static const yytabelem yyr1[]={

     0,     1,     1,     2,     2,     3,     3,     5,     6,     7,
     7,     8,     9,    10,    10,    12,    11,    14,    11,    13,
    13,     4,     4,    16,    15,    15,    18,    19,    17,    17,
    20,    21,    22,    23,    23,    23,    24,    25,    27,    26,
    26 };
static const yytabelem yyr2[]={

     0,     3,     3,     0,     4,     3,     3,    12,     3,     0,
     4,     4,     3,     0,     4,     1,     6,     1,     6,     2,
     2,    19,    15,     3,     0,     4,     4,     3,     0,     4,
    12,     3,     3,     0,     4,     6,     6,     3,     3,     3,
     3 };
static const yytabelem yychk[]={

-10000000,    -1,    -2,   256,    -3,    -4,    -5,   -15,   260,   257,
   -18,   266,    -6,   262,   -16,   262,   -19,   265,   123,    58,
   123,    -7,   262,   -17,   125,    -8,    -9,   258,   123,   125,
   -20,   -21,   268,    59,   -10,   -17,    59,   -22,   259,   -11,
   262,   267,   125,    40,   -12,   -14,    59,   -23,   -13,    59,
    44,   -13,    41,   -24,   -25,   264,    59,    44,   -26,   262,
   258,   -27,   262 };
static const yytabelem yydef[]={

    -2,    -2,    -2,     2,     4,     5,     6,     0,     0,     0,
    25,     0,     0,     8,     0,    23,    26,    27,     9,     0,
    28,     0,     0,     0,     0,    10,    13,    12,    28,     0,
    29,     0,    31,     7,    11,     0,    22,     0,    32,    14,
    15,    17,     0,    33,     0,     0,    21,     0,    16,    19,
    20,    18,     0,    34,     0,    37,    30,    35,     0,    39,
    40,    36,    38 };
typedef struct
#ifdef __cplusplus
	yytoktype
#endif
{ char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"INTER",	257,
	"CORBA",	258,
	"ICALL",	259,
	"STRUC",	260,
	"PROTO",	261,
	"IDENT",	262,
	"NUMBE",	263,
	"INOUT",	264,
	"STRIN",	265,
	"INCLU",	266,
	"ARRAY",	267,
	"STAFC",	268,
	"-unknown-",	-1	/* ends search */
};

char * yyreds[] =
{
	"-no such reduction-",
	"finish : theFile",
	"finish : error",
	"theFile : /* empty */",
	"theFile : theFile onePart",
	"onePart : pam",
	"onePart : tbl",
	"tbl : STRUC tblName '{' tAndNs '}' ';'",
	"tblName : IDENT",
	"tAndNs : /* empty */",
	"tAndNs : tAndNs tAndN",
	"tAndN : colType cols",
	"colType : CORBA",
	"cols : /* empty */",
	"cols : cols col",
	"col : IDENT",
	"col : IDENT cs",
	"col : ARRAY",
	"col : ARRAY cs",
	"cs : ';'",
	"cs : ','",
	"pam : incs INTER pamName ':' IDENT '{' protos '}' ';'",
	"pam : incs INTER pamName '{' protos '}' ';'",
	"pamName : IDENT",
	"incs : /* empty */",
	"incs : incs inc",
	"inc : INCLU incFile",
	"incFile : STRIN",
	"protos : /* empty */",
	"protos : protos proto",
	"proto : fncType fncName '(' args ')' ';'",
	"fncType : STAFC",
	"fncName : ICALL",
	"args : /* empty */",
	"args : args arg",
	"args : args arg ','",
	"arg : inOut argType argName",
	"inOut : INOUT",
	"argName : IDENT",
	"argType : IDENT",
	"argType : CORBA",
};
#endif /* YYDEBUG */
# line	1 "/usr/ccs/bin/yaccpar"
/*
 * Copyright (c) 1993 by Sun Microsystems, Inc.
 */

#pragma ident	"@(#)yaccpar	6.14	97/01/16 SMI"

/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab
#define YYACCEPT	return(0)
#define YYABORT		return(1)
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#define YYNEW(type)	malloc(sizeof(type) * yynewmax)
#define YYCOPY(to, from, type) \
	(type *) memcpy(to, (char *) from, yymaxdepth * sizeof (type))
#define YYENLARGE( from, type) \
	(type *) realloc((char *) from, yynewmax * sizeof(type))
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG		(-10000000)

/*
** global variables used by the parser
*/
YYSTYPE *yypv;			/* top of value stack */
int *yyps;			/* top of state stack */

int yystate;			/* current state */
int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */
int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */



#ifdef YYNMBCHARS
#define YYLEX()		yycvtok(yylex())
/*
** yycvtok - return a token if i is a wchar_t value that exceeds 255.
**	If i<255, i itself is the token.  If i>255 but the neither 
**	of the 30th or 31st bit is on, i is already a token.
*/
#if defined(__STDC__) || defined(__cplusplus)
int yycvtok(int i)
#else
int yycvtok(i) int i;
#endif
{
	int first = 0;
	int last = YYNMBCHARS - 1;
	int mid;
	wchar_t j;

	if(i&0x60000000){/*Must convert to a token. */
		if( yymbchars[last].character < i ){
			return i;/*Giving up*/
		}
		while ((last>=first)&&(first>=0)) {/*Binary search loop*/
			mid = (first+last)/2;
			j = yymbchars[mid].character;
			if( j==i ){/*Found*/ 
				return yymbchars[mid].tvalue;
			}else if( j<i ){
				first = mid + 1;
			}else{
				last = mid -1;
			}
		}
		/*No entry in the table.*/
		return i;/* Giving up.*/
	}else{/* i is already a token. */
		return i;
	}
}
#else/*!YYNMBCHARS*/
#define YYLEX()		yylex()
#endif/*!YYNMBCHARS*/

/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
#if defined(__STDC__) || defined(__cplusplus)
int yyparse(void)
#else
int yyparse()
#endif
{
	register YYSTYPE *yypvt = 0;	/* top of value stack for $vars */

#if defined(__cplusplus) || defined(lint)
/*
	hacks to please C++ and lint - goto's inside
	switch should never be executed
*/
	static int __yaccpar_lint_hack__ = 0;
	switch (__yaccpar_lint_hack__)
	{
		case 1: goto yyerrlab;
		case 2: goto yynewstate;
	}
#endif

	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

#if YYMAXDEPTH <= 0
	if (yymaxdepth <= 0)
	{
		if ((yymaxdepth = YYEXPAND(0)) <= 0)
		{
			yyerror("yacc initialization error");
			YYABORT;
		}
	}
#endif

	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */
	goto yystack;	/* moved from 6 lines above to here to please C++ */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
			/*
			** reallocate and recover.  Note that pointers
			** have to be reset, or bad things will happen
			*/
			int yyps_index = (yy_ps - yys);
			int yypv_index = (yy_pv - yyv);
			int yypvt_index = (yypvt - yyv);
			int yynewmax;
#ifdef YYEXPAND
			yynewmax = YYEXPAND(yymaxdepth);
#else
			yynewmax = 2 * yymaxdepth;	/* double table size */
			if (yymaxdepth == YYMAXDEPTH)	/* first time growth */
			{
				char *newyys = (char *)YYNEW(int);
				char *newyyv = (char *)YYNEW(YYSTYPE);
				if (newyys != 0 && newyyv != 0)
				{
					yys = YYCOPY(newyys, yys, int);
					yyv = YYCOPY(newyyv, yyv, YYSTYPE);
				}
				else
					yynewmax = 0;	/* failed */
			}
			else				/* not first time */
			{
				yys = YYENLARGE(yys, int);
				yyv = YYENLARGE(yyv, YYSTYPE);
				if (yys == 0 || yyv == 0)
					yynewmax = 0;	/* failed */
			}
#endif
			if (yynewmax <= yymaxdepth)	/* tables not expanded */
			{
				yyerror( "yacc stack overflow" );
				YYABORT;
			}
			yymaxdepth = yynewmax;

			yy_ps = yys + yyps_index;
			yy_pv = yyv + yypv_index;
			yypvt = yyv + yypvt_index;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = YYLEX() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			printf( "Received token " );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = YYLEX() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				printf( "Received token " );
				if ( yychar == 0 )
					printf( "end-of-file\n" );
				else if ( yychar < 0 )
					printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register const int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
			skip_init:
				yynerrs++;
				/* FALLTHRU */
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					printf( "Error recovery discards " );
					if ( yychar == 0 )
						printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 1:
# line 117 "../src/idl.y"
{ } break;
case 2:
# line 117 "../src/idl.y"
{ Error(); } break;
case 5:
# line 119 "../src/idl.y"
{ Pam(); Init(); } break;
case 6:
# line 119 "../src/idl.y"
{ Tbl(); Init(); } break;
case 8:
# line 121 "../src/idl.y"
{ TblName(yylval.str); } break;
case 12:
# line 124 "../src/idl.y"
{ gFtc=gNColNames; ColType(yylval.str); } break;
case 15:
# line 126 "../src/idl.y"
{ Col(yylval.str); } break;
case 17:
# line 126 "../src/idl.y"
{ Col(yylval.str); } break;
case 21:
# line 128 "../src/idl.y"
{ gMkCc=7; } break;
case 22:
# line 129 "../src/idl.y"
{ gMkCc=0; } break;
case 23:
# line 130 "../src/idl.y"
{ PamName(yylval.str); } break;
case 27:
# line 133 "../src/idl.y"
{ IncludeFileName(yylval.str); } break;
case 31:
# line 136 "../src/idl.y"
{ FncType(yylval.str); } break;
case 32:
# line 137 "../src/idl.y"
{ PrototypeName(yylval.str); } break;
case 37:
# line 140 "../src/idl.y"
{ InOut(yylval.str); } break;
case 38:
# line 141 "../src/idl.y"
{ ArgName(yylval.str); } break;
case 39:
# line 142 "../src/idl.y"
{ ArgType(yylval.str); } break;
case 40:
# line 142 "../src/idl.y"
{ ArgType(yylval.str); } break;
# line	531 "/usr/ccs/bin/yaccpar"
	}
	goto yystack;		/* reset registers in driver code */
}

