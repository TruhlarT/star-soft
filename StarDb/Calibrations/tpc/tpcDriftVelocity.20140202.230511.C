TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33073
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50741; // +/- 3.58225e-05 cm/us East: Slope = -10.4382 +/- 23.2468 DV = 5.50741 +/- 3.58225e-05
  row.laserDriftVelocityWest	 =   5.50545; // +/- 2.45793e-05 cm/us West: Slope = -10.4382 +/- 23.2468 DV = 5.50545 +/- 2.45793e-05
//row.scaleY                  	 = 8.64591e-08;// +/-1.27138e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50608 +/- 2.02672e-05
};
