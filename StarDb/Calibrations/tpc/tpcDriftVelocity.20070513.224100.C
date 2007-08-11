TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 133065
  row.laserDriftVelocityEast	 =   5.56881; // +/- 1.10936e-05 cm/us East: Slope = 1.02369 +/- 0.00200155 DV = 5.56881 +/- 1.10936e-05
  row.laserDriftVelocityWest	 =   5.57187; // +/- 2.05178e-05 cm/us West: Slope = 0.476816 +/- 0.00365754 DV = 5.57187 +/- 2.05178e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
