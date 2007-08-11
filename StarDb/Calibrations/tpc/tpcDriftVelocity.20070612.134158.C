TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 163037
  row.laserDriftVelocityEast	 =   5.56962; // +/- -1 cm/us East: Slope = 0.713313 +/- 0.00881695 DV = 5.57058 +/- 4.88752e-05
  row.laserDriftVelocityWest	 =   5.57293; // +/- 2.40264e-05 cm/us West: Slope = 0.281944 +/- 0.00436186 DV = 5.57293 +/- 2.40264e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
