TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 175073
  row.laserDriftVelocityEast	 =   5.56884; // +/- 3.91671e-05 cm/us East: Slope = 1.01821 +/- 0.00697211 DV = 5.56884 +/- 3.91671e-05
  row.laserDriftVelocityWest	 =   5.57278; // +/- 3.06825e-05 cm/us West: Slope = 0.31035 +/- 0.00563171 DV = 5.57278 +/- 3.06825e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
