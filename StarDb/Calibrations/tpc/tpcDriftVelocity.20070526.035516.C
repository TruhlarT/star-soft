TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 145097
  row.laserDriftVelocityEast	 =   5.5741; // +/- 1.84693e-05 cm/us All: East = 0.401541 +/- 6.16971
  row.laserDriftVelocityWest	 =   5.5741; // +/- 1.84693e-05 cm/us All: West = 0.0751185 +/- 0.00330819
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5741 +/- 1.84693e-05
  return (TDataSet *)tableSet;// West = 5.5741 +/- 1.84694e-05 East = 5.57678 +/- 0.00925104
};
