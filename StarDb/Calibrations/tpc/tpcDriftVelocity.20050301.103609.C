TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6060017
  row.laserDriftVelocityEast	 =   5.53668; // +/- 9.44211e-05 cm/us All: East = 5.5363 +/- 0.000181164
  row.laserDriftVelocityWest	 =   5.53668; // +/- 9.44211e-05 cm/us All: West = 5.53683 +/- 0.000110636
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.3896 +/- 0.0179601
  return (TDataSet *)tableSet;// West = 1.36186 +/- 0.0222873 East = 1.44099 +/- 0.0303317
};
