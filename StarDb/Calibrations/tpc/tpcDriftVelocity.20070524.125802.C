TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 144002
  row.laserDriftVelocityEast	 =   5.57084; // +/- -1 cm/us East: Slope = -17.2215 +/- 0.0594779 DV = 5.57101 +/- 0.000281162
  row.laserDriftVelocityWest	 =   5.57366; // +/- 1.24953e-05 cm/us West: Slope = -17.6749 +/- 0.00219583 DV = 5.57366 +/- 1.24953e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
