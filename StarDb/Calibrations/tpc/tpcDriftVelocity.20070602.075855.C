TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 153022
  row.laserDriftVelocityEast	 =   5.56993; // +/- -1 cm/us East: Slope = 0 +/- 0 DV = 0 +/- 0
  row.laserDriftVelocityWest	 =   5.57298; // +/- 2.47772e-05 cm/us West: Slope = 0.285927 +/- 0.00445557 DV = 5.57298 +/- 2.47772e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
