TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 132016
  row.laserDriftVelocityEast	 =   5.56589; // +/- 2.42005e-05 cm/us East: Slope = 1.54862 +/- 0.00432674 DV = 5.56589 +/- 2.42005e-05
  row.laserDriftVelocityWest	 =   5.56738; // +/- 2.59601e-05 cm/us West: Slope = 1.28422 +/- 0.00464893 DV = 5.56738 +/- 2.59601e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
