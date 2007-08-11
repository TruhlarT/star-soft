TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 156111
  row.laserDriftVelocityEast	 =   5.57048; // +/- -1 cm/us East: Slope = 0 +/- 0 DV = 0 +/- 0
  row.laserDriftVelocityWest	 =   5.57362; // +/- 2.81238e-05 cm/us West: Slope = 0.15987 +/- 0.00504195 DV = 5.57362 +/- 2.81238e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
