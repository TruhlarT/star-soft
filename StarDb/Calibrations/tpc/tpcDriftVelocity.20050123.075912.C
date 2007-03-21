TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6023010
  row.laserDriftVelocityEast	 =   5.55453; // +/- 3.22398e-05 cm/us All: East = 5.55484 +/- 5.94851e-05
  row.laserDriftVelocityWest	 =   5.55453; // +/- 3.22398e-05 cm/us All: West = 5.5544 +/- 3.83628e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.74096 +/- 0.00583365
  return (TDataSet *)tableSet;// West = 1.76462 +/- 0.00692385 East = 1.68308 +/- 0.0108306
};
