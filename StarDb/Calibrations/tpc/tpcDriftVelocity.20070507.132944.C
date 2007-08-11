TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 127027
  row.laserDriftVelocityEast	 =   5.57441; // +/- 2.31976e-05 cm/us East: Slope = 0.0265188 +/- 0.00416749 DV = 5.57441 +/- 2.31976e-05
  row.laserDriftVelocityWest	 =   5.5768; // +/- -1 cm/us West: Slope = -0.248129 +/- 0.00772805 DV = 5.57591 +/- 4.33199e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
