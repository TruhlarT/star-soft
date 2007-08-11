TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126050
  row.laserDriftVelocityEast	 =   5.57416; // +/- 1.80496e-05 cm/us East: Slope = 0.0646392 +/- 0.00322069 DV = 5.57416 +/- 1.80496e-05
  row.laserDriftVelocityWest	 =   5.5769; // +/- 3.16926e-05 cm/us West: Slope = -0.429778 +/- 0.00570215 DV = 5.5769 +/- 3.16926e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
