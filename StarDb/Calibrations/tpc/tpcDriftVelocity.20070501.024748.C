TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 120122
  row.laserDriftVelocityEast	 =   5.57904; // +/- 2.40814e-05 cm/us All: East = -0.891445 +/- 0.00841682
  row.laserDriftVelocityWest	 =   5.57904; // +/- 2.40814e-05 cm/us All: West = -0.784028 +/- 0.0048938
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57904 +/- 2.40814e-05
  return (TDataSet *)tableSet;// West = 5.5789 +/- 2.79465e-05 East = 5.57945 +/- 4.74579e-05
};
