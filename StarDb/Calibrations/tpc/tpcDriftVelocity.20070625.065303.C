TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176014
  row.laserDriftVelocityEast	 =   5.57148; // +/- 2.20332e-05 cm/us All: East = 0.697344 +/- 0.00554477
  row.laserDriftVelocityWest	 =   5.57148; // +/- 2.20332e-05 cm/us All: West = 0.392631 +/- 0.00558751
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57148 +/- 2.20332e-05
  return (TDataSet *)tableSet;// West = 5.57234 +/- 3.14429e-05 East = 5.57064 +/- 3.08839e-05
};
