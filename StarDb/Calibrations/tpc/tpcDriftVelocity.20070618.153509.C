TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169052
  row.laserDriftVelocityEast	 =   5.57091; // +/- 2.12245e-05 cm/us All: East = 0.838644 +/- 0.00533148
  row.laserDriftVelocityWest	 =   5.57091; // +/- 2.12245e-05 cm/us All: West = 0.460664 +/- 0.00538094
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57091 +/- 2.12245e-05
  return (TDataSet *)tableSet;// West = 5.57196 +/- 3.01473e-05 East = 5.56987 +/- 2.98865e-05
};
