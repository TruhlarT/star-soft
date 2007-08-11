TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169028
  row.laserDriftVelocityEast	 =   5.5677; // +/- 1.76069e-05 cm/us East: Slope = 1.22463 +/- 0.00315366 DV = 5.5677 +/- 1.76069e-05
  row.laserDriftVelocityWest	 =   5.57216; // +/- 2.53252e-05 cm/us West: Slope = 0.424981 +/- 0.00460946 DV = 5.57216 +/- 2.53252e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
