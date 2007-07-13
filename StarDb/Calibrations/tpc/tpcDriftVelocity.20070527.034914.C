TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 146094
  row.laserDriftVelocityEast	 =   5.57373; // +/- 1.68729e-05 cm/us All: East = 0.161971 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57373; // +/- 1.68729e-05 cm/us All: West = 0.142454 +/- 0.00304405
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57373 +/- 1.68729e-05
  return (TDataSet *)tableSet;// West = 5.57373 +/- 1.68729e-05 East = 4.4587 +/- 1.41421
};
