TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 67002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51949; // +/- 3.81559e-05 cm/us East: Slope = -1.04673 +/- 0.00727524 DV = 5.51949 +/- 3.81559e-05
  row.laserDriftVelocityWest	 =   5.51997; // +/- 2.92154e-05 cm/us West: Slope = -1.1189 +/- 0.00561925 DV = 5.51997 +/- 2.92154e-05
//row.scaleY                  	 = -2.33728e-07;// +/-1.18685e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51979 +/- 2.31965e-05
};
