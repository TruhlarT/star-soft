TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49025
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50216; // +/- 2.73394e-05 cm/us East: Slope = -0.115471 +/- 0.00509308 DV = 5.50216 +/- 2.73394e-05
  row.laserDriftVelocityWest	 =   5.50178; // +/- 2.38437e-05 cm/us West: Slope = -0.0427333 +/- 0.00440056 DV = 5.50178 +/- 2.38437e-05
//row.scaleY                  	 = 6.01327e-06;// +/-3.37486e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50194 +/- 1.79697e-05
};
