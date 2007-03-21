TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6012002
  row.laserDriftVelocityEast	 =   5.51569; // +/- 5.22382e-05 cm/us All: East = 5.5159 +/- 8.55625e-05
  row.laserDriftVelocityWest	 =   5.51569; // +/- 5.22382e-05 cm/us All: West = 5.51557 +/- 6.59577e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.246561 +/- 0.00521407
  return (TDataSet *)tableSet;// West = 0.260937 +/- 0.00652416 East = 0.221147 +/- 0.00867458
};
