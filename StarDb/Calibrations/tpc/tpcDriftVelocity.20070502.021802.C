TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 121120
  row.laserDriftVelocityEast	 =   5.5781; // +/- 2.82021e-05 cm/us East: Slope = -0.631908 +/- 0.00497357 DV = 5.5781 +/- 2.82021e-05
  row.laserDriftVelocityWest	 =   5.57964; // +/- 2.7536e-05 cm/us West: Slope = -0.916951 +/- 0.00488492 DV = 5.57964 +/- 2.7536e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
