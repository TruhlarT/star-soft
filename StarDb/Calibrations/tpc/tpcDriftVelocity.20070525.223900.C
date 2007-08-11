TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 145065
  row.laserDriftVelocityEast	 =   5.57202; // +/- -1 cm/us East: Slope = -0.208333 +/- 0.246897 DV = 5.57566 +/- 0.00142889
  row.laserDriftVelocityWest	 =   5.57488; // +/- 1.03977e-05 cm/us West: Slope = -0.0643566 +/- 0.00185614 DV = 5.57488 +/- 1.03977e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
