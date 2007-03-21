TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6028005
  row.laserDriftVelocityEast	 =   5.55379; // +/- 4.17271e-05 cm/us All: East = 5.55393 +/- 9.66109e-05
  row.laserDriftVelocityWest	 =   5.55379; // +/- 4.17271e-05 cm/us All: West = 5.55376 +/- 4.62649e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.1625 +/- 0.0095158
  return (TDataSet *)tableSet;// West = 2.17033 +/- 0.0106949 East = 2.13271 +/- 0.0208477
};
