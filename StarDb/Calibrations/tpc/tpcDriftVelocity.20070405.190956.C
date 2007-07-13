TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 95139
  row.laserDriftVelocityEast	 =   5.57806; // +/- 1.50924e-05 cm/us All: East = -2.01648 +/- 0.00362801
  row.laserDriftVelocityWest	 =   5.57806; // +/- 1.50924e-05 cm/us All: West = -1.84861 +/- 0.00406834
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57806 +/- 1.50924e-05
  return (TDataSet *)tableSet;// West = 5.57754 +/- 2.27635e-05 East = 5.57846 +/- 2.01607e-05
};
