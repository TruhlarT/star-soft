TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126017
  row.laserDriftVelocityEast	 =   5.57788; // +/- 2.60603e-05 cm/us All: East = -0.496799 +/- 0.00584053
  row.laserDriftVelocityWest	 =   5.57788; // +/- 2.60603e-05 cm/us All: West = -0.790598 +/- 0.00772359
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57788 +/- 2.60603e-05
  return (TDataSet *)tableSet;// West = 5.57891 +/- 4.37784e-05 East = 5.57732 +/- 3.24326e-05
};
