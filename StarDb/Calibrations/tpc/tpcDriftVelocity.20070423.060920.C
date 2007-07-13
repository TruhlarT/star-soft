TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 113008
  row.laserDriftVelocityEast	 =   5.5766; // +/- 2.23303e-05 cm/us All: East = -0.428548 +/- 0.00569476
  row.laserDriftVelocityWest	 =   5.5766; // +/- 2.23303e-05 cm/us All: West = -0.303871 +/- 0.00559279
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5766 +/- 2.23303e-05
  return (TDataSet *)tableSet;// West = 5.57623 +/- 3.11939e-05 East = 5.57699 +/- 3.19805e-05
};
