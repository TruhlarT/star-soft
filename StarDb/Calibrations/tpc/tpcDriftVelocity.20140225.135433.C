TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56023
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51104; // +/- 3.74601e-05 cm/us East: Slope = 0.531518 +/- 0.00724417 DV = 5.51104 +/- 3.74601e-05
  row.laserDriftVelocityWest	 =   5.51456; // +/- 3.52347e-05 cm/us West: Slope = -0.187727 +/- 0.00666442 DV = 5.51456 +/- 3.52347e-05
//row.scaleY                  	 = 2.97046e-06;// +/-2.04863e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5129 +/- 2.56654e-05
};
