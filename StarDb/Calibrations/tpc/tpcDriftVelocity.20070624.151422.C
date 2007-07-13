TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 175029
  row.laserDriftVelocityEast	 =   5.57214; // +/- 2.22316e-05 cm/us All: East = 0.57154 +/- 0.00546618
  row.laserDriftVelocityWest	 =   5.57214; // +/- 2.22316e-05 cm/us All: West = 0.276186 +/- 0.00586936
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57214 +/- 2.22316e-05
  return (TDataSet *)tableSet;// West = 5.57298 +/- 3.21566e-05 East = 5.57136 +/- 3.07697e-05
};
