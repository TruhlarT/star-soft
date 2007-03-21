TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6058060
  row.laserDriftVelocityEast	 =   5.5374; // +/- 5.66035e-05 cm/us All: East = 5.5402 +/- 0.000149645
  row.laserDriftVelocityWest	 =   5.5374; // +/- 5.66035e-05 cm/us All: West = 5.53693 +/- 6.11466e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.27644 +/- 0.0102435
  return (TDataSet *)tableSet;// West = 1.36795 +/- 0.0111227 East = 0.76528 +/- 0.0262882
};
