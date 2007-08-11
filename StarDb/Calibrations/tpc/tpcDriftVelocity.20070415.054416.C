TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105012
  row.laserDriftVelocityEast	 =   5.58089; // +/- -1 cm/us East: Slope = 0 +/- 0 DV = 0 +/- 0
  row.laserDriftVelocityWest	 =   5.58271; // +/- 1.87654e-05 cm/us West: Slope = -1.4658 +/- 0.00331771 DV = 5.58271 +/- 1.87654e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
