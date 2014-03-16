TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 58053
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51322; // +/- 2.67885e-05 cm/us East: Slope = 0.118904 +/- 0.0048433 DV = 5.51322 +/- 2.67885e-05
  row.laserDriftVelocityWest	 =   5.51585; // +/- 3.48395e-05 cm/us West: Slope = -0.40393 +/- 0.00696155 DV = 5.51585 +/- 3.48395e-05
//row.scaleY                  	 = 6.93034e-06;// +/-1.63665e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51419 +/- 2.12365e-05
};
