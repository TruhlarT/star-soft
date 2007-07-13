TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138094
  row.laserDriftVelocityEast	 =   5.57424; // +/- 3.53076e-05 cm/us All: East = 0.086155 +/- 0.0106582
  row.laserDriftVelocityWest	 =   5.57424; // +/- 3.53076e-05 cm/us All: West = 0.0266835 +/- 0.00776387
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57424 +/- 3.53076e-05
  return (TDataSet *)tableSet;// West = 5.5744 +/- 4.25088e-05 East = 5.57388 +/- 6.34031e-05
};
