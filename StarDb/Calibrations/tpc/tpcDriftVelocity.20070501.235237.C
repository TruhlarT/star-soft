TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 121105
  row.laserDriftVelocityEast	 =   5.57945; // +/- 1.79886e-05 cm/us All: East = -0.87659 +/- 0.00438884
  row.laserDriftVelocityWest	 =   5.57945; // +/- 1.79886e-05 cm/us All: West = -0.878944 +/- 0.00486628
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57945 +/- 1.79886e-05
  return (TDataSet *)tableSet;// West = 5.57944 +/- 2.67211e-05 East = 5.57945 +/- 2.43267e-05
};
