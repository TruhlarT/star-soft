TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40049
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50607; // +/- 1.45627e-05 cm/us East: Slope = 0.02982 +/- 0.00261559 DV = 5.50607 +/- 1.45627e-05
  row.laserDriftVelocityWest	 =   5.50488; // +/- 2.28039e-05 cm/us West: Slope = 0.245851 +/- 0.00420838 DV = 5.50488 +/- 2.28039e-05
//row.scaleY                  	 = -5.46826e-07;// +/-1.07452e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50572 +/- 1.22735e-05
};
