TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 164035
  row.laserDriftVelocityEast	 =   5.56883; // +/- 2.68786e-05 cm/us East: Slope = 1.00965 +/- 0.00495577 DV = 5.56883 +/- 2.68786e-05
  row.laserDriftVelocityWest	 =   5.57241; // +/- 2.53081e-05 cm/us West: Slope = 0.38123 +/- 0.00456175 DV = 5.57241 +/- 2.53081e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
