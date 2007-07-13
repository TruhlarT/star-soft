TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 118011
  row.laserDriftVelocityEast	 =   5.57719; // +/- 1.85303e-05 cm/us All: East = -0.482568 +/- 0.00447722
  row.laserDriftVelocityWest	 =   5.57719; // +/- 1.85303e-05 cm/us All: West = -0.46395 +/- 0.00512853
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57719 +/- 1.85303e-05
  return (TDataSet *)tableSet;// West = 5.5771 +/- 2.80344e-05 East = 5.57725 +/- 2.46939e-05
};
