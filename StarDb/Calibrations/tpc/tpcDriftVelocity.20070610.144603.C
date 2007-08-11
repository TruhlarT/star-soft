TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 161050
  row.laserDriftVelocityEast	 =   5.57029; // +/- -1 cm/us East: Slope = 0.647456 +/- 0.0141288 DV = 5.57091 +/- 7.82788e-05
  row.laserDriftVelocityWest	 =   5.57355; // +/- 2.97996e-05 cm/us West: Slope = 0.173478 +/- 0.00540121 DV = 5.57355 +/- 2.97996e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
