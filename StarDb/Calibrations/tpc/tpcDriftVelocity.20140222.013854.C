TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52065
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50119; // +/- 4.09449e-05 cm/us East: Slope = 0.217134 +/- 0.0074379 DV = 5.50119 +/- 4.09449e-05
  row.laserDriftVelocityWest	 =   5.50319; // +/- 3.52664e-05 cm/us West: Slope = -0.1793 +/- 0.00697382 DV = 5.50319 +/- 3.52664e-05
//row.scaleY                  	 = 1.56645e-06;// +/-2.01426e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50234 +/- 2.67211e-05
};
