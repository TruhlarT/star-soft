TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 156011
  row.laserDriftVelocityEast	 =   5.5706; // +/- -1 cm/us East: Slope = -0.0444857 +/- 0.0172014 DV = 5.57476 +/- 9.61161e-05
  row.laserDriftVelocityWest	 =   5.57372; // +/- 2.50283e-05 cm/us West: Slope = 0.14455 +/- 0.00447389 DV = 5.57372 +/- 2.50283e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
