TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 154028
  row.laserDriftVelocityEast	 =   5.56986; // +/- -1 cm/us East: Slope = -0.00826257 +/- 0.036478 DV = 5.57465 +/- 0.000186911
  row.laserDriftVelocityWest	 =   5.57295; // +/- 1.77903e-05 cm/us West: Slope = 0.281049 +/- 0.0031709 DV = 5.57295 +/- 1.77903e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
