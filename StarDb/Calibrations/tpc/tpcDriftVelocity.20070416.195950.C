TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 106073
  row.laserDriftVelocityEast	 =   5.57933; // +/- 1.34389e-05 cm/us All: East = -0.88297 +/- 0.00304129
  row.laserDriftVelocityWest	 =   5.57933; // +/- 1.34389e-05 cm/us All: West = -0.817932 +/- 0.00390298
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57933 +/- 1.34389e-05
  return (TDataSet *)tableSet;// West = 5.5791 +/- 2.20061e-05 East = 5.57946 +/- 1.69711e-05
};
