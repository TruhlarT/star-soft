TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112085
  row.laserDriftVelocityEast	 =   5.57414; // +/- 1.19125e-05 cm/us East: Slope = 0.0706305 +/- 0.00212941 DV = 5.57414 +/- 1.19125e-05
  row.laserDriftVelocityWest	 =   5.57627; // +/- 2.12071e-05 cm/us West: Slope = -0.311815 +/- 0.00378795 DV = 5.57627 +/- 2.12071e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
