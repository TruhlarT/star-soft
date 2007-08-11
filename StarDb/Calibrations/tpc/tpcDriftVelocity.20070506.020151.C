TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125109
  row.laserDriftVelocityEast	 =   5.57675; // +/- 1.64545e-05 cm/us East: Slope = -0.397258 +/- 0.00294945 DV = 5.57675 +/- 1.64545e-05
  row.laserDriftVelocityWest	 =   5.5787; // +/- 2.1489e-05 cm/us West: Slope = -0.74694 +/- 0.00383875 DV = 5.5787 +/- 2.1489e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
