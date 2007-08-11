TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 114033
  row.laserDriftVelocityEast	 =   5.5756; // +/- 2.18519e-05 cm/us East: Slope = -0.19449 +/- 0.00386053 DV = 5.5756 +/- 2.18519e-05
  row.laserDriftVelocityWest	 =   5.57722; // +/- 3.13443e-05 cm/us West: Slope = -0.482095 +/- 0.0056139 DV = 5.57722 +/- 3.13443e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
