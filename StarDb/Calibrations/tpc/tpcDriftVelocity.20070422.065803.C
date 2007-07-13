TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112009
  row.laserDriftVelocityEast	 =   5.57597; // +/- 4.50741e-05 cm/us All: East = -0.369115 +/- 0.0132273
  row.laserDriftVelocityWest	 =   5.57597; // +/- 4.50741e-05 cm/us All: West = -0.197731 +/- 0.00998681
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57597 +/- 4.50741e-05
  return (TDataSet *)tableSet;// West = 5.57563 +/- 5.63043e-05 East = 5.57658 +/- 7.52146e-05
};
