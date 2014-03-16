TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 58044
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51178; // +/- 3.6523e-05 cm/us East: Slope = 0.415293 +/- 0.00683782 DV = 5.51178 +/- 3.6523e-05
  row.laserDriftVelocityWest	 =   5.51477; // +/- 3.42254e-05 cm/us West: Slope = -0.210272 +/- 0.00655927 DV = 5.51477 +/- 3.42254e-05
//row.scaleY                  	 = 1.66181e-06;// +/-1.71471e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51337 +/- 2.49738e-05
};
