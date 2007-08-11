TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 122023
  row.laserDriftVelocityEast	 =   5.57788; // +/- 2.3067e-05 cm/us East: Slope = -0.602191 +/- 0.0041332 DV = 5.57788 +/- 2.3067e-05
  row.laserDriftVelocityWest	 =   5.58012; // +/- 2.79509e-05 cm/us West: Slope = -1.00781 +/- 0.0049972 DV = 5.58012 +/- 2.79509e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
