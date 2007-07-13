TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 168081
  row.laserDriftVelocityEast	 =   5.57112; // +/- 2.02081e-05 cm/us All: East = 0.788498 +/- 0.00476704
  row.laserDriftVelocityWest	 =   5.57112; // +/- 2.02081e-05 cm/us All: West = 0.381914 +/- 0.00555678
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57112 +/- 2.02081e-05
  return (TDataSet *)tableSet;// West = 5.57239 +/- 3.06343e-05 East = 5.57014 +/- 2.6888e-05
};
