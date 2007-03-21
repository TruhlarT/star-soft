TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6077035
  row.laserDriftVelocityEast	 =   5.5301; // +/- 4.46175e-05 cm/us All: East = 5.52974 +/- 6.60891e-05
  row.laserDriftVelocityWest	 =   5.5301; // +/- 4.46175e-05 cm/us All: West = 5.53041 +/- 6.04806e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.477123 +/- 0.00811429
  return (TDataSet *)tableSet;// West = 0.409066 +/- 0.0109896 East = 0.5587 +/- 0.0120317
};
