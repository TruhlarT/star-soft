TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138094
  row.laserDriftVelocityEast	 =   5.57193; // +/- 3.85917e-05 cm/us East: Slope = 0.477914 +/- 0.00691539 DV = 5.57193 +/- 3.85917e-05
  row.laserDriftVelocityWest	 =   5.57457; // +/- 2.09073e-05 cm/us West: Slope = -0.00343617 +/- 0.00376183 DV = 5.57457 +/- 2.09073e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
