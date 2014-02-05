TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50043; // +/- 4.72981e-05 cm/us East: Slope = 0.0970368 +/- 0.0138351 DV = 5.50043 +/- 4.72981e-05
  row.laserDriftVelocityWest	 =   5.48532; // +/- 6.55736e-05 cm/us West: Slope = 2.83564 +/- 0.0175616 DV = 5.48532 +/- 6.55736e-05
//row.scaleY                  	 = -1.04412e-06;// +/-2.53477e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49526 +/- 3.83604e-05
};
