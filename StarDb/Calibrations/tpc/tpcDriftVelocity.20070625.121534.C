TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176038
  row.laserDriftVelocityEast	 =   5.57145; // +/- 2.19675e-05 cm/us All: East = 0.717659 +/- 0.00580258
  row.laserDriftVelocityWest	 =   5.57145; // +/- 2.19675e-05 cm/us All: West = 0.408398 +/- 0.0053523
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57145 +/- 2.19675e-05
  return (TDataSet *)tableSet;// West = 5.57225 +/- 2.98134e-05 East = 5.57049 +/- 3.24928e-05
};
