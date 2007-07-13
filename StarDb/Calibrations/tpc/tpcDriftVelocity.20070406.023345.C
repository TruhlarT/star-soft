TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 95225
  row.laserDriftVelocityEast	 =   5.57681; // +/- 1.50928e-05 cm/us All: East = -1.67526 +/- 0.00324243
  row.laserDriftVelocityWest	 =   5.57681; // +/- 1.50928e-05 cm/us All: West = -1.80155 +/- 0.00483345
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57681 +/- 1.50928e-05
  return (TDataSet *)tableSet;// West = 5.57727 +/- 2.70078e-05 East = 5.57659 +/- 1.81998e-05
};
