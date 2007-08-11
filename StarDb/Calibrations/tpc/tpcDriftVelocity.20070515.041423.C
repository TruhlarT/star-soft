TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135001
  row.laserDriftVelocityEast	 =   5.57269; // +/- 2.2602e-05 cm/us East: Slope = 0.328708 +/- 0.00401537 DV = 5.57269 +/- 2.2602e-05
  row.laserDriftVelocityWest	 =   5.57374; // +/- 3.20993e-05 cm/us West: Slope = 0.141178 +/- 0.00577258 DV = 5.57374 +/- 3.20993e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
