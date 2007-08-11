TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 146088
  row.laserDriftVelocityEast	 =   5.57094; // +/- -1 cm/us East: Slope = 0.685708 +/- 0.760963 DV = 5.57124 +/- 0.00457879
  row.laserDriftVelocityWest	 =   5.57383; // +/- 1.21057e-05 cm/us West: Slope = 0.123363 +/- 0.00216953 DV = 5.57383 +/- 1.21057e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
