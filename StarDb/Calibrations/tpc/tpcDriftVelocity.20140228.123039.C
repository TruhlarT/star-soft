TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 59021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51236; // +/- 3.84596e-05 cm/us East: Slope = 0.251117 +/- 0.00678176 DV = 5.51236 +/- 3.84596e-05
  row.laserDriftVelocityWest	 =   5.51547; // +/- 3.14521e-05 cm/us West: Slope = -0.328598 +/- 0.005985 DV = 5.51547 +/- 3.14521e-05
//row.scaleY                  	 = 2.07011e-06;// +/-2.1717e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51422 +/- 2.43472e-05
};
