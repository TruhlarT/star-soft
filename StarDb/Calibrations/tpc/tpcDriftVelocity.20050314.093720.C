TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6073011
  row.laserDriftVelocityEast	 =   5.53181; // +/- 4.94139e-05 cm/us All: East = 5.53175 +/- 7.87914e-05
  row.laserDriftVelocityWest	 =   5.53181; // +/- 4.94139e-05 cm/us All: West = 5.53185 +/- 6.34406e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.584984 +/- 0.00905236
  return (TDataSet *)tableSet;// West = 0.573873 +/- 0.0117242 East = 0.601387 +/- 0.0142447
};
