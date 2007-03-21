TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6029020
  row.laserDriftVelocityEast	 =   5.55685; // +/- 7.24972e-05 cm/us All: East = 5.55583 +/- 0.000523555
  row.laserDriftVelocityWest	 =   5.55685; // +/- 7.24972e-05 cm/us All: West = 5.55687 +/- 7.32024e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.19962 +/- 0.0130361
  return (TDataSet *)tableSet;// West = 2.19594 +/- 0.0131442 East = 2.42064 +/- 0.10188
};
