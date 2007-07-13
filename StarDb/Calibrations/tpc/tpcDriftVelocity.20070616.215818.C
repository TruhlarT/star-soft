TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 167048
  row.laserDriftVelocityEast	 =   5.57102; // +/- 1.97023e-05 cm/us All: East = 0.764228 +/- 0.00467354
  row.laserDriftVelocityWest	 =   5.57102; // +/- 1.97023e-05 cm/us All: West = 0.44144 +/- 0.00547254
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57102 +/- 1.97023e-05
  return (TDataSet *)tableSet;// West = 5.57205 +/- 3.03051e-05 East = 5.57026 +/- 2.59301e-05
};
