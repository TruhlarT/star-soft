TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33010
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50368; // +/- 1.9511e-05 cm/us East: Slope = 0.260506 +/- 0.00350441 DV = 5.50368 +/- 1.9511e-05
  row.laserDriftVelocityWest	 =   5.48362; // +/- 2.66242e-05 cm/us West: Slope = 0.367317 +/- 0.00510021 DV = 5.48362 +/- 2.66242e-05
//row.scaleY                  	 = -1.78225e-07;// +/-1.00803e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49667 +/- 1.57375e-05
};
