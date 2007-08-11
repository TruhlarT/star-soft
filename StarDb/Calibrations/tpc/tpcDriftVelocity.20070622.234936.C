TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 173087
  row.laserDriftVelocityEast	 =   5.56889; // +/- 2.16359e-05 cm/us East: Slope = 1.01093 +/- 0.00388388 DV = 5.56889 +/- 2.16359e-05
  row.laserDriftVelocityWest	 =   5.57247; // +/- 2.07791e-05 cm/us West: Slope = 0.370173 +/- 0.00374216 DV = 5.57247 +/- 2.07791e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
