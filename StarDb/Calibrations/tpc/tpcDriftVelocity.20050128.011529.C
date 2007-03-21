TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6027068
  row.laserDriftVelocityEast	 =   5.55317; // +/- 7.12659e-05 cm/us All: East = 5.55372 +/- 0.000166039
  row.laserDriftVelocityWest	 =   5.55317; // +/- 7.12659e-05 cm/us All: West = 5.55304 +/- 7.89035e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.73517 +/- 0.0128107
  return (TDataSet *)tableSet;// West = 2.75992 +/- 0.0141769 East = 2.62502 +/- 0.0299109
};
