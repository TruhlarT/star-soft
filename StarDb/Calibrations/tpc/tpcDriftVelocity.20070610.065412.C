TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 161018
  row.laserDriftVelocityEast	 =   5.57286; // +/- 2.06552e-05 cm/us All: East = 0.404502 +/- 0.0130384
  row.laserDriftVelocityWest	 =   5.57286; // +/- 2.06552e-05 cm/us All: West = 0.289112 +/- 0.00384745
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57286 +/- 2.06552e-05
  return (TDataSet *)tableSet;// West = 5.57291 +/- 2.14448e-05 East = 5.5722 +/- 7.68262e-05
};
