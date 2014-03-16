TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56038
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51246; // +/- 3.57122e-05 cm/us East: Slope = 0.229183 +/- 0.00691698 DV = 5.51246 +/- 3.57122e-05
  row.laserDriftVelocityWest	 =   5.51469; // +/- 3.03047e-05 cm/us West: Slope = -0.185763 +/- 0.00529259 DV = 5.51469 +/- 3.03047e-05
//row.scaleY                  	 = 4.92413e-05;// +/-1.52074e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51375 +/- 2.31065e-05
};
