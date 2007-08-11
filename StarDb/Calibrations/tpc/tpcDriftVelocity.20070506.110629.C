TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126031
  row.laserDriftVelocityEast	 =   5.5753; // +/- 1.66349e-05 cm/us East: Slope = -0.139987 +/- 0.00300365 DV = 5.5753 +/- 1.66349e-05
  row.laserDriftVelocityWest	 =   5.57764; // +/- 2.5454e-05 cm/us West: Slope = -0.557688 +/- 0.0045844 DV = 5.57764 +/- 2.5454e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
