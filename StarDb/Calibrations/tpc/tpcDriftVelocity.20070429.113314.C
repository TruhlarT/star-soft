TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119018
  row.laserDriftVelocityEast	 =   5.57628; // +/- 1.14009e-05 cm/us East: Slope = -0.313739 +/- 0.00204156 DV = 5.57628 +/- 1.14009e-05
  row.laserDriftVelocityWest	 =   5.57803; // +/- 1.53153e-05 cm/us West: Slope = -0.629412 +/- 0.00275158 DV = 5.57803 +/- 1.53153e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
