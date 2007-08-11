TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 120121
  row.laserDriftVelocityEast	 =   5.57779; // +/- 3.45082e-05 cm/us East: Slope = -0.579216 +/- 0.00619689 DV = 5.57779 +/- 3.45082e-05
  row.laserDriftVelocityWest	 =   5.57886; // +/- 2.18774e-05 cm/us West: Slope = -0.776493 +/- 0.00393944 DV = 5.57886 +/- 2.18774e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
