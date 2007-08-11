TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 136013
  row.laserDriftVelocityEast	 =   5.57418; // +/- 2.76682e-05 cm/us East: Slope = 0.0562715 +/- 0.0049474 DV = 5.57418 +/- 2.76682e-05
  row.laserDriftVelocityWest	 =   5.57515; // +/- 3.22611e-05 cm/us West: Slope = -0.11164 +/- 0.00576343 DV = 5.57515 +/- 3.22611e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
