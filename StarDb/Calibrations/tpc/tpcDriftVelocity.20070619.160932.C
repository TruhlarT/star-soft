TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 170047
  row.laserDriftVelocityEast	 =   5.56948; // +/- 2.04662e-05 cm/us All: East = 1.04662 +/- 0.00480617
  row.laserDriftVelocityWest	 =   5.56948; // +/- 2.04662e-05 cm/us All: West = 0.705999 +/- 0.00566046
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56948 +/- 2.04662e-05
  return (TDataSet *)tableSet;// West = 5.5706 +/- 3.17098e-05 East = 5.56869 +/- 2.67943e-05
};
