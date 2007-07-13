TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 118081
  row.laserDriftVelocityEast	 =   5.57797; // +/- 1.8198e-05 cm/us All: East = -0.631914 +/- 0.00493793
  row.laserDriftVelocityWest	 =   5.57797; // +/- 1.8198e-05 cm/us All: West = -0.613657 +/- 0.00433726
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57797 +/- 1.8198e-05
  return (TDataSet *)tableSet;// West = 5.57794 +/- 2.43249e-05 East = 5.57801 +/- 2.74247e-05
};
