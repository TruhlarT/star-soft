TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 131009
  row.laserDriftVelocityEast	 =   5.5579; // +/- 1.86036e-05 cm/us East: Slope = 2.99214 +/- 0.00334539 DV = 5.5579 +/- 1.86036e-05
  row.laserDriftVelocityWest	 =   5.56006; // +/- 3.25512e-05 cm/us West: Slope = 2.60507 +/- 0.00588628 DV = 5.56006 +/- 3.25512e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
