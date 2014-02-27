TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50405; // +/- 4.29016e-05 cm/us East: Slope = 0.256463 +/- 0.00799532 DV = 5.50405 +/- 4.29016e-05
  row.laserDriftVelocityWest	 =   5.50452; // +/- 2.77319e-05 cm/us West: Slope = 0.180766 +/- 0.00509948 DV = 5.50452 +/- 2.77319e-05
//row.scaleY                  	 = -1.34029e-07;// +/-3.77059e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50438 +/- 2.32898e-05
};
