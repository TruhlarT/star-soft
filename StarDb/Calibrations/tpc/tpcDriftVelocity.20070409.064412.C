TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 99013
  row.laserDriftVelocityEast	 =   5.57443; // +/- 2.05058e-05 cm/us All: East = 0.404641 +/- 0.00483497
  row.laserDriftVelocityWest	 =   5.57443; // +/- 2.05058e-05 cm/us All: West = 0.834996 +/- 0.00562292
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57443 +/- 2.05058e-05
  return (TDataSet *)tableSet;// West = 5.57307 +/- 3.14272e-05 East = 5.57544 +/- 2.70595e-05
};
