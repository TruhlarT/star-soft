TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52074
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50296; // +/- 4.57271e-05 cm/us East: Slope = 0.315922 +/- 0.00888463 DV = 5.50296 +/- 4.57271e-05
  row.laserDriftVelocityWest	 =   5.49989; // +/- 3.49146e-05 cm/us West: Slope = 0.848098 +/- 0.00669285 DV = 5.49989 +/- 3.49146e-05
//row.scaleY                  	 = -2.20307e-07;// +/-3.89943e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50102 +/- 2.77502e-05
};
