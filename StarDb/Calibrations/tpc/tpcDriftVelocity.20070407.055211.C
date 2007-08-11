TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 97022
  row.laserDriftVelocityEast	 =   5.57518; // +/- 2.26025e-05 cm/us East: Slope = -1.4186 +/- 0.00409558 DV = 5.57518 +/- 2.26025e-05
  row.laserDriftVelocityWest	 =   5.57558; // +/- 2.01969e-05 cm/us West: Slope = -1.49504 +/- 0.00363814 DV = 5.57558 +/- 2.01969e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
