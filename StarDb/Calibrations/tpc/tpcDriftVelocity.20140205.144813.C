TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50771; // +/- 3.98145e-05 cm/us East: Slope = 0.230468 +/- 0.00728588 DV = 5.50771 +/- 3.98145e-05
  row.laserDriftVelocityWest	 =   5.51032; // +/- 3.24932e-05 cm/us West: Slope = -0.28761 +/- 0.00603043 DV = 5.51032 +/- 3.24932e-05
//row.scaleY                  	 = -1.31598e-07;// +/-1.45086e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50927 +/- 2.51738e-05
};
