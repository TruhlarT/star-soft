TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 107018
  row.laserDriftVelocityEast	 =   5.57608; // +/- 1.81681e-05 cm/us East: Slope = -0.27918 +/- 0.00327398 DV = 5.57608 +/- 1.81681e-05
  row.laserDriftVelocityWest	 =   5.57766; // +/- 2.6017e-05 cm/us West: Slope = -0.561301 +/- 0.00459803 DV = 5.57766 +/- 2.6017e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
