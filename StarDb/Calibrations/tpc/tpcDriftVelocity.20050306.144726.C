TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6065020
  row.laserDriftVelocityEast	 =   5.53568; // +/- 3.1874e-05 cm/us All: East = 5.53573 +/- 6.36368e-05
  row.laserDriftVelocityWest	 =   5.53568; // +/- 3.1874e-05 cm/us All: West = 5.53566 +/- 3.68264e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.03306 +/- 0.0057654
  return (TDataSet *)tableSet;// West = 1.03486 +/- 0.00665322 East = 1.02762 +/- 0.0115521
};
