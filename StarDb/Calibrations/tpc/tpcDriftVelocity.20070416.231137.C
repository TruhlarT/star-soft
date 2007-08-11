TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 106088
  row.laserDriftVelocityEast	 =   5.57742; // +/- 2.80589e-05 cm/us East: Slope = -0.519197 +/- 0.00505633 DV = 5.57742 +/- 2.80589e-05
  row.laserDriftVelocityWest	 =   5.57899; // +/- 2.40919e-05 cm/us West: Slope = -0.800609 +/- 0.00430131 DV = 5.57899 +/- 2.40919e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
