TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6016052
  row.laserDriftVelocityEast	 =   5.53951; // +/- 4.99454e-05 cm/us All: East = 5.54061 +/- 9.93452e-05
  row.laserDriftVelocityWest	 =   5.53951; // +/- 4.99454e-05 cm/us All: West = 5.53915 +/- 5.77782e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.384093 +/- 0.00949218
  return (TDataSet *)tableSet;// West = 0.455226 +/- 0.0111463 East = 0.196353 +/- 0.0181081
};
