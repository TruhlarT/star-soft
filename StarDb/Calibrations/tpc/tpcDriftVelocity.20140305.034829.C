TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 63066
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50997; // +/- 3.72587e-05 cm/us East: Slope = 0.681345 +/- 0.00657394 DV = 5.50997 +/- 3.72587e-05
  row.laserDriftVelocityWest	 =   5.5153; // +/- 2.60827e-05 cm/us West: Slope = -0.314547 +/- 0.00479407 DV = 5.5153 +/- 2.60827e-05
//row.scaleY                  	 = -1.13586e-06;// +/-2.51477e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51355 +/- 2.13674e-05
};
