TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 120029
  row.laserDriftVelocityEast	 =   5.57692; // +/- 1.47561e-05 cm/us East: Slope = -0.426383 +/- 0.00263418 DV = 5.57692 +/- 1.47561e-05
  row.laserDriftVelocityWest	 =   5.57847; // +/- 2.3329e-05 cm/us West: Slope = -0.706925 +/- 0.00417955 DV = 5.57847 +/- 2.3329e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
