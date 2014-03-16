TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56004
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51222; // +/- 3.60629e-05 cm/us East: Slope = 0.192303 +/- 0.00724756 DV = 5.51222 +/- 3.60629e-05
  row.laserDriftVelocityWest	 =   5.51436; // +/- 2.85163e-05 cm/us West: Slope = -0.200036 +/- 0.00517417 DV = 5.51436 +/- 2.85163e-05
//row.scaleY                  	 = 6.16179e-06;// +/-1.642e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51353 +/- 2.23682e-05
};
