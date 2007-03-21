TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6048015
  row.laserDriftVelocityEast	 =   5.52682; // +/- 3.88238e-05 cm/us All: East = 5.52755 +/- 0.000408454
  row.laserDriftVelocityWest	 =   5.52682; // +/- 3.88238e-05 cm/us All: West = 5.52681 +/- 3.90004e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.3036 +/- 0.00735375
  return (TDataSet *)tableSet;// West = 1.30465 +/- 0.00738935 East = 1.19578 +/- 0.075003
};
