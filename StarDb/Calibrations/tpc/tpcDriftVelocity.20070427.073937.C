TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 117020
  row.laserDriftVelocityEast	 =   5.57713; // +/- 1.87174e-05 cm/us All: East = -0.471714 +/- 0.00476261
  row.laserDriftVelocityWest	 =   5.57713; // +/- 1.87174e-05 cm/us All: West = -0.466227 +/- 0.00469684
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57713 +/- 1.87174e-05
  return (TDataSet *)tableSet;// West = 5.57713 +/- 2.63936e-05 East = 5.57714 +/- 2.65479e-05
};
