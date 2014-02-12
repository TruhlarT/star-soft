TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38065
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50993; // +/- 2.75308e-05 cm/us East: Slope = 0.270479 +/- 0.0050959 DV = 5.50993 +/- 2.75308e-05
  row.laserDriftVelocityWest	 =   5.51008; // +/- 4.74343e-05 cm/us West: Slope = 0.276685 +/- 0.00965423 DV = 5.51008 +/- 4.74343e-05
//row.scaleY                  	 = -3.58346e-09;// +/-1.6053e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50997 +/- 2.38109e-05
};
