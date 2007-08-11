TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 133010
  row.laserDriftVelocityEast	 =   5.56773; // +/- 2.74255e-05 cm/us East: Slope = 1.23024 +/- 0.00492055 DV = 5.56773 +/- 2.74255e-05
  row.laserDriftVelocityWest	 =   5.57026; // +/- -1 cm/us West: Slope = 0.911661 +/- 0.00793941 DV = 5.56943 +/- 4.54791e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
