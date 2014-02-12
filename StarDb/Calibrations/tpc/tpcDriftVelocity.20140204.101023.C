TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51021; // +/- 3.36398e-05 cm/us East: Slope = 0.179733 +/- 0.00677508 DV = 5.51021 +/- 3.36398e-05
  row.laserDriftVelocityWest	 =   5.5094; // +/- 3.31603e-05 cm/us West: Slope = 0.054215 +/- 0.00554327 DV = 5.5094 +/- 3.31603e-05
//row.scaleY                  	 = -2.40433e-07;// +/-1.22638e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5098 +/- 2.36156e-05
};
