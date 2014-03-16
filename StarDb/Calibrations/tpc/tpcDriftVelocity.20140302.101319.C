TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 61016
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51196; // +/- 3.07575e-05 cm/us East: Slope = 0.376583 +/- 0.00572525 DV = 5.51196 +/- 3.07575e-05
  row.laserDriftVelocityWest	 =   5.51552; // +/- 3.28275e-05 cm/us West: Slope = -0.355984 +/- 0.00637489 DV = 5.51552 +/- 3.28275e-05
//row.scaleY                  	 = 1.56358e-06;// +/-1.78991e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51362 +/- 2.2445e-05
};
