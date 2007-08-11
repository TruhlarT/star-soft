TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 149002
  row.laserDriftVelocityEast	 =   5.57028; // +/- -1 cm/us East: Slope = 0.250289 +/- 1.41421 DV = 4.45821 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57323; // +/- 1.42751e-05 cm/us West: Slope = 0.233769 +/- 0.00254638 DV = 5.57323 +/- 1.42751e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
