TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33073
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50748; // +/- 3.53937e-05 cm/us East: Slope = 0.21326 +/- 0.00668883 DV = 5.50748 +/- 3.53937e-05
  row.laserDriftVelocityWest	 =   5.5052; // +/- 3.02106e-05 cm/us West: Slope = 0.657459 +/- 0.00541158 DV = 5.5052 +/- 3.02106e-05
//row.scaleY                  	 = 8.20244e-08;// +/-1.28539e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50616 +/- 2.29783e-05
};
