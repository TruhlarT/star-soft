TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105092
  row.laserDriftVelocityEast	 =   5.57994; // +/- 1.70457e-05 cm/us East: Slope = -0.965149 +/- 0.00304611 DV = 5.57994 +/- 1.70457e-05
  row.laserDriftVelocityWest	 =   5.58241; // +/- 1.77191e-05 cm/us West: Slope = -1.41169 +/- 0.00312954 DV = 5.58241 +/- 1.77191e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
