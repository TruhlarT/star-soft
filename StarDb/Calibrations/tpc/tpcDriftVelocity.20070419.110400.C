TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 109041
  row.laserDriftVelocityEast	 =   5.57122; // +/- 1.30183e-05 cm/us East: Slope = 0.59558 +/- 0.00234181 DV = 5.57122 +/- 1.30183e-05
  row.laserDriftVelocityWest	 =   5.57528; // +/- 1.3776e-05 cm/us West: Slope = -0.134718 +/- 0.00246864 DV = 5.57528 +/- 1.3776e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
