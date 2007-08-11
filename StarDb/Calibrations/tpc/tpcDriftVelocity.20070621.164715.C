TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 172085
  row.laserDriftVelocityEast	 =   5.5687; // +/- 3.07393e-05 cm/us East: Slope = 1.04787 +/- 0.00545423 DV = 5.5687 +/- 3.07393e-05
  row.laserDriftVelocityWest	 =   5.57173; // +/- 1.92347e-05 cm/us West: Slope = 0.501316 +/- 0.00344467 DV = 5.57173 +/- 1.92347e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
