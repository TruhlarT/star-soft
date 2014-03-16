TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 58002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51299; // +/- 2.90628e-05 cm/us East: Slope = 0.137242 +/- 0.00558395 DV = 5.51299 +/- 2.90628e-05
  row.laserDriftVelocityWest	 =   5.51549; // +/- 3.44396e-05 cm/us West: Slope = -0.372032 +/- 0.0067637 DV = 5.51549 +/- 3.44396e-05
//row.scaleY                  	 = 0.0203045;// +/-5.94705e-11
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51403 +/- 2.2211e-05
};
