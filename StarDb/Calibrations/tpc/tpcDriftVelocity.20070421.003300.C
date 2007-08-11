TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 110130
  row.laserDriftVelocityEast	 =   5.57307; // +/- 1.75193e-05 cm/us East: Slope = 0.262262 +/- 0.00313909 DV = 5.57307 +/- 1.75193e-05
  row.laserDriftVelocityWest	 =   5.57487; // +/- 1.74536e-05 cm/us West: Slope = -0.0610732 +/- 0.0031325 DV = 5.57487 +/- 1.74536e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
