TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 70014
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5182; // +/- 3.637e-05 cm/us East: Slope = -0.81463 +/- 0.00684223 DV = 5.5182 +/- 3.637e-05
  row.laserDriftVelocityWest	 =   5.51995; // +/- 3.08847e-05 cm/us West: Slope = -1.146 +/- 0.00601921 DV = 5.51995 +/- 3.08847e-05
//row.scaleY                  	 = -2.10199e-07;// +/-1.19985e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51922 +/- 2.35418e-05
};
