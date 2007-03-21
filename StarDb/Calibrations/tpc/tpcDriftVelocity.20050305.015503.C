TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6063050
  row.laserDriftVelocityEast	 =   5.53586; // +/- 5.05547e-05 cm/us All: East = 5.53616 +/- 8.92222e-05
  row.laserDriftVelocityWest	 =   5.53586; // +/- 5.05547e-05 cm/us All: West = 5.53571 +/- 6.13541e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.981379 +/- 0.00931758
  return (TDataSet *)tableSet;// West = 1.00842 +/- 0.0112841 East = 0.923425 +/- 0.0165183
};
