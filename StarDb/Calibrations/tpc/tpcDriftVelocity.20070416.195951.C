TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 106073
  row.laserDriftVelocityEast	 =   5.57754; // +/- 1.48441e-05 cm/us East: Slope = -0.537496 +/- 0.00265126 DV = 5.57754 +/- 1.48441e-05
  row.laserDriftVelocityWest	 =   5.57917; // +/- 1.87389e-05 cm/us West: Slope = -0.834005 +/- 0.00339478 DV = 5.57917 +/- 1.87389e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
