TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169003
  row.laserDriftVelocityEast	 =   5.57097; // +/- 2.21016e-05 cm/us All: East = 0.768197 +/- 0.00481064
  row.laserDriftVelocityWest	 =   5.57097; // +/- 2.21016e-05 cm/us All: West = 0.379498 +/- 0.00691279
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57097 +/- 2.21016e-05
  return (TDataSet *)tableSet;// West = 5.57244 +/- 3.88349e-05 East = 5.57026 +/- 2.68792e-05
};
