TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 107082
  row.laserDriftVelocityEast	 =   5.57306; // +/- 1.54137e-05 cm/us East: Slope = 0.261603 +/- 0.0027624 DV = 5.57306 +/- 1.54137e-05
  row.laserDriftVelocityWest	 =   5.5769; // +/- 2.32599e-05 cm/us West: Slope = -0.423567 +/- 0.00417247 DV = 5.5769 +/- 2.32599e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
