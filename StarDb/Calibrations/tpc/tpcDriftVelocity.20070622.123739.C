TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 173028
  row.laserDriftVelocityEast	 =   5.5683; // +/- 2.78298e-05 cm/us East: Slope = 1.11573 +/- 0.00501517 DV = 5.5683 +/- 2.78298e-05
  row.laserDriftVelocityWest	 =   5.57213; // +/- 2.89298e-05 cm/us West: Slope = 0.430674 +/- 0.00519271 DV = 5.57213 +/- 2.89298e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
