TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 95087
  row.laserDriftVelocityEast	 =   5.57822; // +/- 2.15673e-05 cm/us All: East = -2.0593 +/- 0.00521253
  row.laserDriftVelocityWest	 =   5.57822; // +/- 2.15673e-05 cm/us All: West = -1.86104 +/- 0.00592789
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57822 +/- 2.15673e-05
  return (TDataSet *)tableSet;// West = 5.57759 +/- 3.24516e-05 East = 5.57872 +/- 2.88643e-05
};
