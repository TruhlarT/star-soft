/*  
 *   Example program calling minuit.
 *   
 *   Gunter Folger, Dec 94
 *
 */
#if defined(__hpux) || defined(_IBMR2) || defined(__alpha) || defined(__apollo) || defined(__ultrix) || defined(__sgi) || defined(__sun) 
#define extname
#endif 

#ifdef extname
#define FCN fcn_
#else
#define FCN fcn
#endif

#include "cfortran.h"
#include "minuit.h"
#define Ncont 20
void main()
{
	int error_flag=0;
	void *fcn_();
	struct {
		double x[Ncont];
		double y[Ncont];
		int n;
		} pts;
	double f_null=0.;
	

	MNINIT(5,6,7);   /*  initialise  */

	MNSETI(" Minuit Example ");   /* set title */

	MNPARM(1,"X",0.,.1,f_null,f_null,error_flag);

	MNPARM(2,"-Y-",0.,.01,f_null,f_null,error_flag);

	MNEXCM(fcn_,"MIGRAD",0,0,error_flag,0);

	MNEXCM(fcn_,"MINOS",0,0,error_flag,0);

	MNCONT(fcn_,1,2,Ncont,pts.x[0],pts.y[0],pts.n, 0);

}

