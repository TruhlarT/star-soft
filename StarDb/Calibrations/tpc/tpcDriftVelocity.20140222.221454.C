TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53048
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50554; // +/- 3.91415e-05 cm/us East: Slope = 0.339089 +/- 0.00698562 DV = 5.50554 +/- 3.91415e-05
  row.laserDriftVelocityWest	 =   5.50803; // +/- 3.6141e-05 cm/us West: Slope = -0.183473 +/- 0.00703709 DV = 5.50803 +/- 3.6141e-05
//row.scaleY                  	 = 3.18e-06;// +/-1.87887e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50689 +/- 2.6553e-05
};
