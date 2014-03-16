TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33063
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50685; // +/- 3.27151e-05 cm/us East: Slope = 0.287853 +/- 0.00620808 DV = 5.50685 +/- 3.27151e-05
  row.laserDriftVelocityWest	 =   5.50537; // +/- 2.65514e-05 cm/us West: Slope = 0.575081 +/- 0.00481241 DV = 5.50537 +/- 2.65514e-05
//row.scaleY                  	 = 4.73108e-08;// +/-1.26096e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50596 +/- 2.06161e-05
};
