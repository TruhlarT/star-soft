TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 123016
  row.laserDriftVelocityEast	 =   5.57879; // +/- 1.58487e-05 cm/us All: East = -0.829289 +/- 0.00333498
  row.laserDriftVelocityWest	 =   5.57879; // +/- 1.58487e-05 cm/us All: West = -0.604074 +/- 0.00541767
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57879 +/- 1.58487e-05
  return (TDataSet *)tableSet;// West = 5.5779 +/- 3.01479e-05 East = 5.57914 +/- 1.86307e-05
};
