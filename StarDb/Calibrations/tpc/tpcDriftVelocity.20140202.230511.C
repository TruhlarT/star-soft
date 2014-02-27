TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33073
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50775; // +/- 3.76059e-05 cm/us East: Slope = 0.114604 +/- 0.00686885 DV = 5.50775 +/- 3.76059e-05
  row.laserDriftVelocityWest	 =   5.50721; // +/- 2.29146e-05 cm/us West: Slope = 0.232889 +/- 0.00416487 DV = 5.50721 +/- 2.29146e-05
//row.scaleY                  	 = 3.67395e-06;// +/-1.92274e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50736 +/- 1.9568e-05
};
