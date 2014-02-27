TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51108; // +/- 3.95274e-05 cm/us East: Slope = 0.234519 +/- 0.00745097 DV = 5.51108 +/- 3.95274e-05
  row.laserDriftVelocityWest	 =   5.50902; // +/- 2.92723e-05 cm/us West: Slope = 0.542024 +/- 0.00561024 DV = 5.50902 +/- 2.92723e-05
//row.scaleY                  	 = -2.24625e-07;// +/-1.30136e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50975 +/- 2.3524e-05
};
