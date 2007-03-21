TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6076026
  row.laserDriftVelocityEast	 =   5.52962; // +/- 8.71715e-05 cm/us All: East = 5.5298 +/- 0.000120121
  row.laserDriftVelocityWest	 =   5.52962; // +/- 8.71715e-05 cm/us All: West = 5.52943 +/- 0.000126701
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.404078 +/- 0.0158506
  return (TDataSet *)tableSet;// West = 0.441879 +/- 0.0229654 East = 0.369688 +/- 0.0219045
};
