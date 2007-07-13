TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169044
  row.laserDriftVelocityEast	 =   5.5705; // +/- 1.92972e-05 cm/us All: East = 0.874723 +/- 0.00442821
  row.laserDriftVelocityWest	 =   5.5705; // +/- 1.92972e-05 cm/us All: West = 0.481944 +/- 0.00557676
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5705 +/- 1.92972e-05
  return (TDataSet *)tableSet;// West = 5.57184 +/- 3.09475e-05 East = 5.56964 +/- 2.46835e-05
};
