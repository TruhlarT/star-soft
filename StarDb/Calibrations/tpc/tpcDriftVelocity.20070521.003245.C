TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 140063
  row.laserDriftVelocityEast	 =   5.57425; // +/- 2.56788e-05 cm/us East: Slope = 0.0460359 +/- 0.00457849 DV = 5.57425 +/- 2.56788e-05
  row.laserDriftVelocityWest	 =   5.57496; // +/- 2.23843e-05 cm/us West: Slope = -0.0790573 +/- 0.00403658 DV = 5.57496 +/- 2.23843e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
