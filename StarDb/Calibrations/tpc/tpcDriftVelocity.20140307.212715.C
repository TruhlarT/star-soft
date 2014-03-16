TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 66065
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.519; // +/- 3.5022e-05 cm/us East: Slope = -0.951007 +/- 0.00663853 DV = 5.519 +/- 3.5022e-05
  row.laserDriftVelocityWest	 =   5.51982; // +/- 3.07059e-05 cm/us West: Slope = -1.08598 +/- 0.00593754 DV = 5.51982 +/- 3.07059e-05
//row.scaleY                  	 = -3.30803e-07;// +/-1.20915e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51946 +/- 2.30884e-05
};
