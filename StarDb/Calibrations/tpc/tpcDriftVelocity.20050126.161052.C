TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6026064
  row.laserDriftVelocityEast	 =   5.55373; // +/- 0.000206665 cm/us All: East = 5.55475 +/- 0.000447221
  row.laserDriftVelocityWest	 =   5.55373; // +/- 0.000206665 cm/us All: West = 5.55346 +/- 0.000233039
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -15.7629 +/- 0.0360929
  return (TDataSet *)tableSet;// West = -15.7117 +/- 0.040837 East = -15.9456 +/- 0.0771527
};
