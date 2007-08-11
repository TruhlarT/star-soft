TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 93001
  row.laserDriftVelocityEast	 =   5.5812; // +/- 1.60455e-05 cm/us East: Slope = -2.50719 +/- 0.00287318 DV = 5.5812 +/- 1.60455e-05
  row.laserDriftVelocityWest	 =   5.58276; // +/- 2.32828e-05 cm/us West: Slope = -2.78312 +/- 0.00415771 DV = 5.58276 +/- 2.32828e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
