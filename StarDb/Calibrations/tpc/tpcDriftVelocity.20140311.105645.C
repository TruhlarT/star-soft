TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 70020
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51824; // +/- 3.64723e-05 cm/us East: Slope = -0.842614 +/- 0.00702031 DV = 5.51824 +/- 3.64723e-05
  row.laserDriftVelocityWest	 =   5.51983; // +/- 3.2013e-05 cm/us West: Slope = -1.11227 +/- 0.00626744 DV = 5.51983 +/- 3.2013e-05
//row.scaleY                  	 = -2.6007e-07;// +/-1.25867e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51914 +/- 2.40596e-05
};
