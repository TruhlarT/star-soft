TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 67047
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51568; // +/- 3.37332e-05 cm/us East: Slope = -0.345258 +/- 0.00626715 DV = 5.51568 +/- 3.37332e-05
  row.laserDriftVelocityWest	 =   5.51696; // +/- 2.78405e-05 cm/us West: Slope = -0.583161 +/- 0.00528542 DV = 5.51696 +/- 2.78405e-05
//row.scaleY                  	 = -2.8993e-07;// +/-1.16167e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51644 +/- 2.14721e-05
};
