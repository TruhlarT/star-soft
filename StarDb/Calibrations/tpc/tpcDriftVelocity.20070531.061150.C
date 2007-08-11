TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 151012
  row.laserDriftVelocityEast	 =   5.56993; // +/- -1 cm/us East: Slope = 0.310762 +/- 1.41421 DV = 4.45792 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57292; // +/- 2.26287e-05 cm/us West: Slope = 0.290885 +/- 0.00406459 DV = 5.57292 +/- 2.26287e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
