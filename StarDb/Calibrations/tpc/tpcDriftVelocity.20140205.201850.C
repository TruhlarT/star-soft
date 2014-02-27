TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51018; // +/- 3.16312e-05 cm/us East: Slope = 0.180461 +/- 0.00571872 DV = 5.51018 +/- 3.16312e-05
  row.laserDriftVelocityWest	 =   5.50881; // +/- 2.86035e-05 cm/us West: Slope = 0.400661 +/- 0.0053958 DV = 5.50881 +/- 2.86035e-05
//row.scaleY                  	 = 5.11408e-06;// +/-2.4292e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50943 +/- 2.12156e-05
};
