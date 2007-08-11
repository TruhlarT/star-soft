TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 116059
  row.laserDriftVelocityEast	 =   5.57457; // +/- 1.97928e-05 cm/us East: Slope = -0.00831319 +/- 0.00359048 DV = 5.57457 +/- 1.97928e-05
  row.laserDriftVelocityWest	 =   5.5768; // +/- 2.59601e-05 cm/us West: Slope = -0.405899 +/- 0.00460282 DV = 5.5768 +/- 2.59601e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
