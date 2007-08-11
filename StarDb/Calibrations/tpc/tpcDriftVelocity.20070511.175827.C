TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 131056
  row.laserDriftVelocityEast	 =   5.56196; // +/- 2.59399e-05 cm/us East: Slope = 2.26322 +/- 0.00463981 DV = 5.56196 +/- 2.59399e-05
  row.laserDriftVelocityWest	 =   5.56299; // +/- 3.349e-05 cm/us West: Slope = 2.07368 +/- 0.00607527 DV = 5.56299 +/- 3.349e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
