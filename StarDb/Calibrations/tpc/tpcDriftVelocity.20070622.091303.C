TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 173019
  row.laserDriftVelocityEast	 =   5.57107; // +/- 2.07347e-05 cm/us All: East = 0.79624 +/- 0.00521741
  row.laserDriftVelocityWest	 =   5.57107; // +/- 2.07347e-05 cm/us All: West = 0.439151 +/- 0.00530459
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57107 +/- 2.07347e-05
  return (TDataSet *)tableSet;// West = 5.57208 +/- 2.95934e-05 East = 5.5701 +/- 2.90605e-05
};
