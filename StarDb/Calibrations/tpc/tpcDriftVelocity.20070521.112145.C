TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141044
  row.laserDriftVelocityEast	 =   5.57467; // +/- 2.23611e-05 cm/us All: East = 0.00956828 +/- 0.00472216
  row.laserDriftVelocityWest	 =   5.57467; // +/- 2.23611e-05 cm/us All: West = -0.0969997 +/- 0.00784048
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57467 +/- 2.23611e-05
  return (TDataSet *)tableSet;// West = 5.57511 +/- 4.28453e-05 East = 5.5745 +/- 2.62146e-05
};
