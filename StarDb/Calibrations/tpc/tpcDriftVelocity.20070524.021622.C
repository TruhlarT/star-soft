TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 143060
  row.laserDriftVelocityEast	 =   5.57253; // +/- 1.79878e-05 cm/us All: East = -0.149102 +/- 0.0872764
  row.laserDriftVelocityWest	 =   5.57253; // +/- 1.79878e-05 cm/us All: West = 0.361933 +/- 0.0032252
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57253 +/- 1.79878e-05
  return (TDataSet *)tableSet;// West = 5.57253 +/- 1.79981e-05 East = 5.5749 +/- 0.000530956
};
