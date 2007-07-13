TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 121092
  row.laserDriftVelocityEast	 =   5.57899; // +/- 2.32841e-05 cm/us All: East = -0.7313 +/- 0.00673181
  row.laserDriftVelocityWest	 =   5.57899; // +/- 2.32841e-05 cm/us All: West = -0.842175 +/- 0.00519668
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57899 +/- 2.32841e-05
  return (TDataSet *)tableSet;// West = 5.57922 +/- 2.96231e-05 East = 5.57862 +/- 3.76635e-05
};
