TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125011
  row.laserDriftVelocityEast	 =   5.57689; // +/- 1.85936e-05 cm/us East: Slope = -0.426175 +/- 0.00333817 DV = 5.57689 +/- 1.85936e-05
  row.laserDriftVelocityWest	 =   5.57833; // +/- 3.01759e-05 cm/us West: Slope = -0.681201 +/- 0.00541322 DV = 5.57833 +/- 3.01759e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
