TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48076
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50004; // +/- 3.87291e-05 cm/us East: Slope = 0.349611 +/- 0.00657678 DV = 5.50004 +/- 3.87291e-05
  row.laserDriftVelocityWest	 =   5.49902; // +/- 3.42574e-05 cm/us West: Slope = 0.355306 +/- 0.0063971 DV = 5.49902 +/- 3.42574e-05
//row.scaleY                  	 = -5.14085e-07;// +/-1.30831e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49946 +/- 2.56597e-05
};
