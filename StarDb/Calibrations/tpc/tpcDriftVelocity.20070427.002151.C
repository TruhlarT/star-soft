TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 116091
  row.laserDriftVelocityEast	 =   5.57507; // +/- 1.60768e-05 cm/us East: Slope = -0.09326 +/- 0.00286872 DV = 5.57507 +/- 1.60768e-05
  row.laserDriftVelocityWest	 =   5.57686; // +/- 1.66795e-05 cm/us West: Slope = -0.420548 +/- 0.00298027 DV = 5.57686 +/- 1.66795e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
