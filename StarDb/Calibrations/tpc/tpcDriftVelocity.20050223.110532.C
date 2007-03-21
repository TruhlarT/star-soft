TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6054033
  row.laserDriftVelocityEast	 =   5.53299; // +/- 7.9044e-05 cm/us All: East = 5.53522 +/- 0.000176852
  row.laserDriftVelocityWest	 =   5.53299; // +/- 7.9044e-05 cm/us All: West = 5.53243 +/- 8.83608e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.36791 +/- 0.0142914
  return (TDataSet *)tableSet;// West = 1.46782 +/- 0.0159334 East = 0.956754 +/- 0.0323234
};
