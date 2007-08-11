TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169123
  row.laserDriftVelocityEast	 =   5.56745; // +/- 2.09152e-05 cm/us East: Slope = 1.27636 +/- 0.00375507 DV = 5.56745 +/- 2.09152e-05
  row.laserDriftVelocityWest	 =   5.57125; // +/- 2.55518e-05 cm/us West: Slope = 0.588381 +/- 0.00460034 DV = 5.57125 +/- 2.55518e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
