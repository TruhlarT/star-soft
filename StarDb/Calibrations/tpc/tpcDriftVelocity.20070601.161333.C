TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 152023
  row.laserDriftVelocityEast	 =   5.57303; // +/- 2.4695e-05 cm/us All: East = 0.0932994 +/- 19.6068
  row.laserDriftVelocityWest	 =   5.57303; // +/- 2.4695e-05 cm/us All: West = 0.274083 +/- 0.00440858
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57303 +/- 2.4695e-05
  return (TDataSet *)tableSet;// West = 5.57303 +/- 2.4695e-05 East = 5.57405 +/- 0.108818
};
