TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 108005
  row.laserDriftVelocityEast	 =   5.57308; // +/- 1.45597e-05 cm/us East: Slope = 0.256821 +/- 0.00262565 DV = 5.57308 +/- 1.45597e-05
  row.laserDriftVelocityWest	 =   5.5766; // +/- 1.66759e-05 cm/us West: Slope = -0.371096 +/- 0.00299763 DV = 5.5766 +/- 1.66759e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
