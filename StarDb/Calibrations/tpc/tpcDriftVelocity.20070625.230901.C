TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176082
  row.laserDriftVelocityEast	 =   5.57096; // +/- 2.37054e-05 cm/us All: East = 0.784828 +/- 0.00621283
  row.laserDriftVelocityWest	 =   5.57096; // +/- 2.37054e-05 cm/us All: West = 0.520085 +/- 0.00576242
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57096 +/- 2.37054e-05
  return (TDataSet *)tableSet;// West = 5.57164 +/- 3.20119e-05 East = 5.57014 +/- 3.5274e-05
};
