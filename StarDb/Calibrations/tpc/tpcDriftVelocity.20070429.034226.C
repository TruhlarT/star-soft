TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 118082
  row.laserDriftVelocityEast	 =   5.57781; // +/- 1.69982e-05 cm/us All: East = -0.599406 +/- 0.00386341
  row.laserDriftVelocityWest	 =   5.57781; // +/- 1.69982e-05 cm/us All: West = -0.579353 +/- 0.00515721
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57781 +/- 1.69982e-05
  return (TDataSet *)tableSet;// West = 5.57777 +/- 2.8513e-05 East = 5.57783 +/- 2.11718e-05
};
