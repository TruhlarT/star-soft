TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 121092
  row.laserDriftVelocityEast	 =   5.5771; // +/- 2.11495e-05 cm/us East: Slope = -0.459911 +/- 0.00379672 DV = 5.5771 +/- 2.11495e-05
  row.laserDriftVelocityWest	 =   5.57934; // +/- 1.98074e-05 cm/us West: Slope = -0.862903 +/- 0.00353773 DV = 5.57934 +/- 1.98074e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
