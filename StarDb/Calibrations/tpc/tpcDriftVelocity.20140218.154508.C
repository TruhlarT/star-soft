TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49033
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50249; // +/- 4.46996e-05 cm/us East: Slope = 0.115573 +/- 0.0105889 DV = 5.50249 +/- 4.46996e-05
  row.laserDriftVelocityWest	 =   5.50272; // +/- 2.9235e-05 cm/us West: Slope = 0.261581 +/- 0.00548471 DV = 5.50272 +/- 2.9235e-05
//row.scaleY                  	 = -1.21968e-06;// +/-2.14291e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50265 +/- 2.44667e-05
};
