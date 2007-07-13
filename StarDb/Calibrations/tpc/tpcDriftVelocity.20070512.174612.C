TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 132016
  row.laserDriftVelocityEast	 =   5.5675; // +/- 2.62893e-05 cm/us All: East = 1.20893 +/- 0.00769758
  row.laserDriftVelocityWest	 =   5.5675; // +/- 2.62893e-05 cm/us All: West = 1.30508 +/- 0.00609581
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5675 +/- 2.62893e-05
  return (TDataSet *)tableSet;// West = 5.56728 +/- 3.30568e-05 East = 5.56787 +/- 4.33639e-05
};
