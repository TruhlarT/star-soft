/*:>--------------------------------------------------------------------
**: FILE:       tfc_load_native_gains.c.template
**: HISTORY:
**:             00jan93-v000a-hpl- Created by stic Version
**:  Id: idl.y,v 1.14 1998/08/28 21:22:28 fisyak Exp  
**:<------------------------------------------------------------------*/
#include "tfc_load_native_gains.h"
#define nRows 45		/* number of rows */
/* Some global variables for indexing the ped/gain tables */
int           RowOffset[nRows]={1662, 1566, 1462, 1350, 1232, 
                                1106, 972,  830,  680,  522,
			        356,  182,  0,    3844, 3744,
                                3642, 3538, 3432, 3326, 3218,
                                3108, 2996, 2884, 2770, 2654, 
                                2536, 2416, 2294, 2172, 2048,
                                1922, 1794, 1666, 1536, 1404,
                                1270, 1134, 996,  858,  718,
				576,  432,  288,  144,  0};

int           pads_in_row[nRows]={ 88,  96, 104, 112, 118,
				   126, 134, 142, 150, 158,
			           166, 174, 182,  98, 100,
			           102, 104, 106, 106, 108,
			           110, 112, 112, 114, 116,
			           118, 120, 122, 122, 124,
			           126, 128, 128, 130, 132,
			           134, 136, 138, 138, 140,
			           142, 144, 144, 144, 144};
                                
