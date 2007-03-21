TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6078040
  row.laserDriftVelocityEast	 =   5.53046; // +/- 0.000105632 cm/us All: East = 5.53066 +/- 0.000171603
  row.laserDriftVelocityWest	 =   5.53046; // +/- 0.000105632 cm/us All: West = 5.53034 +/- 0.000134036
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.276541 +/- 0.0191295
  return (TDataSet *)tableSet;// West = 0.295624 +/- 0.0244891 East = 0.24667 +/- 0.0306389
};
