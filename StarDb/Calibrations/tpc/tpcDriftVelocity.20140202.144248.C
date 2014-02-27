TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33030
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50559; // +/- 3.94647e-05 cm/us East: Slope = 0.186944 +/- 0.00768252 DV = 5.50559 +/- 3.94647e-05
  row.laserDriftVelocityWest	 =   5.50424; // +/- 2.76129e-05 cm/us West: Slope = 0.278513 +/- 0.00459254 DV = 5.50424 +/- 2.76129e-05
//row.scaleY                  	 = 1.49701e-07;// +/-1.30783e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50468 +/- 2.26247e-05
};
