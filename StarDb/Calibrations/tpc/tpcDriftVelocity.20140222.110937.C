TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53015
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.89418; // +/- 0.000340536 cm/us East: Slope = 5.89418 +/- 0.000340536 DV = 5.89418 +/- 0.000340536
  row.laserDriftVelocityWest	 =   5.89157; // +/- 6.31232e-05 cm/us West: Slope = 5.89418 +/- 0.000340536 DV = 5.89157 +/- 6.31232e-05
//row.scaleY                  	 = -1.41511e-06;// +/-2.08968e-07
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.89166 +/- 6.20659e-05
};
