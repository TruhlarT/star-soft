TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 100169
  row.laserDriftVelocityEast	 =   5.57044; // +/- 2.47501e-05 cm/us East: Slope = 1.15157 +/- 0.00444106 DV = 5.57044 +/- 2.47501e-05
  row.laserDriftVelocityWest	 =   5.5729; // +/- 2.49388e-05 cm/us West: Slope = 0.707627 +/- 0.00449035 DV = 5.5729 +/- 2.49388e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
