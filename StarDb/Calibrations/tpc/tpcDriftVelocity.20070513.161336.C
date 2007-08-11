TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 133038
  row.laserDriftVelocityEast	 =   5.56892; // +/- 2.14621e-05 cm/us East: Slope = 1.00047 +/- 0.00381894 DV = 5.56892 +/- 2.14621e-05
  row.laserDriftVelocityWest	 =   5.57027; // +/- 2.4843e-05 cm/us West: Slope = 0.763571 +/- 0.00445889 DV = 5.57027 +/- 2.4843e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
