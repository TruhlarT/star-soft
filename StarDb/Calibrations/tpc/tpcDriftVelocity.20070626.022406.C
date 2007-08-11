TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176106
  row.laserDriftVelocityEast	 =   5.56828; // +/- 3.66341e-05 cm/us East: Slope = 1.13152 +/- 0.00661049 DV = 5.56828 +/- 3.66341e-05
  row.laserDriftVelocityWest	 =   5.57114; // +/- 2.8112e-05 cm/us West: Slope = 0.605145 +/- 0.00500893 DV = 5.57114 +/- 2.8112e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
