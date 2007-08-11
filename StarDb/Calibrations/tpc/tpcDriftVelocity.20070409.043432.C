TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 99004
  row.laserDriftVelocityEast	 =   5.57227; // +/- 2.59983e-05 cm/us East: Slope = 0.929058 +/- 0.00488553 DV = 5.57227 +/- 2.59983e-05
  row.laserDriftVelocityWest	 =   5.57324; // +/- 2.24791e-05 cm/us West: Slope = 0.81623 +/- 0.0043249 DV = 5.57324 +/- 2.24791e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
