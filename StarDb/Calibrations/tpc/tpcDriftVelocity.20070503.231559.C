TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 123065
  row.laserDriftVelocityEast	 =   5.57615; // +/- 1.45341e-05 cm/us East: Slope = -0.292583 +/- 0.00260479 DV = 5.57615 +/- 1.45341e-05
  row.laserDriftVelocityWest	 =   5.57904; // +/- 3.12207e-05 cm/us West: Slope = -0.811036 +/- 0.00561877 DV = 5.57904 +/- 3.12207e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
