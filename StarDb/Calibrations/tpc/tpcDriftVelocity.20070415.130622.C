TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105040
  row.laserDriftVelocityEast	 =   5.58252; // +/- 2.14093e-05 cm/us East: Slope = -1.42445 +/- 0.00376567 DV = 5.58252 +/- 2.14093e-05
  row.laserDriftVelocityWest	 =   5.5836; // +/- 2.12956e-05 cm/us West: Slope = -1.624 +/- 0.00387285 DV = 5.5836 +/- 2.12956e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
