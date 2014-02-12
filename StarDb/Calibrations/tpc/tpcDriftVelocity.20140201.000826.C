TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31080
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49577; // +/- 5.35998e-05 cm/us East: Slope = 0.990267 +/- 0.0163438 DV = 5.49577 +/- 5.35998e-05
  row.laserDriftVelocityWest	 =   5.48968; // +/- 8.00584e-05 cm/us West: Slope = 2.06106 +/- 0.0343848 DV = 5.48968 +/- 8.00584e-05
//row.scaleY                  	 = -3.89995e-07;// +/-2.99849e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49388 +/- 4.45392e-05
};
