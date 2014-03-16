TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 63062
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50961; // +/- 1.90046e-05 cm/us East: Slope = 0.740457 +/- 0.00341789 DV = 5.50961 +/- 1.90046e-05
  row.laserDriftVelocityWest	 =   5.51551; // +/- 2.35874e-05 cm/us West: Slope = -0.348053 +/- 0.00434886 DV = 5.51551 +/- 2.35874e-05
//row.scaleY                  	 = -1.23828e-06;// +/-1.57769e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51193 +/- 1.47988e-05
};
