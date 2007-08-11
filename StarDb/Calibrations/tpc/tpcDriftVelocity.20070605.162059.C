TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 156050
  row.laserDriftVelocityEast	 =   5.57119; // +/- -1 cm/us East: Slope = -0.411789 +/- 0.0538755 DV = 5.57696 +/- 0.000376772
  row.laserDriftVelocityWest	 =   5.57433; // +/- 1.74099e-05 cm/us West: Slope = 0.0314844 +/- 0.0031295 DV = 5.57433 +/- 1.74099e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
