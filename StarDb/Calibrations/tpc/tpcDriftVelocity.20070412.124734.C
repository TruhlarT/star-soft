TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 102058
  row.laserDriftVelocityEast	 =   5.5696; // +/- 1.56986e-05 cm/us East: Slope = 1.30178 +/- 0.00287698 DV = 5.5696 +/- 1.56986e-05
  row.laserDriftVelocityWest	 =   5.57376; // +/- 2.10782e-05 cm/us West: Slope = 0.555279 +/- 0.00373873 DV = 5.57376 +/- 2.10782e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
