TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 149029
  row.laserDriftVelocityEast	 =   5.57018; // +/- -1 cm/us East: Slope = 0.274983 +/- 1.41421 DV = 4.4581 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57313; // +/- 1.5079e-05 cm/us West: Slope = 0.250985 +/- 0.00271022 DV = 5.57313 +/- 1.5079e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
