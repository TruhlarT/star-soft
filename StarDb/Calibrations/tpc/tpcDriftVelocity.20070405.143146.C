TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 95088
  row.laserDriftVelocityEast	 =   5.57828; // +/- 1.40141e-05 cm/us All: East = -2.04713 +/- 0.00317899
  row.laserDriftVelocityWest	 =   5.57828; // +/- 1.40141e-05 cm/us All: West = -1.87168 +/- 0.00397532
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57828 +/- 1.40141e-05
  return (TDataSet *)tableSet;// West = 5.57767 +/- 2.26129e-05 East = 5.57866 +/- 1.78568e-05
};
