//*********************************************************************** 
//File : sal_make_align.cc
//Description : find tracks parameters and defined the vertex coordinates
//Input: svg_config, sal_spt, sal_vrtx
//Output: sal_vrtx_find
//***********************************************************************

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "svt.h"
# include "sal_make_align.h"

long type_of_call sal_make_align_(TABLE_HEAD_ST *config_h, SVG_CONFIG_ST *config,
                     TABLE_HEAD_ST *sal_spt_h, SAL_SPT_ST  *sal_spt,
                     TABLE_HEAD_ST  *sal_vrtx_h, SAL_VRTX_ST *sal_vrtx,
                     TABLE_HEAD_ST  *sal_vrtx_find_h, SAL_VRTX_ST *sal_vrtx_find,
                     TABLE_HEAD_ST  *sal_geom_h,  SAL_GEOM_ST *sal_geom )
{




Point P;
int iev;
long waf_id;
float r1, r2, r3, r4, r5, r6;
int p, i, j, k, l, n, pf[NEV+1];

r1 = config[0].layer_radius[0]*10;
r2 = config[0].layer_radius[1]*10;
r3 = config[0].layer_radius[2]*10;
r4 = config[0].layer_radius[3]*10;
r5 = config[0].layer_radius[4]*10;
r6 = config[0].layer_radius[5]*10;

work work(r1, r2, r3, r4, r5, r6); 
event Event(r1, r2, r3, r4, r5, r6);
work.ClearParam();
work.InstallParam();

//***********************************************************************
//           Creating of event hits map
//***********************************************************************
p = 1; pf[0] = 0; 
for(iev = 1; iev <= NEV; iev++)
 {
  while(sal_spt[p].id > 0)  p++;
  pf[iev] = p+1;
  p++;
 }

//**********************************************************************
//          Filling structure by hits and vertex coordinates
//**********************************************************************
for(iev = 0; iev < NEV; iev++)
{
 p = pf[iev];
 while(p < pf[iev+1])
  {
  waf_id  = sal_spt[p].wafer_id ;
  n = (int)(waf_id/1000);
  i = (int)((waf_id/1000-1)/2);
  k = (int)(waf_id/100)- 10*((int)(waf_id/1000));
  l = ((int)(n/2) + 1 - (int)((n+1)/2));
  j = 2*(waf_id - 100*((int)waf_id/100) - 1) + l;  
  k = work.Events[iev].Bars[i].ladders[j].num_waf - k;
  work.Events[iev].Bars[i].PutPoint(j, k, sal_spt[p].xl*10,
                                         sal_spt[p].yl*10);
  p++;
  }
 

  work.ry[iev] = sal_vrtx[iev].x[0]*10;
  work.rz[iev] = sal_vrtx[iev].x[1]*10;
  work.rx[iev] = sal_vrtx[iev].x[2]*10;

}
//***********************************************************************
//   Calling of alignment procedure
//***********************************************************************
 for(iev = 0; iev < NEV; iev++) 
  {
   work.Events[iev].Clear();
   work.Events[iev].FindAllTracks();
   printf("\n Total tracks found : %d\n  ", work.Events[iev].num);

   work.Events[iev].OptimizeTracks(); 
   work.Events[iev].SelectTracks();
   int nt = 0;
   for(int q = 0; q < work.Events[iev].num; q++) 
   if (work.Events[iev].tracks[q].flag == 1) nt++;
   printf("Selected tracks  :  %d\n", nt);
  }
  
work.MakeAlign();

//***********************************************************************
//  Writing output
//***********************************************************************
for(iev = 0; iev < NEV; iev++)
{
 printf("\n Find : %.4f %.4f %.4f",work.Events[iev].Vertex.Y,
              work.Events[iev].Vertex.Z,work.Events[iev].Vertex.X);  
 printf("\n Real : %.4f %.4f %.4f\n",work.ry[iev],
                    work.rz[iev],work.rx[iev] );
 sal_vrtx_find[iev].x[0] = work.Events[iev].Vertex.Y*0.1;
 sal_vrtx_find[iev].x[1] = work.Events[iev].Vertex.Z*0.1;
 sal_vrtx_find[iev].x[2] = work.Events[iev].Vertex.X*0.1;
}
p = 0;
for(i = 0; i < 3; i++)
 for(l = 0; l < 2; l++)  
  for(j = 0; j < Event.Bars[i].num_lad/2; j++)
   for(k = Event.Bars[i].ladders[j*2+l].num_waf - 1; k >= 0; k--)
    {
      Event.Bars[i].PutPoint(j*2+l, k, 0.0, 0.0); 
                        
      Event.Bars[i].SetParam(j*2+l, k, work.par[i][j*2+l][k]);
      P = Event.Bars[i].GetPoint(j*2+l, k, 0);
      
      sal_geom[p].x[0] = P.Y*0.1;
      sal_geom[p].x[1] = P.Z*0.1;
      sal_geom[p].x[2] = P.X*0.1;
      sal_geom[p].par[0] = work.par[i][j*2+l][k][0];  
      sal_geom[p].par[0] = work.par[i][j*2+l][k][1];
      sal_geom[p].par[0] = work.par[i][j*2+l][k][2];
      sal_geom[p].par[0] = work.par[i][j*2+l][k][3];
      sal_geom[p].par[0] = work.par[i][j*2+l][k][4];
      sal_geom[p].par[0] = work.par[i][j*2+l][k][5];
      printf("%.3f %.3f %.3f\n",P.Y*0.1,P.Z*0.1,P.X*0.1);
      sal_geom[p].id = p;
      p++; 
    }
sal_geom_h->nok = p;
sal_vrtx_find_h->nok = iev;
return STAFCV_OK;
}

