TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 151049
  row.laserDriftVelocityEast	 =   5.56995; // +/- -1 cm/us East: Slope = 0.426369 +/- 0.276529 DV = 5.57216 +/- 0.00122697
  row.laserDriftVelocityWest	 =   5.57296; // +/- 1.53307e-05 cm/us West: Slope = 0.278086 +/- 0.00275658 DV = 5.57296 +/- 1.53307e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
