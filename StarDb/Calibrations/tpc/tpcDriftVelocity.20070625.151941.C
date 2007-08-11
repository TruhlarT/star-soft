TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176047
  row.laserDriftVelocityEast	 =   5.56831; // +/- 3.54558e-05 cm/us East: Slope = 1.11458 +/- 0.00639987 DV = 5.56831 +/- 3.54558e-05
  row.laserDriftVelocityWest	 =   5.57222; // +/- 3.34227e-05 cm/us West: Slope = 0.41273 +/- 0.00598861 DV = 5.57222 +/- 3.34227e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
