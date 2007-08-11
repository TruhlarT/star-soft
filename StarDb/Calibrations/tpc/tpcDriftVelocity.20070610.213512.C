TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 161074
  row.laserDriftVelocityEast	 =   5.57024; // +/- -1 cm/us East: Slope = 0.531922 +/- 0.00978853 DV = 5.57154 +/- 5.64183e-05
  row.laserDriftVelocityWest	 =   5.57351; // +/- 2.81906e-05 cm/us West: Slope = 0.194612 +/- 0.00507577 DV = 5.57351 +/- 2.81906e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
