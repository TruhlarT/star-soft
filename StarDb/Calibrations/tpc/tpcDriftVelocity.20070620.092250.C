TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 171010
  row.laserDriftVelocityEast	 =   5.56684; // +/- 2.06158e-05 cm/us East: Slope = 1.38201 +/- 0.0037364 DV = 5.56684 +/- 2.06158e-05
  row.laserDriftVelocityWest	 =   5.5705; // +/- 3.17246e-05 cm/us West: Slope = 0.721228 +/- 0.00566076 DV = 5.5705 +/- 3.17246e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
