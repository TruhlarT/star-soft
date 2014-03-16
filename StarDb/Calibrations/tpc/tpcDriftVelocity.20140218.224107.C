TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49084
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50216; // +/- 3.57079e-05 cm/us East: Slope = 0.464747 +/- 0.00658024 DV = 5.50216 +/- 3.57079e-05
  row.laserDriftVelocityWest	 =   5.50218; // +/- 3.18532e-05 cm/us West: Slope = 0.326834 +/- 0.00587093 DV = 5.50218 +/- 3.18532e-05
//row.scaleY                  	 = -1.22292e-06;// +/-1.80162e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50217 +/- 2.377e-05
};
