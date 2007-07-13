TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 110027
  row.laserDriftVelocityEast	 =   5.57483; // +/- 1.86534e-05 cm/us All: East = 0.0675426 +/- 0.0060742
  row.laserDriftVelocityWest	 =   5.57483; // +/- 1.86534e-05 cm/us All: West = -0.109916 +/- 0.00401742
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57483 +/- 1.86534e-05
  return (TDataSet *)tableSet;// West = 5.57514 +/- 2.25467e-05 East = 5.57417 +/- 3.32073e-05
};
