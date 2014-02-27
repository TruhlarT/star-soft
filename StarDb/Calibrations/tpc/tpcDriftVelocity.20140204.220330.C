TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35073
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5117; // +/- 2.66137e-05 cm/us East: Slope = 0.0689602 +/- 0.00475364 DV = 5.5117 +/- 2.66137e-05
  row.laserDriftVelocityWest	 =   5.51109; // +/- 3.12883e-05 cm/us West: Slope = 0.183238 +/- 0.00739551 DV = 5.51109 +/- 3.12883e-05
//row.scaleY                  	 = 9.48596e-06;// +/-2.56043e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51144 +/- 2.0272e-05
};
