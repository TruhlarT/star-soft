TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 61024
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51083; // +/- 2.95247e-05 cm/us East: Slope = 0.496406 +/- 0.00525635 DV = 5.51083 +/- 2.95247e-05
  row.laserDriftVelocityWest	 =   5.51589; // +/- 3.15144e-05 cm/us West: Slope = -0.417012 +/- 0.00646855 DV = 5.51589 +/- 3.15144e-05
//row.scaleY                  	 = 3.16694e-07;// +/-1.74637e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51319 +/- 2.15462e-05
};
