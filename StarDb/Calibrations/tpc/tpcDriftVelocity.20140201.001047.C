TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31081
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49532; // +/- 2.29574e-05 cm/us East: Slope = 1.03815 +/- 0.00451837 DV = 5.49532 +/- 2.29574e-05
  row.laserDriftVelocityWest	 =   5.48957; // +/- 3.63261e-05 cm/us West: Slope = 2.01183 +/- 0.00899893 DV = 5.48957 +/- 3.63261e-05
//row.scaleY                  	 = -1.21084e-06;// +/-3.41817e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49368 +/- 1.94067e-05
};
