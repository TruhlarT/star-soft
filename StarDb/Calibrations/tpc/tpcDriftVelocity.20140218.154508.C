TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49033
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5032; // +/- 6.19853e-05 cm/us East: Slope = 0.0969108 +/- 0.0101255 DV = 5.5032 +/- 6.19853e-05
  row.laserDriftVelocityWest	 =   5.50276; // +/- 2.90769e-05 cm/us West: Slope = 0.153371 +/- 0.00541716 DV = 5.50276 +/- 2.90769e-05
//row.scaleY                  	 = -4.73486e-06;// +/-3.98188e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50284 +/- 2.63245e-05
};
