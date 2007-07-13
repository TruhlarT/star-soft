TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 84129
  row.laserDriftVelocityEast	 =   5.56367; // +/- 3.40315e-05 cm/us All: East = 0.670716 +/- 0.00693948
  row.laserDriftVelocityWest	 =   5.56367; // +/- 3.40315e-05 cm/us All: West = 0.572826 +/- 0.0129209
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56367 +/- 3.40315e-05
  return (TDataSet *)tableSet;// West = 5.5641 +/- 7.07779e-05 East = 5.56354 +/- 3.88125e-05
};
