TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 107028
  row.laserDriftVelocityEast	 =   5.57766; // +/- 1.83537e-05 cm/us All: East = -0.624371 +/- 0.00436068
  row.laserDriftVelocityWest	 =   5.57766; // +/- 1.83537e-05 cm/us All: West = -0.461888 +/- 0.00496617
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57766 +/- 1.83537e-05
  return (TDataSet *)tableSet;// West = 5.57711 +/- 2.79721e-05 East = 5.57807 +/- 2.43213e-05
};
