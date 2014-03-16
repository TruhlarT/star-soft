TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 66006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51877; // +/- 3.34716e-05 cm/us East: Slope = -0.900959 +/- 0.00644023 DV = 5.51877 +/- 3.34716e-05
  row.laserDriftVelocityWest	 =   5.51972; // +/- 4.91797e-05 cm/us West: Slope = -1.20131 +/- 0.0101398 DV = 5.51972 +/- 4.91797e-05
//row.scaleY                  	 = -4.35635e-07;// +/-1.36576e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51907 +/- 2.76708e-05
};
