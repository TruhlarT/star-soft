TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48088
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50222; // +/- 3.52585e-05 cm/us East: Slope = 0.235301 +/- 0.0066756 DV = 5.50222 +/- 3.52585e-05
  row.laserDriftVelocityWest	 =   5.49811; // +/- 3.20487e-05 cm/us West: Slope = 0.465035 +/- 0.00616156 DV = 5.49811 +/- 3.20487e-05
//row.scaleY                  	 = -1.18303e-06;// +/-1.78716e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49997 +/- 2.37156e-05
};
