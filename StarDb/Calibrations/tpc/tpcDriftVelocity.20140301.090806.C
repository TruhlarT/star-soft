TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 60015
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51269; // +/- 2.73155e-05 cm/us East: Slope = 0.550782 +/- 0.00509901 DV = 5.51269 +/- 2.73155e-05
  row.laserDriftVelocityWest	 =   5.51622; // +/- 3.15161e-05 cm/us West: Slope = -0.477907 +/- 0.00609588 DV = 5.51622 +/- 3.15161e-05
//row.scaleY                  	 = 6.3144e-06;// +/-1.78095e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51421 +/- 2.06415e-05
};
