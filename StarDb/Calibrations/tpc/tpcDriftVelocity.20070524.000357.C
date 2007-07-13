TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 143055
  row.laserDriftVelocityEast	 =   5.57213; // +/- 2.10777e-05 cm/us All: East = -0.355023 +/- 0.142096
  row.laserDriftVelocityWest	 =   5.57213; // +/- 2.10777e-05 cm/us All: West = 0.450896 +/- 0.00387277
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57213 +/- 2.10777e-05
  return (TDataSet *)tableSet;// West = 5.57213 +/- 2.10903e-05 East = 5.57669 +/- 0.000608953
};
