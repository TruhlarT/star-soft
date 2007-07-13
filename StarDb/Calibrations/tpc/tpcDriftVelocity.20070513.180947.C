TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 133044
  row.laserDriftVelocityEast	 =   5.571; // +/- 2.30262e-05 cm/us All: East = 0.504166 +/- 0.00565248
  row.laserDriftVelocityWest	 =   5.571; // +/- 2.30262e-05 cm/us All: West = 0.756225 +/- 0.00589372
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.571 +/- 2.30262e-05
  return (TDataSet *)tableSet;// West = 5.57031 +/- 3.33115e-05 East = 5.57163 +/- 3.18646e-05
};
