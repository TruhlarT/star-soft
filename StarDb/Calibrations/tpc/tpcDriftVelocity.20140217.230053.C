TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48082
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5026; // +/- 4.81793e-05 cm/us East: Slope = 0.472306 +/- 0.00926483 DV = 5.5026 +/- 4.81793e-05
  row.laserDriftVelocityWest	 =   5.50322; // +/- 4.36765e-05 cm/us West: Slope = 0.183509 +/- 0.00926454 DV = 5.50322 +/- 4.36765e-05
//row.scaleY                  	 = 2.68752e-06;// +/-2.95153e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50294 +/- 3.2359e-05
};
