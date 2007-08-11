TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125064
  row.laserDriftVelocityEast	 =   5.57623; // +/- 1.93988e-05 cm/us East: Slope = -0.304302 +/- 0.00343225 DV = 5.57623 +/- 1.93988e-05
  row.laserDriftVelocityWest	 =   5.57872; // +/- 3.57301e-05 cm/us West: Slope = -0.749808 +/- 0.0064854 DV = 5.57872 +/- 3.57301e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
