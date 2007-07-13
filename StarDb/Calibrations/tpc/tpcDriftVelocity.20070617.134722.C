TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 168047
  row.laserDriftVelocityEast	 =   5.57122; // +/- 2.52886e-05 cm/us All: East = 0.760404 +/- 0.00587046
  row.laserDriftVelocityWest	 =   5.57122; // +/- 2.52886e-05 cm/us All: West = 0.359936 +/- 0.00697891
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57122 +/- 2.52886e-05
  return (TDataSet *)tableSet;// West = 5.57252 +/- 3.90217e-05 East = 5.57028 +/- 3.32051e-05
};
