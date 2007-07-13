TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138095
  row.laserDriftVelocityEast	 =   5.57443; // +/- 3.11267e-05 cm/us All: East = 0.0966839 +/- 0.0205705
  row.laserDriftVelocityWest	 =   5.57443; // +/- 3.11267e-05 cm/us All: West = 0.0243364 +/- 0.00563531
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57443 +/- 3.11267e-05
  return (TDataSet *)tableSet;// West = 5.57446 +/- 3.23974e-05 East = 5.57401 +/- 0.000112242
};
