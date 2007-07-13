TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 114079
  row.laserDriftVelocityEast	 =   5.57742; // +/- 1.57124e-05 cm/us All: East = -0.519536 +/- 0.00336129
  row.laserDriftVelocityWest	 =   5.57742; // +/- 1.57124e-05 cm/us All: West = -0.522726 +/- 0.00505785
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57742 +/- 1.57124e-05
  return (TDataSet *)tableSet;// West = 5.57743 +/- 2.84143e-05 East = 5.57742 +/- 1.8858e-05
};
