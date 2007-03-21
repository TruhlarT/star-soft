TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6027019
  row.laserDriftVelocityEast	 =   5.55268; // +/- 4.67517e-05 cm/us All: East = 5.55254 +/- 0.00013575
  row.laserDriftVelocityWest	 =   5.55268; // +/- 4.67517e-05 cm/us All: West = 5.5527 +/- 4.97981e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.68633 +/- 0.00861095
  return (TDataSet *)tableSet;// West = 2.68884 +/- 0.00919864 East = 2.6685 +/- 0.0244835
};
