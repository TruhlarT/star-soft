TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169003
  row.laserDriftVelocityEast	 =   5.56823; // +/- 1.48603e-05 cm/us East: Slope = 1.12851 +/- 0.00267194 DV = 5.56823 +/- 1.48603e-05
  row.laserDriftVelocityWest	 =   5.57252; // +/- 2.15451e-05 cm/us West: Slope = 0.359057 +/- 0.00386382 DV = 5.57252 +/- 2.15451e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
