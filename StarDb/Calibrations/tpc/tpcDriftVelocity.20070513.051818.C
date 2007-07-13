TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 133010
  row.laserDriftVelocityEast	 =   5.56955; // +/- 2.33235e-05 cm/us All: East = 0.861455 +/- 0.00489201
  row.laserDriftVelocityWest	 =   5.56955; // +/- 2.33235e-05 cm/us All: West = 0.918763 +/- 0.0081441
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56955 +/- 2.33235e-05
  return (TDataSet *)tableSet;// West = 5.5694 +/- 4.37465e-05 East = 5.56961 +/- 2.75686e-05
};
