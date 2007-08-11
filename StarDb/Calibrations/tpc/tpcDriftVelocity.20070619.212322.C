TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 170074
  row.laserDriftVelocityEast	 =   5.56729; // +/- 1.77687e-05 cm/us East: Slope = 1.29846 +/- 0.00321692 DV = 5.56729 +/- 1.77687e-05
  row.laserDriftVelocityWest	 =   5.57134; // +/- 2.07139e-05 cm/us West: Slope = 0.572501 +/- 0.0037077 DV = 5.57134 +/- 2.07139e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
