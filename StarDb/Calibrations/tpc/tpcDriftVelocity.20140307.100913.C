TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 66016
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51857; // +/- 3.24085e-05 cm/us East: Slope = -0.859913 +/- 0.00610367 DV = 5.51857 +/- 3.24085e-05
  row.laserDriftVelocityWest	 =   5.52059; // +/- 2.92678e-05 cm/us West: Slope = -1.2865 +/- 0.0056042 DV = 5.52059 +/- 2.92678e-05
//row.scaleY                  	 = -3.10291e-07;// +/-1.22406e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51968 +/- 2.17212e-05
};
