TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51113; // +/- 3.9863e-05 cm/us East: Slope = 0.0623186 +/- 0.00748752 DV = 5.51113 +/- 3.9863e-05
  row.laserDriftVelocityWest	 =   5.51192; // +/- 2.93051e-05 cm/us West: Slope = -0.148596 +/- 0.00560361 DV = 5.51192 +/- 2.93051e-05
//row.scaleY                  	 = -2.23866e-07;// +/-1.30061e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51165 +/- 2.36114e-05
};
