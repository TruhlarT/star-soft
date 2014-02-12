TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50575; // +/- 3.86332e-05 cm/us East: Slope = 0.982531 +/- 0.00746144 DV = 5.50575 +/- 3.86332e-05
  row.laserDriftVelocityWest	 =   5.50575; // +/- 3.86332e-05 cm/us West: Slope = 0.982531 +/- 0.00746144 DV = 5.50575 +/- 3.86332e-05
//row.scaleY                  	 = 2.21681e-07;// +/-1.41909e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50575 +/- 3.86332e-05
};
