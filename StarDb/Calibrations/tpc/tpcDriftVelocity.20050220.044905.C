TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6050133
  row.laserDriftVelocityEast	 =   5.5351; // +/- 0.000111183 cm/us All: East = 5.53536 +/- 0.000243256
  row.laserDriftVelocityWest	 =   5.5351; // +/- 0.000111183 cm/us All: West = 5.53503 +/- 0.000125004
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.722979 +/- 0.0195624
  return (TDataSet *)tableSet;// West = 0.735587 +/- 0.0218899 East = 0.672968 +/- 0.043596
};
