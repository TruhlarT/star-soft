TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33010
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50367; // +/- 1.93585e-05 cm/us East: Slope = -0.474717 +/- 0.00348166 DV = 5.50367 +/- 1.93585e-05
  row.laserDriftVelocityWest	 =   5.49457; // +/- 2.0847e-05 cm/us West: Slope = -0.416205 +/- 0.00387629 DV = 5.49457 +/- 2.0847e-05
//row.scaleY                  	 = -1.72129e-07;// +/-1.01688e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49946 +/- 1.41856e-05
};
