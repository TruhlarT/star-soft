TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 146088
  row.laserDriftVelocityEast	 =   5.57386; // +/- 1.69832e-05 cm/us All: East = 0.43956 +/- 1.06538
  row.laserDriftVelocityWest	 =   5.57386; // +/- 1.69832e-05 cm/us All: West = 0.119865 +/- 0.00307087
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57386 +/- 1.69832e-05
  return (TDataSet *)tableSet;// West = 5.57386 +/- 1.69832e-05 East = 5.57628 +/- 0.0109063
};
