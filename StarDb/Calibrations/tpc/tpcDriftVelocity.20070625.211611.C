TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176076
  row.laserDriftVelocityEast	 =   5.56861; // +/- 2.60481e-05 cm/us East: Slope = 1.05953 +/- 0.00466506 DV = 5.56861 +/- 2.60481e-05
  row.laserDriftVelocityWest	 =   5.57181; // +/- 2.57347e-05 cm/us West: Slope = 0.488122 +/- 0.00460451 DV = 5.57181 +/- 2.57347e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
