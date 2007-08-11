TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 95064
  row.laserDriftVelocityEast	 =   5.5765; // +/- 1.51573e-05 cm/us East: Slope = -1.66314 +/- 0.00272436 DV = 5.5765 +/- 1.51573e-05
  row.laserDriftVelocityWest	 =   5.5778; // +/- 1.91805e-05 cm/us West: Slope = -1.89257 +/- 0.00346092 DV = 5.5778 +/- 1.91805e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
