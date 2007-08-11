TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 134058
  row.laserDriftVelocityEast	 =   5.57185; // +/- 2.33936e-05 cm/us East: Slope = 0.478543 +/- 0.00416828 DV = 5.57185 +/- 2.33936e-05
  row.laserDriftVelocityWest	 =   5.5735; // +/- 3.1113e-05 cm/us West: Slope = 0.182987 +/- 0.00574682 DV = 5.5735 +/- 3.1113e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
