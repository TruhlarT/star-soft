TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 144002
  row.laserDriftVelocityEast	 =   5.57366; // +/- 1.2486e-05 cm/us All: East = -17.5725 +/- 0.0729832
  row.laserDriftVelocityWest	 =   5.57366; // +/- 1.2486e-05 cm/us All: West = -17.6749 +/- 0.00219583
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57366 +/- 1.2486e-05
  return (TDataSet *)tableSet;// West = 5.57366 +/- 1.24953e-05 East = 5.57308 +/- 0.000323172
};
