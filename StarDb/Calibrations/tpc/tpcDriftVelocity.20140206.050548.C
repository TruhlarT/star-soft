TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37001
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50983; // +/- 3.79805e-05 cm/us East: Slope = 0.232489 +/- 0.00655925 DV = 5.50983 +/- 3.79805e-05
  row.laserDriftVelocityWest	 =   5.50767; // +/- 3.20197e-05 cm/us West: Slope = 0.592073 +/- 0.00612788 DV = 5.50767 +/- 3.20197e-05
//row.scaleY                  	 = -1.39688e-07;// +/-1.21777e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50857 +/- 2.44807e-05
};
