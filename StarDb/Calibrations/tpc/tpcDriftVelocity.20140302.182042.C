TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 61039
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51159; // +/- 2.90198e-05 cm/us East: Slope = 0.441531 +/- 0.00542572 DV = 5.51159 +/- 2.90198e-05
  row.laserDriftVelocityWest	 =   5.51527; // +/- 3.02427e-05 cm/us West: Slope = -0.307317 +/- 0.00571544 DV = 5.51527 +/- 3.02427e-05
//row.scaleY                  	 = 2.0202e-06;// +/-1.86483e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51335 +/- 2.09391e-05
};
