TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6026065
  row.laserDriftVelocityEast	 =   5.55393; // +/- 8.93283e-05 cm/us All: East = 5.55381 +/- 0.000129331
  row.laserDriftVelocityWest	 =   5.55393; // +/- 8.93283e-05 cm/us All: West = 5.55404 +/- 0.000123527
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -15.7936 +/- 0.0156392
  return (TDataSet *)tableSet;// West = -15.816 +/- 0.0216484 East = -15.7692 +/- 0.0226177
};
