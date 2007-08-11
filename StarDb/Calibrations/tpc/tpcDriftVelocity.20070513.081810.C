TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 133023
  row.laserDriftVelocityEast	 =   5.56892; // +/- 3.80499e-05 cm/us East: Slope = 1.00934 +/- 0.00690705 DV = 5.56892 +/- 3.80499e-05
  row.laserDriftVelocityWest	 =   5.57145; // +/- -1 cm/us West: Slope = 0.872568 +/- 0.00744703 DV = 5.56964 +/- 4.13908e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
