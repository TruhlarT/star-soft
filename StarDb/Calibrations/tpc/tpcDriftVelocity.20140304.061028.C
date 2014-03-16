TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 63003
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51125; // +/- 3.56849e-05 cm/us East: Slope = 0.465339 +/- 0.00693643 DV = 5.51125 +/- 3.56849e-05
  row.laserDriftVelocityWest	 =   5.51454; // +/- 3.23229e-05 cm/us West: Slope = -0.166574 +/- 0.00574779 DV = 5.51454 +/- 3.23229e-05
//row.scaleY                  	 = 4.83273e-06;// +/-1.73606e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51306 +/- 2.39564e-05
};
