TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56004
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51219; // +/- 4.6551e-05 cm/us East: Slope = -1.38518 +/- 0.0101016 DV = 5.51219 +/- 4.6551e-05
  row.laserDriftVelocityWest	 =   5.50883; // +/- 3.5547e-05 cm/us West: Slope = -0.78344 +/- 0.0066876 DV = 5.50883 +/- 3.5547e-05
//row.scaleY                  	 = 1.34729e-07;// +/-2.2067e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51007 +/- 2.82519e-05
};
