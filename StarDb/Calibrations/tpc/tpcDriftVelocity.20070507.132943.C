TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 127027
  row.laserDriftVelocityEast	 =   5.57632; // +/- 2.02388e-05 cm/us All: East = -0.340084 +/- 0.00412228
  row.laserDriftVelocityWest	 =   5.57632; // +/- 2.02388e-05 cm/us All: West = -0.249337 +/- 0.0076945
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57632 +/- 2.02388e-05
  return (TDataSet *)tableSet;// West = 5.57589 +/- 4.29294e-05 East = 5.57644 +/- 2.29491e-05
};
