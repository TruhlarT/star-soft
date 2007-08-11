TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 160012
  row.laserDriftVelocityEast	 =   5.57043; // +/- -1 cm/us East: Slope = 0.513585 +/- 0.011923 DV = 5.57161 +/- 6.60173e-05
  row.laserDriftVelocityWest	 =   5.57366; // +/- 2.93403e-05 cm/us West: Slope = 0.152352 +/- 0.00517797 DV = 5.57366 +/- 2.93403e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
