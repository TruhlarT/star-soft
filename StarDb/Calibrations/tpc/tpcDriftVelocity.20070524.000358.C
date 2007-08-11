TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 143055
  row.laserDriftVelocityEast	 =   5.56953; // +/- -1 cm/us East: Slope = 0.116394 +/- 0.0340409 DV = 5.57387 +/- 0.000166479
  row.laserDriftVelocityWest	 =   5.57235; // +/- 1.37758e-05 cm/us West: Slope = 0.393055 +/- 0.00249202 DV = 5.57235 +/- 1.37758e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
