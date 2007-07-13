TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 159047
  row.laserDriftVelocityEast	 =   5.5743; // +/- 3.4293e-05 cm/us All: East = 0.135262 +/- 0.0561207
  row.laserDriftVelocityWest	 =   5.5743; // +/- 3.4293e-05 cm/us All: West = 0.0407858 +/- 0.00617953
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5743 +/- 3.4293e-05
  return (TDataSet *)tableSet;// West = 5.57431 +/- 3.45337e-05 East = 5.57391 +/- 0.000290974
};
