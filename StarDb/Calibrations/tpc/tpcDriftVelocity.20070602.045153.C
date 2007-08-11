TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 153003
  row.laserDriftVelocityEast	 =   5.56971; // +/- -1 cm/us East: Slope = 0.566729 +/- 23.841 DV = 5.57138 +/- 0.131967
  row.laserDriftVelocityWest	 =   5.57275; // +/- 2.33476e-05 cm/us West: Slope = 0.315749 +/- 0.00419503 DV = 5.57275 +/- 2.33476e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
