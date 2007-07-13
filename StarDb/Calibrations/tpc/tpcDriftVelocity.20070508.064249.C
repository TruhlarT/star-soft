TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 128009
  row.laserDriftVelocityEast	 =   5.57614; // +/- 3.67017e-05 cm/us All: East = -0.230465 +/- 0.0220038
  row.laserDriftVelocityWest	 =   5.57614; // +/- 3.67017e-05 cm/us All: West = -0.303087 +/- 0.00674214
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57614 +/- 3.67017e-05
  return (TDataSet *)tableSet;// West = 5.57618 +/- 3.84277e-05 East = 5.57571 +/- 0.000123854
};