long type_of_call tfc_load_native_gains_(
  TABLE_HEAD_ST *current_sector_h, TCL_SECTOR_INDEX_ST   *current_sector ,
  TABLE_HEAD_ST       *indextbl_h,       TYPE_INDEX_ST         *indextbl ,
  TABLE_HEAD_ST       *gain_bad_h,    TYPE_GAIN_BAD_ST         *gain_bad ,
  TABLE_HEAD_ST      *structtbl_h,   TYPE_STRUCTTBL_ST        *structtbl ,
  TABLE_HEAD_ST     *gain_sec_m_h,        RAW_SEC_M_ST       *gain_sec_m ,
  TABLE_HEAD_ST    *gain_row_in_h,          RAW_ROW_ST      *gain_row_in ,
  TABLE_HEAD_ST       *gains_in_h,   TYPE_FLOATDATA_ST         *gains_in ,
  TABLE_HEAD_ST   *gain_row_out_h,          RAW_ROW_ST     *gain_row_out ,
  TABLE_HEAD_ST      *gains_out_h,   TYPE_FLOATDATA_ST        *gains_out )
{
/*:>--------------------------------------------------------------------
**: ROUTINE:    tfc_load_native_gains_
**: DESCRIPTION: Physics Analysis Module ANSI C template.
**:             This is an ANSI C Physics Analysis Module template
**:             automatically generated by stic from tfc_load_native_gains.idl.
**:             Please edit comments and code.
**: AUTHOR:     hpl - H.P. Lovecraft, hplovecraft@cthulhu.void
**: ARGUMENTS:
**:       IN:
**:       current_sector  -
**:      current_sector_h -
**:           indextbl    - PLEASE FILL IN DESCRIPTION HERE
**:          indextbl_h   - header Structure for indextbl
**:           gain_bad    - PLEASE FILL IN DESCRIPTION HERE
**:          gain_bad_h   - header Structure for gain_bad
**:          structtbl    - PLEASE FILL IN DESCRIPTION HERE
**:         structtbl_h   - header Structure for structtbl
**:    INOUT:
**:      OUT:
**:         gain_sec_m    - PLEASE FILL IN DESCRIPTION HERE
**:        gain_sec_m_h   - header Structure for raw_sec_m
**:        gain_row_in    - PLEASE FILL IN DESCRIPTION HERE
**:       gain_row_in_h   - header Structure for raw_row_in
**:           gains_in    - PLEASE FILL IN DESCRIPTION HERE
**:          gains_in_h   - header Structure for gains_in
**:       gain_row_out    - PLEASE FILL IN DESCRIPTION HERE
**:      gain_row_out_h   - header Structure for raw_row_out
**:          gains_out    - PLEASE FILL IN DESCRIPTION HERE
**:         gains_out_h   - header Structure for gains_out
**: RETURNS:    STAF Condition Value
**:>------------------------------------------------------------------*/
  int i; /* loop index */
  int k; /* loop index */
  int StructRow; /* pointer to the structtable table */
  int DataRow;   /* pointer to the gain_bad table */
  int Row;       /* row number for the data */
  int Npads;     /* number of pads that will follow in the structtable */
  int Pad;       /* pad ID */

  /* if this is first call initialise gain_sec_m table */
  if( gain_sec_m_h[0].nok == 0){
  for (i=0;i<24;i++)
    {
      gain_sec_m[i].tfirst=0;
      gain_sec_m[i].tlast=0;
      gain_sec_m[i].TimeRef='N';
      gain_sec_m[i].RowRefIn='N';
      gain_sec_m[i].RowRefOut='N';
      gain_sec_m[i].SectorId=i+1;}
  gain_sec_m_h[0].nok=24;}
  /* if this is first call for that sector, initialise gain_row_in and gain_row_our structures */
  if (gain_row_in_h[0].nok == 0){
    for(i=0;i<13;i++){
      gain_row_in[i].ipixel=RowOffset[i];
      gain_row_in[i].iseq=0;
      gain_row_in[i].npixel=pads_in_row[i];
      gain_row_in[i].nseq=0;
      gain_row_in[i].ipad=0;
      gain_row_in[i].PadFirst=0;
      gain_row_in[i].npad=0;
      gain_row_in[i].PadModBreak=0;
      gain_row_in[i].PadRef='N';
      gain_row_in[i].RowId=i+1;
      /* Now initialize all the gains to 1 for this row */
      for(k=RowOffset[i]; k<pads_in_row[i];k++)gains_in[k].data=1.0;
  }
   gain_sec_m[current_sector[0].CurrentSector-1].RowRefIn='R';
   gain_row_in_h[0].nok=13;
   /*Set rowcount for gains */
   gains_in_h[0].nok=1750;
  }
  if (gain_row_out_h[0].nok == 0){
    for(i=0;i<32;i++){
      gain_row_out[i].ipixel=RowOffset[i+13];
      gain_row_out[i].iseq=0;
      gain_row_out[i].npixel=pads_in_row[i+13];
      gain_row_out[i].nseq=0;
      gain_row_out[i].ipad=0;
      gain_row_out[i].PadFirst=0;
      gain_row_out[i].npad=0;
      gain_row_out[i].PadModBreak=0;
      gain_row_out[i].PadRef='N';
      gain_row_out[i].RowId=i+1;
      /* Now initialize all the gains to 1 for this row */
      for(k=RowOffset[i+13]; k<pads_in_row[i+13];k++)gains_out[k].data=1.0;
  }
   gain_sec_m[current_sector[0].CurrentSector-1].RowRefOut='R';
   gain_row_out_h[0].nok=32;
   /*Set rowcount for gains */
   gains_out_h[0].nok=3942;
  }

  
for (i=0;i< indextbl_h[0].nok;i++)
     if (indextbl[i].data_type == 17 && indextbl[i].sector==current_sector[0].CurrentSector){
         StructRow=indextbl[i].struct_row;
         DataRow=  indextbl[i].data_row;
         Row=      indextbl[i].rgm;
         Npads=structtbl[StructRow].info;
	 k=1;
         while(k++<=Npads){
	 Pad=structtbl[StructRow+k].info;
         if(Row<13){gains_in[RowOffset[Row-1]+Pad-1].data=
		      (gain_bad[DataRow+k-1].gain<=0.0)?1.0:gain_bad[DataRow+k-1].gain;}
	 else{gains_out[RowOffset[Row-1]+Pad-1].data=
		      (gain_bad[DataRow+k-1].gain<=0.0)?1.0:gain_bad[DataRow+k-1].gain;}
         }
	   }

   return STAFCV_OK;
}
