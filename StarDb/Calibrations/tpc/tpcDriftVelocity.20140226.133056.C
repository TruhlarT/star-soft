TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 57018
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51087; // +/- 2.41596e-05 cm/us East: Slope = 0.538639 +/- 0.004372 DV = 5.51087 +/- 2.41596e-05
  row.laserDriftVelocityWest	 =   5.51531; // +/- 3.0701e-05 cm/us West: Slope = -0.317962 +/- 0.00621085 DV = 5.51531 +/- 3.0701e-05
//row.scaleY                  	 = 1.15872e-06;// +/-1.57833e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51257 +/- 1.89859e-05
};
