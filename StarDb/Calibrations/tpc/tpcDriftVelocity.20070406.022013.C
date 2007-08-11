TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 95221
  row.laserDriftVelocityEast	 =   5.57466; // +/- 1.18486e-05 cm/us East: Slope = -1.33244 +/- 0.00212583 DV = 5.57466 +/- 1.18486e-05
  row.laserDriftVelocityWest	 =   5.57721; // +/- 1.49758e-05 cm/us West: Slope = -1.78789 +/- 0.00268615 DV = 5.57721 +/- 1.49758e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
