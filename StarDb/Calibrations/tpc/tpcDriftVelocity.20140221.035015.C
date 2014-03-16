TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51157
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50099; // +/- 3.56114e-05 cm/us East: Slope = 0.519429 +/- 0.00634871 DV = 5.50099 +/- 3.56114e-05
  row.laserDriftVelocityWest	 =   5.50403; // +/- 3.22138e-05 cm/us West: Slope = -0.0313023 +/- 0.00633383 DV = 5.50403 +/- 3.22138e-05
//row.scaleY                  	 = -1.34857e-06;// +/-1.79041e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50266 +/- 2.38897e-05
};
