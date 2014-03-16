TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51106; // +/- 3.91569e-05 cm/us East: Slope = 0.21713 +/- 0.00753506 DV = 5.51106 +/- 3.91569e-05
  row.laserDriftVelocityWest	 =   5.51178; // +/- 2.97193e-05 cm/us West: Slope = 0.453735 +/- 0.00712043 DV = 5.51178 +/- 2.97193e-05
//row.scaleY                  	 = -2.24484e-07;// +/-1.30093e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51152 +/- 2.3673e-05
};
