TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 171036
  row.laserDriftVelocityEast	 =   5.56789; // +/- 2.54446e-05 cm/us East: Slope = 1.19593 +/- 0.00456356 DV = 5.56789 +/- 2.54446e-05
  row.laserDriftVelocityWest	 =   5.57124; // +/- 3.28191e-05 cm/us West: Slope = 0.592067 +/- 0.00583925 DV = 5.57124 +/- 3.28191e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
