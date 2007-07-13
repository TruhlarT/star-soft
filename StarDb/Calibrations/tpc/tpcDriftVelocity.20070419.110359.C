TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 109041
  row.laserDriftVelocityEast	 =   5.57408; // +/- 1.25524e-05 cm/us All: East = 0.257901 +/- 0.00298294
  row.laserDriftVelocityWest	 =   5.57408; // +/- 1.25524e-05 cm/us All: West = -0.163242 +/- 0.00343454
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57408 +/- 1.25524e-05
  return (TDataSet *)tableSet;// West = 5.57544 +/- 1.91994e-05 East = 5.57306 +/- 1.6589e-05
};
