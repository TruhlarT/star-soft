TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 152011
  row.laserDriftVelocityEast	 =   5.56987; // +/- -1 cm/us East: Slope = 0.972182 +/- 10.2592 DV = 5.59882 +/- 0.0581429
  row.laserDriftVelocityWest	 =   5.5729; // +/- 1.69895e-05 cm/us West: Slope = 0.292382 +/- 0.00304741 DV = 5.5729 +/- 1.69895e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
