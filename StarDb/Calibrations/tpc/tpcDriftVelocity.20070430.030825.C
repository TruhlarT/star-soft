TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119114
  row.laserDriftVelocityEast	 =   5.57816; // +/- 1.64412e-05 cm/us All: East = -0.654411 +/- 0.00346307
  row.laserDriftVelocityWest	 =   5.57816; // +/- 1.64412e-05 cm/us All: West = -0.647507 +/- 0.00559562
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57816 +/- 1.64412e-05
  return (TDataSet *)tableSet;// West = 5.57812 +/- 3.08654e-05 East = 5.57817 +/- 1.94267e-05
};
