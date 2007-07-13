TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139050
  row.laserDriftVelocityEast	 =   5.5748; // +/- 2.75994e-05 cm/us All: East = -0.0926261 +/- 0.00717606
  row.laserDriftVelocityWest	 =   5.5748; // +/- 2.75994e-05 cm/us All: West = -0.0128937 +/- 0.00687718
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5748 +/- 2.75994e-05
  return (TDataSet *)tableSet;// West = 5.57461 +/- 3.82768e-05 East = 5.57501 +/- 3.98326e-05
};
