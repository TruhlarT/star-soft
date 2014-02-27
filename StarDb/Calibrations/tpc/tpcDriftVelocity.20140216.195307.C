TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.4963; // +/- 4.15388e-05 cm/us East: Slope = 0.349416 +/- 0.00867585 DV = 5.4963 +/- 4.15388e-05
  row.laserDriftVelocityWest	 =   5.4963; // +/- 4.15388e-05 cm/us West: Slope = 0.349417 +/- 0.00867585 DV = 5.4963 +/- 4.15388e-05
//row.scaleY                  	 = -3.29866e-06;// +/-7.4234e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.4963 +/- 4.15388e-05
};
