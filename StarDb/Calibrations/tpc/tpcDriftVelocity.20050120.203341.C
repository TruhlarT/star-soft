TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6020026
  row.laserDriftVelocityEast	 =   5.55259; // +/- 0.000266014 cm/us All: East = 5.55288 +/- 0.000658897
  row.laserDriftVelocityWest	 =   5.55259; // +/- 0.000266014 cm/us All: West = 5.55253 +/- 0.000290764
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.28457 +/- 0.063212
  return (TDataSet *)tableSet;// West = 1.28906 +/- 0.0687477 East = 1.26004 +/- 0.160787
};
