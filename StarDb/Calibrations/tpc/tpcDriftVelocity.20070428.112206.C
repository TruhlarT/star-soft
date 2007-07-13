TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 118043
  row.laserDriftVelocityEast	 =   5.57723; // +/- 1.90286e-05 cm/us All: East = -0.52052 +/- 0.00442109
  row.laserDriftVelocityWest	 =   5.57723; // +/- 1.90286e-05 cm/us All: West = -0.428703 +/- 0.0054962
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57723 +/- 1.90286e-05
  return (TDataSet *)tableSet;// West = 5.5769 +/- 3.02237e-05 East = 5.57745 +/- 2.44922e-05
};
