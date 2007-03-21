TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6017010
  row.laserDriftVelocityEast	 =   5.54057; // +/- 9.75336e-05 cm/us All: East = 5.54129 +/- 0.000173991
  row.laserDriftVelocityWest	 =   5.54057; // +/- 9.75336e-05 cm/us All: West = 5.54024 +/- 0.000117779
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.550739 +/- 0.017351
  return (TDataSet *)tableSet;// West = 0.603916 +/- 0.0208579 East = 0.431259 +/- 0.0312646
};
