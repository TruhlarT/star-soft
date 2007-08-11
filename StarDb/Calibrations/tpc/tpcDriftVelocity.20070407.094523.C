TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 97035
  row.laserDriftVelocityEast	 =   5.57524; // +/- 2.36604e-05 cm/us East: Slope = -1.4326 +/- 0.0042303 DV = 5.57524 +/- 2.36604e-05
  row.laserDriftVelocityWest	 =   5.5753; // +/- 2.13397e-05 cm/us West: Slope = -1.44649 +/- 0.00383184 DV = 5.5753 +/- 2.13397e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
