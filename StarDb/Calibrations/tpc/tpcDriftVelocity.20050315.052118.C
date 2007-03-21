TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6074001
  row.laserDriftVelocityEast	 =   5.53001; // +/- 4.59273e-05 cm/us All: East = 5.53027 +/- 7.28443e-05
  row.laserDriftVelocityWest	 =   5.53001; // +/- 4.59273e-05 cm/us All: West = 5.52985 +/- 5.91695e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.501272 +/- 0.00812336
  return (TDataSet *)tableSet;// West = 0.52927 +/- 0.0106169 East = 0.461734 +/- 0.0126165
};
