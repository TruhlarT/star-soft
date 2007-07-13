TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 116035
  row.laserDriftVelocityEast	 =   5.57656; // +/- 1.87007e-05 cm/us All: East = -0.328312 +/- 0.00481403
  row.laserDriftVelocityWest	 =   5.57656; // +/- 1.87007e-05 cm/us All: West = -0.401818 +/- 0.00468683
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57656 +/- 1.87007e-05
  return (TDataSet *)tableSet;// West = 5.57677 +/- 2.61516e-05 East = 5.57635 +/- 2.67522e-05
};
