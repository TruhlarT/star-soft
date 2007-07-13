TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 168101
  row.laserDriftVelocityEast	 =   5.57116; // +/- 2.23009e-05 cm/us All: East = 0.768646 +/- 0.00529428
  row.laserDriftVelocityWest	 =   5.57116; // +/- 2.23009e-05 cm/us All: West = 0.393838 +/- 0.00610199
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57116 +/- 2.23009e-05
  return (TDataSet *)tableSet;// West = 5.57233 +/- 3.37482e-05 East = 5.57025 +/- 2.97124e-05
};
