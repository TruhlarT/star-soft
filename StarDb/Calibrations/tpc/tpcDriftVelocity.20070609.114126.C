TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 160028
  row.laserDriftVelocityEast	 =   5.57131; // +/- 3.71517e-05 cm/us East: Slope = 0.578231 +/- 0.00663882 DV = 5.57131 +/- 3.71517e-05
  row.laserDriftVelocityWest	 =   5.57338; // +/- 2.50927e-05 cm/us West: Slope = 0.208382 +/- 0.00452493 DV = 5.57338 +/- 2.50927e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
