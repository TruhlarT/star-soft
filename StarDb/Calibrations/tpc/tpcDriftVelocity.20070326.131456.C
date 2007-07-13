TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 85098
  row.laserDriftVelocityEast	 =   5.5669; // +/- 6.06441e-05 cm/us All: East = 0.0625104 +/- 0.011427
  row.laserDriftVelocityWest	 =   5.5669; // +/- 6.06441e-05 cm/us All: West = -0.0341628 +/- 0.0354292
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5669 +/- 6.06441e-05
  return (TDataSet *)tableSet;// West = 5.56723 +/- 0.000229719 East = 5.56687 +/- 6.28746e-05
};
