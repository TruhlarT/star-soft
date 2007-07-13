TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 170021
  row.laserDriftVelocityEast	 =   5.56953; // +/- 2.26598e-05 cm/us All: East = 1.04526 +/- 0.00535404
  row.laserDriftVelocityWest	 =   5.56953; // +/- 2.26598e-05 cm/us All: West = 0.687895 +/- 0.00631198
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56953 +/- 2.26598e-05
  return (TDataSet *)tableSet;// West = 5.57071 +/- 3.52057e-05 East = 5.56869 +/- 2.9608e-05
};
