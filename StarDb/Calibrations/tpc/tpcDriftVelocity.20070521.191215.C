TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141066
  row.laserDriftVelocityEast	 =   5.57448; // +/- 1.97317e-05 cm/us All: East = 0.058107 +/- 0.00409434
  row.laserDriftVelocityWest	 =   5.57448; // +/- 1.97317e-05 cm/us All: West = -0.124736 +/- 0.00700464
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57448 +/- 1.97317e-05
  return (TDataSet *)tableSet;// West = 5.57523 +/- 3.91401e-05 East = 5.57423 +/- 2.28475e-05
};
