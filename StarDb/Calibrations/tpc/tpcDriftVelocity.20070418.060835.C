TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 108005
  row.laserDriftVelocityEast	 =   5.5758; // +/- 1.56482e-05 cm/us All: East = -0.114058 +/- 0.0037388
  row.laserDriftVelocityWest	 =   5.5758; // +/- 1.56482e-05 cm/us All: West = -0.376199 +/- 0.00428563
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5758 +/- 1.56482e-05
  return (TDataSet *)tableSet;// West = 5.57664 +/- 2.38053e-05 East = 5.57517 +/- 2.07648e-05
};
