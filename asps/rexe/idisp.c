/*-- Author :    Pavel Nevski   01/09/99*/
int idisp0_ (a,b)   char  *a,*b;     { return  b-a;    }
int idisp1_ (a,b)   char  *a,*b;     { return (b-a)+1; }
int idisp2_ (a,b)   short *a,*b;     { return (b-a)+1; }
int idisp4_ (a,b)   int   *a,*b;     { return (b-a)+1; }
int iponter_(a,b)   int   *a,**b;    { return (*b-a);  }
