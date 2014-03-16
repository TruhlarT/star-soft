TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50104; // +/- 3.59987e-05 cm/us East: Slope = 0.26789 +/- 0.00743128 DV = 5.50104 +/- 3.59987e-05
  row.laserDriftVelocityWest	 =   5.50344; // +/- 3.7479e-05 cm/us West: Slope = -0.175363 +/- 0.0073003 DV = 5.50344 +/- 3.7479e-05
//row.scaleY                  	 = -1.9687e-06;// +/-1.94437e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50219 +/- 2.59625e-05
};
