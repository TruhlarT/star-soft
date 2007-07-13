TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 121038
  row.laserDriftVelocityEast	 =   5.57899; // +/- 1.79569e-05 cm/us All: East = -0.802191 +/- 0.00384915
  row.laserDriftVelocityWest	 =   5.57899; // +/- 1.79569e-05 cm/us All: West = -0.790806 +/- 0.0058186
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57899 +/- 1.79569e-05
  return (TDataSet *)tableSet;// West = 5.57895 +/- 3.28496e-05 East = 5.57901 +/- 2.14445e-05
};
