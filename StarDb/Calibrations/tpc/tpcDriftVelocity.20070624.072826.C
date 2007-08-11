TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 175009
  row.laserDriftVelocityEast	 =   5.56964; // +/- 3.28323e-05 cm/us East: Slope = 0.878081 +/- 0.00582557 DV = 5.56964 +/- 3.28323e-05
  row.laserDriftVelocityWest	 =   5.57288; // +/- 3.30647e-05 cm/us West: Slope = 0.292936 +/- 0.00598001 DV = 5.57288 +/- 3.30647e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
