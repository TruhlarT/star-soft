TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38033
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50667; // +/- 3.67156e-05 cm/us East: Slope = 0.817473 +/- 0.00669741 DV = 5.50667 +/- 3.67156e-05
  row.laserDriftVelocityWest	 =   5.51028; // +/- 6.17089e-05 cm/us West: Slope = 0.0170692 +/- 0.0122033 DV = 5.51028 +/- 6.17089e-05
//row.scaleY                  	 = 1.39478e-07;// +/-2.41951e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50761 +/- 3.1553e-05
};
