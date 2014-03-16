TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56114
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51024; // +/- 2.40603e-05 cm/us East: Slope = 0.558429 +/- 0.004325 DV = 5.51024 +/- 2.40603e-05
  row.laserDriftVelocityWest	 =   5.51382; // +/- 3.58545e-05 cm/us West: Slope = -0.179359 +/- 0.00725216 DV = 5.51382 +/- 3.58545e-05
//row.scaleY                  	 = 2.51812e-06;// +/-1.60801e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51135 +/- 1.99788e-05
};
