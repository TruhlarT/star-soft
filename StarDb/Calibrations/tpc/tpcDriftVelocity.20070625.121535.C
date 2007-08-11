TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176038
  row.laserDriftVelocityEast	 =   5.56852; // +/- 3.21589e-05 cm/us East: Slope = 1.07279 +/- 0.00568474 DV = 5.56852 +/- 3.21589e-05
  row.laserDriftVelocityWest	 =   5.57223; // +/- 2.96814e-05 cm/us West: Slope = 0.406484 +/- 0.00533673 DV = 5.57223 +/- 2.96814e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
