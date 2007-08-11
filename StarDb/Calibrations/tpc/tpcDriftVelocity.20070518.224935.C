TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138079
  row.laserDriftVelocityEast	 =   5.57116; // +/- -1 cm/us East: Slope = 0.126543 +/- 0.00858323 DV = 5.5738 +/- 4.85031e-05
  row.laserDriftVelocityWest	 =   5.57384; // +/- 3.07276e-05 cm/us West: Slope = 0.123879 +/- 0.0055451 DV = 5.57384 +/- 3.07276e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
