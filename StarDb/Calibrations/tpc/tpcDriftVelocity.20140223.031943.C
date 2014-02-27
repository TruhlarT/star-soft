TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53064
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.79215; // +/- 5.18447e-05 cm/us East: Slope = 5.79215 +/- 5.18447e-05 DV = 5.79215 +/- 5.18447e-05
  row.laserDriftVelocityWest	 =   5.78886; // +/- 4.71959e-05 cm/us West: Slope = 5.79215 +/- 5.18447e-05 DV = 5.78886 +/- 4.71959e-05
//row.scaleY                  	 = -2.73111e-05;// +/-3.76296e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.79035 +/- 3.49006e-05
};
