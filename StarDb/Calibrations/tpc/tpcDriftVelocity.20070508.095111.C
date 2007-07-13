TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 128024
  row.laserDriftVelocityEast	 =   5.57616; // +/- 3.36311e-05 cm/us All: East = -0.815091 +/- 0.0334037
  row.laserDriftVelocityWest	 =   5.57616; // +/- 3.36311e-05 cm/us All: West = -0.272429 +/- 0.00604478
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57616 +/- 3.36311e-05
  return (TDataSet *)tableSet;// West = 5.57607 +/- 3.41766e-05 East = 5.57898 +/- 0.000188988
};
