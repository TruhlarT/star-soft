TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 134012
  row.laserDriftVelocityEast	 =   5.56942; // +/- -1 cm/us East: Slope = 0.812382 +/- 0.00753922 DV = 5.57009 +/- 4.18734e-05
  row.laserDriftVelocityWest	 =   5.57198; // +/- 3.38843e-05 cm/us West: Slope = 0.452271 +/- 0.00616165 DV = 5.57198 +/- 3.38843e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
