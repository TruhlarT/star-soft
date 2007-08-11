TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 120049
  row.laserDriftVelocityEast	 =   5.57753; // +/- 1.15334e-05 cm/us East: Slope = -0.53901 +/- 0.00206872 DV = 5.57753 +/- 1.15334e-05
  row.laserDriftVelocityWest	 =   5.57869; // +/- 3.24977e-05 cm/us West: Slope = -0.743878 +/- 0.0059242 DV = 5.57869 +/- 3.24977e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
