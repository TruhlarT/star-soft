TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48016
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50017; // +/- 2.76239e-05 cm/us East: Slope = 1.13518 +/- 0.00515283 DV = 5.50017 +/- 2.76239e-05
  row.laserDriftVelocityWest	 =   5.50038; // +/- 2.33323e-05 cm/us West: Slope = 1.07424 +/- 0.00432207 DV = 5.50038 +/- 2.33323e-05
//row.scaleY                  	 = 3.92785e-06;// +/-2.07491e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50029 +/- 1.78249e-05
};
