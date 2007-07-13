TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 170074
  row.laserDriftVelocityEast	 =   5.56985; // +/- 1.72997e-05 cm/us All: East = 0.961868 +/- 0.00388905
  row.laserDriftVelocityWest	 =   5.56985; // +/- 1.72997e-05 cm/us All: West = 0.615181 +/- 0.00518211
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56985 +/- 1.72997e-05
  return (TDataSet *)tableSet;// West = 5.57109 +/- 2.88822e-05 East = 5.56915 +/- 2.1604e-05
};
