TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48082
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50345; // +/- 3.86374e-05 cm/us East: Slope = -0.0697771 +/- 0.0078469 DV = 5.50345 +/- 3.86374e-05
  row.laserDriftVelocityWest	 =   5.50131; // +/- 3.73664e-05 cm/us West: Slope = 0.0516647 +/- 0.00763134 DV = 5.50131 +/- 3.73664e-05
//row.scaleY                  	 = 9.80859e-07;// +/-3.11177e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50234 +/- 2.68601e-05
};
