TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 163044
  row.laserDriftVelocityEast	 =   5.57121; // +/- 1.63279e-05 cm/us East: Slope = -17.24 +/- 0.00287738 DV = 5.57121 +/- 1.63279e-05
  row.laserDriftVelocityWest	 =   5.57433; // +/- 1.59424e-05 cm/us West: Slope = -17.7899 +/- 0.0028108 DV = 5.57433 +/- 1.59424e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
