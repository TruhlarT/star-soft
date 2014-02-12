TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37058
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50867; // +/- 5.46507e-05 cm/us East: Slope = 0.427692 +/- 0.0096152 DV = 5.50867 +/- 5.46507e-05
  row.laserDriftVelocityWest	 =   5.50415; // +/- 2.98883e-05 cm/us West: Slope = 0.441269 +/- 0.00567959 DV = 5.50415 +/- 2.98883e-05
//row.scaleY                  	 = -8.19327e-08;// +/-1.72271e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50519 +/- 2.62229e-05
};
