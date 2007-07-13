TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135022
  row.laserDriftVelocityEast	 =   5.57441; // +/- 2.06996e-05 cm/us All: East = 0.0486696 +/- 0.00486501
  row.laserDriftVelocityWest	 =   5.57441; // +/- 2.06996e-05 cm/us All: West = -0.0204165 +/- 0.00581695
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57441 +/- 2.06996e-05
  return (TDataSet *)tableSet;// West = 5.57461 +/- 3.27034e-05 East = 5.57428 +/- 2.6737e-05
};
