TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 92034
  row.laserDriftVelocityEast	 =   5.58203; // +/- 1.98349e-05 cm/us East: Slope = -2.64752 +/- 0.00355481 DV = 5.58203 +/- 1.98349e-05
  row.laserDriftVelocityWest	 =   5.58355; // +/- 2.18079e-05 cm/us West: Slope = -2.91833 +/- 0.00391805 DV = 5.58355 +/- 2.18079e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
