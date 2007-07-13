TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 106107
  row.laserDriftVelocityEast	 =   5.57895; // +/- 1.48719e-05 cm/us All: East = -0.831917 +/- 0.00333528
  row.laserDriftVelocityWest	 =   5.57895; // +/- 1.48719e-05 cm/us All: West = -0.727448 +/- 0.00436619
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57895 +/- 1.48719e-05
  return (TDataSet *)tableSet;// West = 5.57858 +/- 2.49441e-05 East = 5.57915 +/- 1.85244e-05
};
