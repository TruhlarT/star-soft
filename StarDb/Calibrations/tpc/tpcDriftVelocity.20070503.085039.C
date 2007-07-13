TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 123010
  row.laserDriftVelocityEast	 =   5.5785; // +/- 2.17055e-05 cm/us All: East = -0.76132 +/- 0.00602407
  row.laserDriftVelocityWest	 =   5.5785; // +/- 2.17055e-05 cm/us All: West = -0.682195 +/- 0.00495339
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5785 +/- 2.17055e-05
  return (TDataSet *)tableSet;// West = 5.57833 +/- 2.82499e-05 East = 5.57875 +/- 3.39125e-05
};
