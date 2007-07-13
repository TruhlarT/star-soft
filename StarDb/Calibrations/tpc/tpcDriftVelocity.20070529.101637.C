TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 149029
  row.laserDriftVelocityEast	 =   5.57301; // +/- 2.07784e-05 cm/us All: East = 0.285497 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57301; // +/- 2.07784e-05 cm/us All: West = 0.266929 +/- 0.00373343
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57301 +/- 2.07784e-05
  return (TDataSet *)tableSet;// West = 5.57301 +/- 2.07784e-05 East = 4.45805 +/- 1.41421
};
