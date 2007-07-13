TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 162063
  row.laserDriftVelocityEast	 =   5.57403; // +/- 4.03381e-05 cm/us All: East = 0.690309 +/- 2.48656
  row.laserDriftVelocityWest	 =   5.57403; // +/- 4.03381e-05 cm/us All: West = 0.0881245 +/- 0.00723555
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57403 +/- 4.03381e-05
  return (TDataSet *)tableSet;// West = 5.57403 +/- 4.03384e-05 East = 5.57046 +/- 0.00975273
};
