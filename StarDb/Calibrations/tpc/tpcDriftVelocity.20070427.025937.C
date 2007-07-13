TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 116106
  row.laserDriftVelocityEast	 =   5.57723; // +/- 1.56489e-05 cm/us All: East = -0.524587 +/- 0.00327994
  row.laserDriftVelocityWest	 =   5.57723; // +/- 1.56489e-05 cm/us All: West = -0.383043 +/- 0.00546923
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57723 +/- 1.56489e-05
  return (TDataSet *)tableSet;// West = 5.57668 +/- 3.00791e-05 East = 5.57744 +/- 1.8324e-05
};
