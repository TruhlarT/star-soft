TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139074
  row.laserDriftVelocityEast	 =   5.57331; // +/- 2.56037e-05 cm/us East: Slope = 0.217968 +/- 0.00459816 DV = 5.57331 +/- 2.56037e-05
  row.laserDriftVelocityWest	 =   5.57484; // +/- 3.021e-05 cm/us West: Slope = -0.0559945 +/- 0.00543663 DV = 5.57484 +/- 3.021e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
