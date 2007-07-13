TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 151058
  row.laserDriftVelocityEast	 =   5.57291; // +/- 2.11704e-05 cm/us All: East = 0.0335517 +/- 0.282983
  row.laserDriftVelocityWest	 =   5.57291; // +/- 2.11704e-05 cm/us All: West = 0.297488 +/- 0.00382017
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57291 +/- 2.11704e-05
  return (TDataSet *)tableSet;// West = 5.57291 +/- 2.11716e-05 East = 5.57418 +/- 0.00202434
};
