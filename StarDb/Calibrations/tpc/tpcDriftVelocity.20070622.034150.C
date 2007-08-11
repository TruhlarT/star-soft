TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 172138
  row.laserDriftVelocityEast	 =   5.56829; // +/- 3.01713e-05 cm/us East: Slope = 1.11754 +/- 0.00526348 DV = 5.56829 +/- 3.01713e-05
  row.laserDriftVelocityWest	 =   5.57188; // +/- 2.87195e-05 cm/us West: Slope = 0.475944 +/- 0.00516057 DV = 5.57188 +/- 2.87195e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
