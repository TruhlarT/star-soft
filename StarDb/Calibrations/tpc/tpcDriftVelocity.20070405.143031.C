TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 95087
  row.laserDriftVelocityEast	 =   5.57668; // +/- 1.75037e-05 cm/us East: Slope = -1.69359 +/- 0.00315673 DV = 5.57668 +/- 1.75037e-05
  row.laserDriftVelocityWest	 =   5.57767; // +/- 2.21688e-05 cm/us West: Slope = -1.87015 +/- 0.00388148 DV = 5.57767 +/- 2.21688e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
