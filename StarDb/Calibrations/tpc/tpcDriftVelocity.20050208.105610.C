TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6039030
  row.laserDriftVelocityEast	 =   5.53217; // +/- 3.57315e-05 cm/us All: East = 5.53193 +/- 8.37546e-05
  row.laserDriftVelocityWest	 =   5.53217; // +/- 3.57315e-05 cm/us All: West = 5.53222 +/- 3.95072e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.54893 +/- 0.00888814
  return (TDataSet *)tableSet;// West = 2.53394 +/- 0.0101659 East = 2.59758 +/- 0.0183122
};
