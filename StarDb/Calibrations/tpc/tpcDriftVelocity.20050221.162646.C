TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6052060
  row.laserDriftVelocityEast	 =   5.53456; // +/- 0.000114613 cm/us All: East = 5.5342 +/- 0.000220376
  row.laserDriftVelocityWest	 =   5.53456; // +/- 0.000114613 cm/us All: West = 5.53469 +/- 0.000134188
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.18141 +/- 0.020551
  return (TDataSet *)tableSet;// West = 1.11813 +/- 0.0240915 East = 1.35049 +/- 0.0393809
};
