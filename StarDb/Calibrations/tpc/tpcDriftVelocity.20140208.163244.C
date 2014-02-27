TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39166
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50646; // +/- 9.44316e-05 cm/us East: Slope = 0.351981 +/- 0.0245709 DV = 5.50646 +/- 9.44316e-05
  row.laserDriftVelocityWest	 =   5.50677; // +/- 5.29273e-05 cm/us West: Slope = 0.333485 +/- 0.0112286 DV = 5.50677 +/- 5.29273e-05
//row.scaleY                  	 = 2.37976e-07;// +/-3.15434e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5067 +/- 4.61699e-05
};
