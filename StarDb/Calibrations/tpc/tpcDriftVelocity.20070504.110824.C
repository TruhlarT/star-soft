TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 124026
  row.laserDriftVelocityEast	 =   5.57829; // +/- 1.54491e-05 cm/us All: East = -0.660806 +/- 0.00311596
  row.laserDriftVelocityWest	 =   5.57829; // +/- 1.54491e-05 cm/us All: West = -0.697386 +/- 0.00643204
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57829 +/- 1.54491e-05
  return (TDataSet *)tableSet;// West = 5.5784 +/- 3.62591e-05 East = 5.57826 +/- 1.70768e-05
};
