TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48004
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.4995; // +/- 2.80377e-05 cm/us East: Slope = 1.24957 +/- 0.00518398 DV = 5.4995 +/- 2.80377e-05
  row.laserDriftVelocityWest	 =   5.4995; // +/- 2.4033e-05 cm/us West: Slope = 1.23093 +/- 0.00452049 DV = 5.4995 +/- 2.4033e-05
//row.scaleY                  	 = 3.08748e-06;// +/-1.82277e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.4995 +/- 1.8247e-05
};
