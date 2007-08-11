TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125034
  row.laserDriftVelocityEast	 =   5.57686; // +/- 1.8345e-05 cm/us East: Slope = -0.424311 +/- 0.00329818 DV = 5.57686 +/- 1.8345e-05
  row.laserDriftVelocityWest	 =   5.57859; // +/- 2.32436e-05 cm/us West: Slope = -0.727211 +/- 0.00415119 DV = 5.57859 +/- 2.32436e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
