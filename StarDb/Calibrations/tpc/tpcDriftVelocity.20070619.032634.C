TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169132
  row.laserDriftVelocityEast	 =   5.57018; // +/- 3.04985e-05 cm/us All: East = 1.05587 +/- 0.00756774
  row.laserDriftVelocityWest	 =   5.57018; // +/- 3.04985e-05 cm/us All: West = 0.508965 +/- 0.00800295
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57018 +/- 3.04985e-05
  return (TDataSet *)tableSet;// West = 5.57164 +/- 4.29267e-05 East = 5.5687 +/- 4.3339e-05
};
