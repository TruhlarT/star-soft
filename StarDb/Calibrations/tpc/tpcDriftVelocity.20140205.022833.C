TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35084
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51112; // +/- 3.25966e-05 cm/us East: Slope = 0.213778 +/- 0.00596081 DV = 5.51112 +/- 3.25966e-05
  row.laserDriftVelocityWest	 =   5.50698; // +/- 3.6459e-05 cm/us West: Slope = 0.971684 +/- 0.00680641 DV = 5.50698 +/- 3.6459e-05
//row.scaleY                  	 = -1.88994e-07;// +/-1.19555e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50928 +/- 2.43005e-05
};
