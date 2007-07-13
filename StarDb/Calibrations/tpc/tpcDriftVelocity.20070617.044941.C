TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 168002
  row.laserDriftVelocityEast	 =   5.57152; // +/- 2.72368e-05 cm/us All: East = 0.768071 +/- 0.00620121
  row.laserDriftVelocityWest	 =   5.57152; // +/- 2.72368e-05 cm/us All: West = 0.159528 +/- 0.00784772
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57152 +/- 2.72368e-05
  return (TDataSet *)tableSet;// West = 5.57366 +/- 4.46844e-05 East = 5.57025 +/- 3.43571e-05
};
