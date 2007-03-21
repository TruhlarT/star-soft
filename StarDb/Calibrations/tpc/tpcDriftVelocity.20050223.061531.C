TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6054012
  row.laserDriftVelocityEast	 =   5.53338; // +/- 4.22492e-05 cm/us All: East = 5.5358 +/- 8.94005e-05
  row.laserDriftVelocityWest	 =   5.53338; // +/- 4.22492e-05 cm/us All: West = 5.53269 +/- 4.79404e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.14042 +/- 0.00761619
  return (TDataSet *)tableSet;// West = 1.26884 +/- 0.00868072 East = 0.711041 +/- 0.0158731
};
