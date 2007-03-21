TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6057089
  row.laserDriftVelocityEast	 =   5.53715; // +/- 9.52246e-05 cm/us All: East = 5.53922 +/- 0.000192877
  row.laserDriftVelocityWest	 =   5.53715; // +/- 9.52246e-05 cm/us All: West = 5.53648 +/- 0.0001095
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.0868 +/- 0.01718
  return (TDataSet *)tableSet;// West = 1.22308 +/- 0.0199566 East = 0.696714 +/- 0.0337636
};
