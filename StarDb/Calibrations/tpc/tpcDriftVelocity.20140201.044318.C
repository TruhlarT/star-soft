TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31129
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49914; // +/- 2.44295e-05 cm/us East: Slope = 0.182315 +/- 0.00452213 DV = 5.49914 +/- 2.44295e-05
  row.laserDriftVelocityWest	 =   5.49876; // +/- 3.07041e-05 cm/us West: Slope = 0.281343 +/- 0.00600304 DV = 5.49876 +/- 3.07041e-05
//row.scaleY                  	 = -1.94881e-07;// +/-1.47437e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.499 +/- 1.91168e-05
};
