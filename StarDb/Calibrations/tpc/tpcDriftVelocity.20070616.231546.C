TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 167053
  row.laserDriftVelocityEast	 =   5.57111; // +/- 2.5917e-05 cm/us All: East = 0.774315 +/- 0.00570124
  row.laserDriftVelocityWest	 =   5.57111; // +/- 2.5917e-05 cm/us All: West = 0.240597 +/- 0.00863745
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57111 +/- 2.5917e-05
  return (TDataSet *)tableSet;// West = 5.5732 +/- 4.68782e-05 East = 5.57018 +/- 3.11026e-05
};
