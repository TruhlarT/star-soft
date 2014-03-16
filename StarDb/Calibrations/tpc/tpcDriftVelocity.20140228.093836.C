TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 59014
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51261; // +/- 3.98191e-05 cm/us East: Slope = 0.362561 +/- 0.00660012 DV = 5.51261 +/- 3.98191e-05
  row.laserDriftVelocityWest	 =   5.51571; // +/- 3.20827e-05 cm/us West: Slope = -0.413155 +/- 0.00624898 DV = 5.51571 +/- 3.20827e-05
//row.scaleY                  	 = 2.87124e-06;// +/-1.65924e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51449 +/- 2.49826e-05
};
