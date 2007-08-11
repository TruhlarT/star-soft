TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 151074
  row.laserDriftVelocityEast	 =   5.56932; // +/- -1 cm/us East: Slope = 1.62046 +/- 0.885654 DV = 5.56566 +/- 0.00425139
  row.laserDriftVelocityWest	 =   5.57234; // +/- 2.37282e-05 cm/us West: Slope = 0.393306 +/- 0.00424194 DV = 5.57234 +/- 2.37282e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
