TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 107071
  row.laserDriftVelocityEast	 =   5.57323; // +/- 1.5971e-05 cm/us East: Slope = 0.236695 +/- 0.00291456 DV = 5.57323 +/- 1.5971e-05
  row.laserDriftVelocityWest	 =   5.57724; // +/- 2.08776e-05 cm/us West: Slope = -0.485483 +/- 0.00371833 DV = 5.57724 +/- 2.08776e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
