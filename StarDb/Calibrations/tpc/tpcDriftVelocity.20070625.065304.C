TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176014
  row.laserDriftVelocityEast	 =   5.56875; // +/- 2.29706e-05 cm/us East: Slope = 1.03748 +/- 0.00414663 DV = 5.56875 +/- 2.29706e-05
  row.laserDriftVelocityWest	 =   5.57245; // +/- 2.24478e-05 cm/us West: Slope = 0.373288 +/- 0.00400717 DV = 5.57245 +/- 2.24478e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
