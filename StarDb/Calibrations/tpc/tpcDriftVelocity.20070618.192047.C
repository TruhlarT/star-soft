TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169091
  row.laserDriftVelocityEast	 =   5.56729; // +/- 2.44394e-05 cm/us East: Slope = 1.30108 +/- 0.00437419 DV = 5.56729 +/- 2.44394e-05
  row.laserDriftVelocityWest	 =   5.57145; // +/- 2.8366e-05 cm/us West: Slope = 0.549574 +/- 0.00511121 DV = 5.57145 +/- 2.8366e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
