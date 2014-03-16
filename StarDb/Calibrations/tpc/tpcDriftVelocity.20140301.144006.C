TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 60029
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51214; // +/- 3.2163e-05 cm/us East: Slope = 0.346064 +/- 0.00598265 DV = 5.51214 +/- 3.2163e-05
  row.laserDriftVelocityWest	 =   5.51619; // +/- 3.1102e-05 cm/us West: Slope = -0.474092 +/- 0.00591265 DV = 5.51619 +/- 3.1102e-05
//row.scaleY                  	 = 6.82295e-06;// +/-1.68036e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51423 +/- 2.23581e-05
};
