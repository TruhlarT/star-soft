TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 170030
  row.laserDriftVelocityEast	 =   5.5666; // +/- 2.75785e-05 cm/us East: Slope = 1.426 +/- 0.00489051 DV = 5.5666 +/- 2.75785e-05
  row.laserDriftVelocityWest	 =   5.5713; // +/- 2.9489e-05 cm/us West: Slope = 0.583201 +/- 0.00535913 DV = 5.5713 +/- 2.9489e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
