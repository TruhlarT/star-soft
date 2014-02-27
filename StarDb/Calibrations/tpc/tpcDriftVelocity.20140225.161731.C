TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56028
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51278; // +/- 4.58777e-05 cm/us East: Slope = -1.50943 +/- 0.010492 DV = 5.51278 +/- 4.58777e-05
  row.laserDriftVelocityWest	 =   5.50928; // +/- 3.34161e-05 cm/us West: Slope = -0.862945 +/- 0.00647943 DV = 5.50928 +/- 3.34161e-05
//row.scaleY                  	 = 3.81124e-06;// +/-2.59312e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51049 +/- 2.70107e-05
};
