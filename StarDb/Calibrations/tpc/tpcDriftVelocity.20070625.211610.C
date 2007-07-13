TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176076
  row.laserDriftVelocityEast	 =   5.57131; // +/- 2.79021e-05 cm/us All: East = 0.681585 +/- 0.00678976
  row.laserDriftVelocityWest	 =   5.57131; // +/- 2.79021e-05 cm/us All: West = 0.452028 +/- 0.00738234
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57131 +/- 2.79021e-05
  return (TDataSet *)tableSet;// West = 5.57198 +/- 4.13503e-05 East = 5.57075 +/- 3.78064e-05
};
