TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 170021
  row.laserDriftVelocityEast	 =   5.56673; // +/- 2.93809e-05 cm/us East: Slope = 1.3994 +/- 0.00530756 DV = 5.56673 +/- 2.93809e-05
  row.laserDriftVelocityWest	 =   5.57071; // +/- 3.52057e-05 cm/us West: Slope = 0.687895 +/- 0.00631198 DV = 5.57071 +/- 3.52057e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
