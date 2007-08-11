TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126017
  row.laserDriftVelocityEast	 =   5.57531; // +/- 3.24962e-05 cm/us East: Slope = -0.139341 +/- 0.00571572 DV = 5.57531 +/- 3.24962e-05
  row.laserDriftVelocityWest	 =   5.57767; // +/- -1 cm/us West: Slope = -0.790888 +/- 0.00771747 DV = 5.57895 +/- 4.29e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
