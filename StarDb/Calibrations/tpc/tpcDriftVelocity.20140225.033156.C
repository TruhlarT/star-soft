TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55138
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51188; // +/- 3.51795e-05 cm/us East: Slope = 0.187493 +/- 0.00690274 DV = 5.51188 +/- 3.51795e-05
  row.laserDriftVelocityWest	 =   5.51387; // +/- 2.92384e-05 cm/us West: Slope = -0.1869 +/- 0.00525309 DV = 5.51387 +/- 2.92384e-05
//row.scaleY                  	 = 5.82909e-06;// +/-1.69873e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51306 +/- 2.2486e-05
};
