/*:>--------------------------------------------------------------------
**: FILE:       track_propagator.c.template
**: HISTORY:
**:             00jan93-v000a-hpl- Created by stic Version
**:  Id: idl.y,v 1.14 1998/08/28 21:22:28 fisyak Exp  
**:<------------------------------------------------------------------*/
#include "track_propagator.h"
#include <stdio.h>
#include <math.h>


long type_of_call track_propagator_(
  TABLE_HEAD_ST         *gtrack_h,      DST_TRACK_ST           *gtrack ,
  TABLE_HEAD_ST         *target_h,  EGR_PROPAGATE_ST           *target ,
  TABLE_HEAD_ST         *ptrack_h,      DST_TRACK_ST           *ptrack )
{
/*:>--------------------------------------------------------------------
**: ROUTINE:    track_propagator_
**: DESCRIPTION: 
**:             Propagates instances of dst_track to points, cylinders
**:             or plane.
**:             
**: AUTHOR:     S. Margetis and W. Deng
**: ARGUMENTS:
**:       IN:
**:            target     - Where to propagate the tracks
**:            target_h   - header Structure for target
**:            gtrack     - input tracks
**:            gtrack_h   - header Structure for gtrack
**:      OUT:
**:             ptrack    - output tracks
**:            ptrack_h   - header Structure for gtrack
**: RETURNS:    STAF Condition Value
**:>------------------------------------------------------------------*/
  
  
  long  i, iflag;
  float bfld, GRADDEG=57.2958;
  float psi, pt, tanl, x0, y0, z0, xp[2], xout[4], p[3], xv[3], xx0[3];
  float trk[7], r1, r2, xc1[2], xc2[2], x[2], y[2], cut, x1[3];
  float phi0, phi, dphi, temppsi, test=1. ;
  float pStraight[3];
  long  q, psiftr;
  float xlocal[3],bfield[3];
  

  /* get magnetic field   */
  
  
  xlocal[0] = 0.;
  xlocal[1] = 0.;
  xlocal[2] = 0.;
  
  gufld_(xlocal,bfield);
  
  bfld = bfield[2];
  
  for(i=0; i<gtrack_h->nok; i++) 
    {
      psi  = gtrack[i].psi;
      q    = (long) gtrack[i].icharge;
      tanl = gtrack[i].tanl;
      if(target->iflag == 5)
	{ 
	  pt = 1.;
	}
      else
	{
	  if(gtrack[i].invpt != 0 )
	    {
	      pt    = 1/gtrack[i].invpt ;
	    }
	  else
	    {
	      /* message('Error, invpt); */
	      pt = 0.01;
	    }
	}
      x0   = gtrack[i].x0 ;
      y0   = gtrack[i].y0 ;
      z0   = gtrack[i].z0;
      trk[0] = gtrack[i].x0;
      trk[1] = gtrack[i].y0;
      trk[2] = gtrack[i].z0;
      trk[3] = gtrack[i].psi;
      trk[4] = gtrack[i].tanl;
      trk[5] = (float) gtrack[i].icharge;
      trk[6] = pt;
      r1     = ((float) gtrack[i].icharge)*(1/gtrack[i].invpt)/(0.0003*bfld);
      /* we should take the absolute value of r1 */
      r1     = fabs(r1);
      
      if(target->iflag == 1 || target->iflag == 2)
	{
	  xp[0]= target->x[0]; 
	  xp[1]= target->x[1];
	  
	  prop_project_track_(&psi, &q, &pt, &tanl, &x0, &y0, &bfld, &z0, xp, xout); 
	  
	  ptrack[i].x0 = xout[0];
	  ptrack[i].y0 = xout[1];
	  ptrack[i].z0 = xout[2];
	  ptrack[i].psi= xout[3];

	  if (target->iflag == 2)
	    {
	      xv[0] = target->x[0];
	      xv[1] = target->x[1];
	      xv[2] = target->x[2];
	      x1[0] = xout[0];
	      x1[1] = xout[1];
	      x1[2] = xout[2];
	      trk[0] = xout[0];
	      trk[1] = xout[1];
	      trk[2] = xout[2];
	      trk[3] = xout[3];
	      prop_track_mom_(trk, p);  
	      prop_fine_approach_(xv, x1, p, &xx0); 
	      ptrack[i].x0 = xx0[0];
	      ptrack[i].y0 = xx0[1];
	      ptrack[i].z0 = xx0[2];
	    }
	}
      
      if(target->iflag == 3)
	{
	  prop_circle_param_(trk, xc1, &r1); 
	  xc2[0] = xc2[1] = 0.;
	  r2 = target->r;
	  cut = 0.4;
	  prop_vzero_geom_(&cut, xc1, xc2, &r1, &r2, x, y, &iflag); 
	  if(iflag == 5)
	    {
	      /* message("Can't project to the circle target->r! "); */
	      continue;
	    }
	  else if (iflag == 3)
	    {
      	      xp[0] = x[0];
	      xp[1] = y[0];
	    }
	  else
	    {
	      if(  ((x0-x[0])*(x0-x[0]) + (y0-y[0])*(y0-y[0])) <
		   ((x0-x[1])*(x0-x[1]) + (y0-y[1])*(y0-y[1]))   )
		{ 
		  xp[0] = x[0];
		  xp[1] = y[0];
		}
	      else
		{
		  xp[0] = x[1];
		  xp[1] = y[1];
		} 
	    }
	  
	  prop_project_track_(&psi, &q, &pt, &tanl, &x0, &y0, &bfld, &z0, xp, xout); 
	  
	  ptrack[i].x0 = xout[0];
	  ptrack[i].y0 = xout[1];
	  ptrack[i].z0 = xout[2];
	  ptrack[i].psi= xout[3];
	}
      
      if(target->iflag == 4)
	{
	  phi0 = atan2(y0,x0);
	  dphi = - trk[5]*(target->z-z0)/(trk[4]*r1); 
	  /*   trk[4] != 0.  */
	  phi  = phi0 + dphi;
	  ptrack[i].x0 = x0 + r1*(cos(phi)-cos(phi0));
	  ptrack[i].y0 = y0 + r1*(sin(phi)-sin(phi0));
	  ptrack[i].z0 = target->z;
	  temppsi = trk[3]+dphi*GRADDEG;
	  if(temppsi<0.)
	    {
	      psiftr = (long)(temppsi/360.-1.);
	    }
	  else
	    {
	      psiftr = (long)(temppsi/360.);
	    }
	  ptrack[i].psi= temppsi - 360.* (float)psiftr; 
	  /*  Do we have to consider if psi is within (0, 360) degree? */ 
	}

      if(target->iflag == 5)
	{
	  xv[0] = target->x[0];
	  xv[1] = target->x[1];
	  xv[2] = target->x[2];
	  pStraight[0] = pt * cos(psi);
	  pStraight[1] = pt * sin(psi);
	  pStraight[2] = pt * tanl;
	  prop_fine_approach_(xv, x0, pStraight, &xx0);
	  ptrack[i].x0 = xx0[0];
	  ptrack[i].y0 = xx0[1];
	  ptrack[i].z0 = xx0[2]; 
	}
    }
  return STAFCV_OK;
}  

