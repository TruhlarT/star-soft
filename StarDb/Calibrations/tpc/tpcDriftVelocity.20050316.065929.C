TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6075017
  row.laserDriftVelocityEast	 =   5.53025; // +/- 4.99762e-05 cm/us All: East = 5.53066 +/- 7.82087e-05
  row.laserDriftVelocityWest	 =   5.53025; // +/- 4.99762e-05 cm/us All: West = 5.52996 +/- 6.49719e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.313964 +/- 0.00892279
  return (TDataSet *)tableSet;// West = 0.359469 +/- 0.0116007 East = 0.248044 +/- 0.0139624
};
