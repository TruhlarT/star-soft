TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138079
  row.laserDriftVelocityEast	 =   5.57443; // +/- 2.57572e-05 cm/us All: East = -0.255218 +/- 0.00862379
  row.laserDriftVelocityWest	 =   5.57443; // +/- 2.57572e-05 cm/us All: West = 0.12007 +/- 0.00549101
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57443 +/- 2.57572e-05
  return (TDataSet *)tableSet;// West = 5.57382 +/- 3.06437e-05 East = 5.57589 +/- 4.7544e-05
};
