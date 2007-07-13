TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 120037
  row.laserDriftVelocityEast	 =   5.57913; // +/- 1.57279e-05 cm/us All: East = -0.857893 +/- 0.00318985
  row.laserDriftVelocityWest	 =   5.57913; // +/- 1.57279e-05 cm/us All: West = -0.697591 +/- 0.00628671
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57913 +/- 1.57279e-05
  return (TDataSet *)tableSet;// West = 5.57842 +/- 3.45461e-05 East = 5.57932 +/- 1.76648e-05
};
