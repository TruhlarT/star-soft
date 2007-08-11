TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141078
  row.laserDriftVelocityEast	 =   5.57344; // +/- 3.00203e-05 cm/us East: Slope = 0.186794 +/- 0.00540502 DV = 5.57344 +/- 3.00203e-05
  row.laserDriftVelocityWest	 =   5.57455; // +/- 3.11773e-05 cm/us West: Slope = -0.00411531 +/- 0.00563557 DV = 5.57455 +/- 3.11773e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
