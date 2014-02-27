TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38033
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50717; // +/- 3.72834e-05 cm/us East: Slope = 0.102836 +/- 0.00667678 DV = 5.50717 +/- 3.72834e-05
  row.laserDriftVelocityWest	 =   5.50408; // +/- 5.44852e-05 cm/us West: Slope = 0.440988 +/- 0.0106593 DV = 5.50408 +/- 5.44852e-05
//row.scaleY                  	 = -9.77427e-06;// +/-1.39401e-08
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50618 +/- 3.07692e-05
};
