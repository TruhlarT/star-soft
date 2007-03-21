TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6036099
  row.laserDriftVelocityEast	 =   5.53647; // +/- 0.000134838 cm/us All: East = 5.53685 +/- 0.00037448
  row.laserDriftVelocityWest	 =   5.53647; // +/- 0.000134838 cm/us All: West = 5.53642 +/- 0.000144532
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.41152 +/- 0.0255291
  return (TDataSet *)tableSet;// West = 2.42277 +/- 0.0266656 East = 2.28788 +/- 0.0883893
};
