TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 118011
  row.laserDriftVelocityEast	 =   5.57549; // +/- 1.81911e-05 cm/us East: Slope = -0.171238 +/- 0.00322531 DV = 5.57549 +/- 1.81911e-05
  row.laserDriftVelocityWest	 =   5.57707; // +/- 1.95572e-05 cm/us West: Slope = -0.455759 +/- 0.00350778 DV = 5.57707 +/- 1.95572e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
