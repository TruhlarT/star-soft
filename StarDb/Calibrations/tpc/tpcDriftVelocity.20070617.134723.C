TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 168047
  row.laserDriftVelocityEast	 =   5.56832; // +/- 3.23133e-05 cm/us East: Slope = 1.11575 +/- 0.00589188 DV = 5.56832 +/- 3.23133e-05
  row.laserDriftVelocityWest	 =   5.57254; // +/- 3.91338e-05 cm/us West: Slope = 0.358931 +/- 0.00694194 DV = 5.57254 +/- 3.91338e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
