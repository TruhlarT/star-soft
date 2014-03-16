TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 58008
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51131; // +/- 2.43905e-05 cm/us East: Slope = 0.481613 +/- 0.00448652 DV = 5.51131 +/- 2.43905e-05
  row.laserDriftVelocityWest	 =   5.51571; // +/- 3.28043e-05 cm/us West: Slope = -0.387519 +/- 0.00657419 DV = 5.51571 +/- 3.28043e-05
//row.scaleY                  	 = 8.33059e-06;// +/-1.7158e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51288 +/- 1.95732e-05
};
