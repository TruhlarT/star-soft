TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6015033
  row.laserDriftVelocityEast	 =   5.53198; // +/- 5.27412e-05 cm/us All: East = 5.53206 +/- 9.75123e-05
  row.laserDriftVelocityWest	 =   5.53198; // +/- 5.27412e-05 cm/us All: West = 5.53194 +/- 6.27044e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.580605 +/- 0.00957779
  return (TDataSet *)tableSet;// West = 0.589787 +/- 0.0112998 East = 0.557177 +/- 0.0180499
};
