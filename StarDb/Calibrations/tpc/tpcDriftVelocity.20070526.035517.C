TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 145097
  row.laserDriftVelocityEast	 =   5.57124; // +/- -1 cm/us East: Slope = -0.193608 +/- 1.67059 DV = 5.56878 +/- 0.01405
  row.laserDriftVelocityWest	 =   5.57411; // +/- 1.84855e-05 cm/us West: Slope = 0.0723973 +/- 0.003346 DV = 5.57411 +/- 1.84855e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
