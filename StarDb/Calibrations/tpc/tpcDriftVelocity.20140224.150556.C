TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55016
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50936; // +/- 4.01803e-05 cm/us East: Slope = 0.556432 +/- 0.00724542 DV = 5.50936 +/- 4.01803e-05
  row.laserDriftVelocityWest	 =   5.51298; // +/- 3.10337e-05 cm/us West: Slope = -0.175232 +/- 0.00617214 DV = 5.51298 +/- 3.10337e-05
//row.scaleY                  	 = 1.53022e-06;// +/-1.93423e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51163 +/- 2.45608e-05
};
