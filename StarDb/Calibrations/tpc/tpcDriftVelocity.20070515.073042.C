TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135022
  row.laserDriftVelocityEast	 =   5.57226; // +/- 2.6828e-05 cm/us East: Slope = 0.403035 +/- 0.00484733 DV = 5.57226 +/- 2.6828e-05
  row.laserDriftVelocityWest	 =   5.57463; // +/- 3.24969e-05 cm/us West: Slope = -0.023332 +/- 0.00576529 DV = 5.57463 +/- 3.24969e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
