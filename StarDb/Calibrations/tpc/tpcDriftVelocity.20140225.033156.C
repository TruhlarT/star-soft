TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55138
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51179; // +/- 4.31338e-05 cm/us East: Slope = -1.38044 +/- 0.007947 DV = 5.51179 +/- 4.31338e-05
  row.laserDriftVelocityWest	 =   5.50862; // +/- 3.13731e-05 cm/us West: Slope = -0.751439 +/- 0.00581441 DV = 5.50862 +/- 3.13731e-05
//row.scaleY                  	 = -1.16726e-06;// +/-2.54254e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50972 +/- 2.53717e-05
};
