TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 100027
  row.laserDriftVelocityEast	 =   5.57299; // +/- 1.79919e-05 cm/us All: East = 0.752637 +/- 0.00443229
  row.laserDriftVelocityWest	 =   5.57299; // +/- 1.79919e-05 cm/us All: West = 0.718165 +/- 0.00471633
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57299 +/- 1.79919e-05
  return (TDataSet *)tableSet;// West = 5.5731 +/- 2.62151e-05 East = 5.57288 +/- 2.4738e-05
};
