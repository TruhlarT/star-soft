TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105063
  row.laserDriftVelocityEast	 =   5.58082; // +/- 2.12262e-05 cm/us East: Slope = -1.12437 +/- 0.00375568 DV = 5.58082 +/- 2.12262e-05
  row.laserDriftVelocityWest	 =   5.58346; // +/- 1.39126e-05 cm/us West: Slope = -1.60104 +/- 0.00247654 DV = 5.58346 +/- 1.39126e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
