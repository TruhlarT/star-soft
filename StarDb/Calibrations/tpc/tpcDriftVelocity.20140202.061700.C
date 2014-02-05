TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33010
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50368; // +/- 1.95261e-05 cm/us East: Slope = -0.473909 +/- 0.00351641 DV = 5.50368 +/- 1.95261e-05
  row.laserDriftVelocityWest	 =   5.49461; // +/- 2.1093e-05 cm/us West: Slope = -0.411827 +/- 0.00391088 DV = 5.49461 +/- 2.1093e-05
//row.scaleY                  	 = -1.72103e-07;// +/-1.02661e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49949 +/- 1.4329e-05
};
