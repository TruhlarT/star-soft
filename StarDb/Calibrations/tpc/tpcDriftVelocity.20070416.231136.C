TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 106088
  row.laserDriftVelocityEast	 =   5.57916; // +/- 1.83314e-05 cm/us All: East = -0.874414 +/- 0.00501246
  row.laserDriftVelocityWest	 =   5.57916; // +/- 1.83314e-05 cm/us All: West = -0.800706 +/- 0.00428415
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57916 +/- 1.83314e-05
  return (TDataSet *)tableSet;// West = 5.57899 +/- 2.41564e-05 East = 5.57938 +/- 2.8148e-05
};
