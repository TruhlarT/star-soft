TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6041094
  row.laserDriftVelocityEast	 =   5.52832; // +/- 0.000156633 cm/us All: East = 5.5287 +/- 0.000498976
  row.laserDriftVelocityWest	 =   5.52832; // +/- 0.000156633 cm/us All: West = 5.52828 +/- 0.000164972
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.08933 +/- 0.0307897
  return (TDataSet *)tableSet;// West = 2.09904 +/- 0.0328809 East = 2.02015 +/- 0.0877367
};
