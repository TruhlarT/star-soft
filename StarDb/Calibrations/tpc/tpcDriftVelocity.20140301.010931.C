TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 59076
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51056; // +/- 3.17104e-05 cm/us East: Slope = 0.619258 +/- 0.00594074 DV = 5.51056 +/- 3.17104e-05
  row.laserDriftVelocityWest	 =   5.51677; // +/- 3.41818e-05 cm/us West: Slope = -0.59089 +/- 0.00650193 DV = 5.51677 +/- 3.41818e-05
//row.scaleY                  	 = 3.40442e-06;// +/-1.67837e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51343 +/- 2.32473e-05
};
