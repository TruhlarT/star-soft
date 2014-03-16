TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 60070
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51075; // +/- 3.04842e-05 cm/us East: Slope = 0.610169 +/- 0.005531 DV = 5.51075 +/- 3.04842e-05
  row.laserDriftVelocityWest	 =   5.51601; // +/- 3.14681e-05 cm/us West: Slope = -0.421466 +/- 0.00629243 DV = 5.51601 +/- 3.14681e-05
//row.scaleY                  	 = 9.56931e-07;// +/-1.61627e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5133 +/- 2.18952e-05
};
