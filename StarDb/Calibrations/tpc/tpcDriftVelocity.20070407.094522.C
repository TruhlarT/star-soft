TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 97035
  row.laserDriftVelocityEast	 =   5.57617; // +/- 1.59431e-05 cm/us All: East = -1.79631 +/- 0.00429424
  row.laserDriftVelocityWest	 =   5.57617; // +/- 1.59431e-05 cm/us All: West = -1.44603 +/- 0.00383563
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57617 +/- 1.59431e-05
  return (TDataSet *)tableSet;// West = 5.5753 +/- 2.13826e-05 East = 5.57725 +/- 2.39248e-05
};
