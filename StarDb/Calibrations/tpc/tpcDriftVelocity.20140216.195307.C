TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49614; // +/- 4.06366e-05 cm/us East: Slope = 0.226577 +/- 0.00846394 DV = 5.49614 +/- 4.06366e-05
  row.laserDriftVelocityWest	 =   5.49614; // +/- 4.06366e-05 cm/us West: Slope = 0.226577 +/- 0.00846394 DV = 5.49614 +/- 4.06366e-05
//row.scaleY                  	 = -1.29231e-06;// +/-2.084e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49614 +/- 4.06366e-05
};
