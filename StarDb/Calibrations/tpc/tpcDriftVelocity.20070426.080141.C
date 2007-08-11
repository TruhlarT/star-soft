TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 116035
  row.laserDriftVelocityEast	 =   5.57438; // +/- 2.70255e-05 cm/us East: Slope = 0.0273063 +/- 0.00479528 DV = 5.57438 +/- 2.70255e-05
  row.laserDriftVelocityWest	 =   5.57677; // +/- 2.60075e-05 cm/us West: Slope = -0.402397 +/- 0.00468609 DV = 5.57677 +/- 2.60075e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
