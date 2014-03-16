TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 61028
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51144; // +/- 2.93835e-05 cm/us East: Slope = 0.487452 +/- 0.00543853 DV = 5.51144 +/- 2.93835e-05
  row.laserDriftVelocityWest	 =   5.51577; // +/- 3.04418e-05 cm/us West: Slope = -0.404217 +/- 0.00604908 DV = 5.51577 +/- 3.04418e-05
//row.scaleY                  	 = -2.37927e-07;// +/-1.75014e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51353 +/- 2.11415e-05
};
