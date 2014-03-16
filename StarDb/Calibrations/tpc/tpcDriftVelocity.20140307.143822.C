TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 66024
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51905; // +/- 4.00906e-05 cm/us East: Slope = -0.935964 +/- 0.0074146 DV = 5.51905 +/- 4.00906e-05
  row.laserDriftVelocityWest	 =   5.52023; // +/- 4.44181e-05 cm/us West: Slope = -1.28459 +/- 0.00894952 DV = 5.52023 +/- 4.44181e-05
//row.scaleY                  	 = -4.32835e-07;// +/-1.34786e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51958 +/- 2.9761e-05
};
