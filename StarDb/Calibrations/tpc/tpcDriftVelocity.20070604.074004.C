TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 155011
  row.laserDriftVelocityEast	 =   5.57002; // +/- -1 cm/us East: Slope = -0.0040894 +/- 0.030753 DV = 5.57441 +/- 0.000153767
  row.laserDriftVelocityWest	 =   5.57312; // +/- 2.48108e-05 cm/us West: Slope = 0.257544 +/- 0.00437696 DV = 5.57312 +/- 2.48108e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
