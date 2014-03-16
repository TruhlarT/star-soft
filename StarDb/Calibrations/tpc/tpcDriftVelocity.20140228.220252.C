TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 59063
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51319; // +/- 2.91378e-05 cm/us East: Slope = 0.100265 +/- 0.00541083 DV = 5.51319 +/- 2.91378e-05
  row.laserDriftVelocityWest	 =   5.51574; // +/- 3.25677e-05 cm/us West: Slope = -0.390056 +/- 0.00623966 DV = 5.51574 +/- 3.25677e-05
//row.scaleY                  	 = 7.48559e-06;// +/-1.67093e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51433 +/- 2.17152e-05
};
