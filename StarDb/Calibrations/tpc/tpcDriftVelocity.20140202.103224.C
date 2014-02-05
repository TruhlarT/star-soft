TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33019
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50479; // +/- 1.95936e-05 cm/us East: Slope = -0.678337 +/- 0.00349291 DV = 5.50479 +/- 1.95936e-05
  row.laserDriftVelocityWest	 =   5.50382; // +/- 2.14109e-05 cm/us West: Slope = -0.517978 +/- 0.00379634 DV = 5.50382 +/- 2.14109e-05
//row.scaleY                  	 = -1.68197e-07;// +/-1.02927e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50435 +/- 1.44546e-05
};
