TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 67015
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51914; // +/- 3.63398e-05 cm/us East: Slope = -0.971353 +/- 0.00682874 DV = 5.51914 +/- 3.63398e-05
  row.laserDriftVelocityWest	 =   5.52005; // +/- 2.94716e-05 cm/us West: Slope = -1.15607 +/- 0.005662 DV = 5.52005 +/- 2.94716e-05
//row.scaleY                  	 = -2.38362e-07;// +/-1.1605e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51969 +/- 2.28901e-05
};
