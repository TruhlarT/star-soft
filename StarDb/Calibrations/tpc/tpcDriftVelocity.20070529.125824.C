TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 149039
  row.laserDriftVelocityEast	 =   5.57323; // +/- 2.18608e-05 cm/us All: East = 0 +/- 0
  row.laserDriftVelocityWest	 =   5.57323; // +/- 2.18608e-05 cm/us All: West = 0.232787 +/- 0.00395493
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57323 +/- 2.18608e-05
  return (TDataSet *)tableSet;// West = 5.57323 +/- 2.18608e-05 East = 0 +/- 0
};
