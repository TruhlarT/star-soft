TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6051039
  row.laserDriftVelocityEast	 =   5.53475; // +/- 5.96271e-05 cm/us All: East = 5.53536 +/- 0.000110314
  row.laserDriftVelocityWest	 =   5.53475; // +/- 5.96271e-05 cm/us All: West = 5.5345 +/- 7.08725e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.00518 +/- 0.0109282
  return (TDataSet *)tableSet;// West = 1.06063 +/- 0.0131253 East = 0.879874 +/- 0.0197305
};
