TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119077
  row.laserDriftVelocityEast	 =   5.57605; // +/- 2.00959e-05 cm/us East: Slope = -0.271361 +/- 0.00361484 DV = 5.57605 +/- 2.00959e-05
  row.laserDriftVelocityWest	 =   5.57821; // +/- 2.95924e-05 cm/us West: Slope = -0.656413 +/- 0.00542457 DV = 5.57821 +/- 2.95924e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
