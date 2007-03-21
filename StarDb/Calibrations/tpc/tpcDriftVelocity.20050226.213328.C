TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6057061
  row.laserDriftVelocityEast	 =   5.53604; // +/- 7.14596e-05 cm/us All: East = 5.53816 +/- 0.000180816
  row.laserDriftVelocityWest	 =   5.53604; // +/- 7.14596e-05 cm/us All: West = 5.53565 +/- 7.77925e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.20678 +/- 0.0139313
  return (TDataSet *)tableSet;// West = 1.27585 +/- 0.0152095 East = 0.846842 +/- 0.0347181
};
