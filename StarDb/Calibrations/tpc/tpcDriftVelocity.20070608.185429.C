TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 159042
  row.laserDriftVelocityEast	 =   5.57083; // +/- -1 cm/us East: Slope = 0.498637 +/- 0.0232484 DV = 5.5719 +/- 0.000119099
  row.laserDriftVelocityWest	 =   5.57405; // +/- 2.22169e-05 cm/us West: Slope = 0.0882917 +/- 0.0039777 DV = 5.57405 +/- 2.22169e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
