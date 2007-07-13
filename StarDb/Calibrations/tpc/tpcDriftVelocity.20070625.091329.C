TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176022
  row.laserDriftVelocityEast	 =   5.57169; // +/- 2.38506e-05 cm/us All: East = 0.676013 +/- 0.00626632
  row.laserDriftVelocityWest	 =   5.57169; // +/- 2.38506e-05 cm/us All: West = 0.359823 +/- 0.00584917
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57169 +/- 2.38506e-05
  return (TDataSet *)tableSet;// West = 5.57253 +/- 3.2809e-05 East = 5.57076 +/- 3.47329e-05
};
