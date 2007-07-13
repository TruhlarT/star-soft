TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 175050
  row.laserDriftVelocityEast	 =   5.57227; // +/- 2.44557e-05 cm/us All: East = 0.541395 +/- 0.00660858
  row.laserDriftVelocityWest	 =   5.57227; // +/- 2.44557e-05 cm/us All: West = 0.292996 +/- 0.00586651
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57227 +/- 2.44557e-05
  return (TDataSet *)tableSet;// West = 5.57288 +/- 3.2981e-05 East = 5.57152 +/- 3.64496e-05
};
