TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6026080
  row.laserDriftVelocityEast	 =   5.55416; // +/- 9.45154e-05 cm/us All: East = 5.55509 +/- 0.000190269
  row.laserDriftVelocityWest	 =   5.55416; // +/- 9.45154e-05 cm/us All: West = 5.55386 +/- 0.000108902
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.1492 +/- 0.0170413
  return (TDataSet *)tableSet;// West = 2.20312 +/- 0.0199075 East = 2.00134 +/- 0.0329659
};
