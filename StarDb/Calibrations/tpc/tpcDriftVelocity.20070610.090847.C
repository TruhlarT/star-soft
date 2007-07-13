TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 161025
  row.laserDriftVelocityEast	 =   5.57292; // +/- 2.45699e-05 cm/us All: East = 0.437603 +/- 0.031838
  row.laserDriftVelocityWest	 =   5.57292; // +/- 2.45699e-05 cm/us All: West = 0.284576 +/- 0.00446389
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57292 +/- 2.45699e-05
  return (TDataSet *)tableSet;// West = 5.57293 +/- 2.48878e-05 East = 5.57227 +/- 0.000154207
};
