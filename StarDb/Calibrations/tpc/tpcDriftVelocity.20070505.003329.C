TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 124097
  row.laserDriftVelocityEast	 =   5.57864; // +/- 1.90333e-05 cm/us All: East = -0.709403 +/- 0.00410114
  row.laserDriftVelocityWest	 =   5.57864; // +/- 1.90333e-05 cm/us All: West = -0.796415 +/- 0.00619247
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57864 +/- 1.90333e-05
  return (TDataSet *)tableSet;// West = 5.57898 +/- 3.44268e-05 East = 5.57849 +/- 2.28417e-05
};
