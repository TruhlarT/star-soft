TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 59006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51116; // +/- 3.32485e-05 cm/us East: Slope = 0.431168 +/- 0.00590017 DV = 5.51116 +/- 3.32485e-05
  row.laserDriftVelocityWest	 =   5.51597; // +/- 3.37665e-05 cm/us West: Slope = -0.446422 +/- 0.00670283 DV = 5.51597 +/- 3.37665e-05
//row.scaleY                  	 = 1.28911e-06;// +/-1.88184e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51353 +/- 2.36913e-05
};
