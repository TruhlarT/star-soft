TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135105
  row.laserDriftVelocityEast	 =   5.57453; // +/- 2.45527e-05 cm/us East: Slope = 0.0021636 +/- 0.00440814 DV = 5.57453 +/- 2.45527e-05
  row.laserDriftVelocityWest	 =   5.5755; // +/- 3.1176e-05 cm/us West: Slope = -0.171155 +/- 0.00552067 DV = 5.5755 +/- 3.1176e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
