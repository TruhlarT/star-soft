TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 128024
  row.laserDriftVelocityEast	 =   5.57362; // +/- -1 cm/us East: Slope = -0.4181 +/- 0.0350775 DV = 5.57707 +/- 0.000177068
  row.laserDriftVelocityWest	 =   5.57603; // +/- 3.39151e-05 cm/us West: Slope = -0.273163 +/- 0.00596896 DV = 5.57603 +/- 3.39151e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
