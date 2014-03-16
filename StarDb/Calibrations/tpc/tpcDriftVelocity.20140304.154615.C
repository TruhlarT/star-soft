TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 63034
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51214; // +/- 4.37623e-05 cm/us East: Slope = 0.320757 +/- 0.00894039 DV = 5.51214 +/- 4.37623e-05
  row.laserDriftVelocityWest	 =   5.51457; // +/- 3.19935e-05 cm/us West: Slope = -0.174643 +/- 0.00596507 DV = 5.51457 +/- 3.19935e-05
//row.scaleY                  	 = 3.79802e-06;// +/-1.86357e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51372 +/- 2.58275e-05
};
