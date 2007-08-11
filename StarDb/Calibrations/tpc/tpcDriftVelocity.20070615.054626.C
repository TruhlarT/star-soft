TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 166009
  row.laserDriftVelocityEast	 =   5.56693; // +/- 2.50139e-05 cm/us East: Slope = 1.36523 +/- 0.00445531 DV = 5.56693 +/- 2.50139e-05
  row.laserDriftVelocityWest	 =   5.57031; // +/- -1 cm/us West: Slope = 0 +/- 0 DV = 0 +/- 0
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
