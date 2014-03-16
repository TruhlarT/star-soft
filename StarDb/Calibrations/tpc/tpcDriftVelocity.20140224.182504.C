TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51133; // +/- 3.7211e-05 cm/us East: Slope = 0.189 +/- 0.00672588 DV = 5.51133 +/- 3.7211e-05
  row.laserDriftVelocityWest	 =   5.51352; // +/- 3.19246e-05 cm/us West: Slope = -0.215879 +/- 0.00617682 DV = 5.51352 +/- 3.19246e-05
//row.scaleY                  	 = 4.33089e-06;// +/-1.73742e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51259 +/- 2.42295e-05
};
