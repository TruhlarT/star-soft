TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6040046
  row.laserDriftVelocityEast	 =   5.53055; // +/- 9.76285e-05 cm/us All: East = 5.52932 +/- 0.000252342
  row.laserDriftVelocityWest	 =   5.53055; // +/- 9.76285e-05 cm/us All: West = 5.53076 +/- 0.000105873
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.47692 +/- 0.0280379
  return (TDataSet *)tableSet;// West = 1.41957 +/- 0.0314085 East = 1.70191 +/- 0.0622125
};
