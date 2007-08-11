TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119089
  row.laserDriftVelocityEast	 =   5.577; // +/- 3.13536e-05 cm/us East: Slope = -0.452602 +/- 0.00564697 DV = 5.577 +/- 3.13536e-05
  row.laserDriftVelocityWest	 =   5.57812; // +/- 3.27442e-05 cm/us West: Slope = -0.642436 +/- 0.00587447 DV = 5.57812 +/- 3.27442e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
