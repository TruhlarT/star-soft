TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 177004
  row.laserDriftVelocityEast	 =   5.57088; // +/- 3.13982e-05 cm/us All: East = 0.675324 +/- 0.0109506
  row.laserDriftVelocityWest	 =   5.57088; // +/- 3.13982e-05 cm/us All: West = 0.645151 +/- 0.00655435
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57088 +/- 3.13982e-05
  return (TDataSet *)tableSet;// West = 5.57093 +/- 3.67152e-05 East = 5.57077 +/- 6.05758e-05
};
