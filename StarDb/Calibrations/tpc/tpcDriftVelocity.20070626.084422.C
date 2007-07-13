TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 177019
  row.laserDriftVelocityEast	 =   5.57002; // +/- 2.35772e-05 cm/us All: East = 0.957216 +/- 0.00637858
  row.laserDriftVelocityWest	 =   5.57002; // +/- 2.35772e-05 cm/us All: West = 0.696187 +/- 0.00565424
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57002 +/- 2.35772e-05
  return (TDataSet *)tableSet;// West = 5.57065 +/- 3.15806e-05 East = 5.56922 +/- 3.54381e-05
};
