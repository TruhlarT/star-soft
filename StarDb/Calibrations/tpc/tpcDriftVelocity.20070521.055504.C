TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141015
  row.laserDriftVelocityEast	 =   5.57251; // +/- -1 cm/us East: Slope = 0.270383 +/- 0.00783624 DV = 5.57306 +/- 4.35022e-05
  row.laserDriftVelocityWest	 =   5.57525; // +/- 3.35515e-05 cm/us West: Slope = -0.127386 +/- 0.00605545 DV = 5.57525 +/- 3.35515e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
