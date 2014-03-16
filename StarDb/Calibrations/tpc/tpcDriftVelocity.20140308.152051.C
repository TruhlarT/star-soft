TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 67023
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51873; // +/- 3.52228e-05 cm/us East: Slope = -0.906273 +/- 0.00697692 DV = 5.51873 +/- 3.52228e-05
  row.laserDriftVelocityWest	 =   5.52004; // +/- 3.10387e-05 cm/us West: Slope = -1.14779 +/- 0.00615351 DV = 5.52004 +/- 3.10387e-05
//row.scaleY                  	 = -2.86565e-07;// +/-1.22853e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51947 +/- 2.32872e-05
};
